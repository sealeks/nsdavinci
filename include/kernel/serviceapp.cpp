
#include <kernel/serviceapp.h>
#include <kernel/constdef.h>
#include <stdio.h>

namespace dvnci {

    static fspath DVNCI_FULL_EXEC_PATH;
    static fspath DVNCI_FULL_EXEC_DIR;
    static std::string DVNCI_EXEC_FILE;

    boost::thread th;

    fspath FULL_EXEC_PATH(const fspath& fl) {
        static fspath exdir = fl;
        return exdir;
    }

    fspath FULL_EXEC_DIR(const fspath& fl) {
        static fspath exdir = fl;
        return exdir;
    }

    std::string EXEC_FILE(const std::string& fl) {
        static std::string exdir = fl;
        return exdir;
    }

    int serviceargumentparser(int argc, char** argv) {
        DVNCI_FULL_EXEC_PATH = argc > 0 ? argv[0] : "";
        FULL_EXEC_PATH(DVNCI_FULL_EXEC_PATH);
        DEBUG_VAL_DVNCI(DVNCI_FULL_EXEC_PATH);
        DVNCI_FULL_EXEC_DIR = DVNCI_FULL_EXEC_PATH.branch_path();
        FULL_EXEC_DIR(DVNCI_FULL_EXEC_DIR);
        DVNCI_EXEC_FILE = DVNCI_FULL_EXEC_PATH.filename().string();
        EXEC_FILE(DVNCI_EXEC_FILE);
        int oper = getserviceoperation(argc > 1 ? argv[1] : "");
        DEBUG_VAL_DVNCI(oper);
        switch (oper) {
            case SERVICE_OPEATION_INSTALL:
            {
                installservice(DVNCI_SERVICE_APPID, DVNCI_SERVICE_NAME);
                break;
            }
            case SERVICE_OPEATION_UNINSTALL:
            {
                uninstallservice(DVNCI_SERVICE_APPID);
                break;
            }
            case SERVICE_OPEATION_APP:
            {
                return SERVICE_OPEATION_APP;
            }
            case SERVICE_OPEATION_START:
            {
                startmain(argc, argv);
                break;
            }
            default: startmain(argc, argv);
        }
        return oper;
    }

    int appargumentparser(int argc, char** argv) {
        DVNCI_FULL_EXEC_PATH = argc > 0 ? argv[0] : "";
        DEBUG_VAL_DVNCI(DVNCI_FULL_EXEC_PATH);
        DVNCI_FULL_EXEC_DIR = DVNCI_FULL_EXEC_PATH.branch_path();
        FULL_EXEC_DIR(DVNCI_FULL_EXEC_DIR);
        DVNCI_EXEC_FILE = DVNCI_FULL_EXEC_PATH.filename().string();
        return 0;
    }

    int getserviceoperation(std::string val) {
        lower_and_trim(val);
        if (val.empty()) return SERVICE_OPEATION_START;
        if ((val == "/install") || (val == "\\install") || (val == "install") ||
                (val == "-install") || (val == "--install") || (val == "-i")) return SERVICE_OPEATION_INSTALL;
        if ((val == "/uninstall") || (val == "\\uninstall") || (val == "uninstall") ||
                (val == "-uninstall") || (val == "--uninstall") || (val == "-u")) return SERVICE_OPEATION_UNINSTALL;
        if ((val == "/start") || (val == "\\start") || (val == "start") ||
                (val == "-start") || (val == "--start") || (val == "-s")) return SERVICE_OPEATION_START;
        if ((val == "/stop") || (val == "\\stop") || (val == "stop") ||
                (val == "-stop") || (val == "--stop") || (val == "-t")) return SERVICE_OPEATION_STOP;
        if ((val == "/app") || (val == "\\app") || (val == "app") ||
                (val == "-app") || (val == "--app") || (val == "-a")) return SERVICE_OPEATION_APP;
        return SERVICE_OPEATION_START;
    }

    void registerservice();
    void unregisterservice();

    bool startservice() {
        registerservice();
        if (mainserv) {
            th = boost::thread(mainserv);
            th.join();
        }
        return true;
    }

    bool stopservice() {

        if (mainserv) {
            mainserv.terminate();
            th.join();
        }
        unregisterservice();
        return true;
    }

    std::string servicemanager::name(appidtype app) const {
        INP_SHARE_LOCK(memlock());
        return exists(app) ? operator[](app)->name() : "";
    }

    std::string servicemanager::fullpath(appidtype app) const {
        INP_SHARE_LOCK(memlock());
        return exists(app) ? (starttpath_ / operator[](app)->name().c_str()).string() : "";
    }

    servicemanager::servicemanager(const fspath& filepath, const fspath& strtpath) :
    filememorymap(filepath / DEMONENTRY_FILE_NAME, DEMONENTRY_MAP_NAME, sizeof (demon_item)* 200),
    starttpath_(strtpath.string().empty() ? filepath : strtpath) {
        ;
    }

    ns_error servicemanager::signature(iteminfo_map& mp) {
        INP_SHARE_LOCK(memlock());
        mp.clear();
        for (struct_type_ptr it = begin(); it != end(); ++it) {
            if (it->appid()) {
                name_with_type tmp_inf(it->name(), NT_SERVICE, status(it->appid()));
                mp.insert(iteminfo_pair(static_cast<indx> (it->appid()), tmp_inf));
            }
        }
        return 0;
    }

    void servicemanager::waitstate(appidtype app, int ws) {
        INP_SHARE_LOCK(memlock());
        if (exists(app)) {
            operator[](app)->waitstate(ws);
            if (ws)
                (*(structs_type_ptr) data()).header.incmonitor();
            (*(structs_type_ptr) data()).header.incmonitor();
        }
    }

    servicemanager::size_type servicemanager::add(appidtype app, const std::string& nm, int stt) {
        if (app <= 0) return npos;
        INP_EXCLUSIVE_LOCK(memlock());
        if (!static_cast<size_type> ((*(structs_type_ptr) data()).header.count())) {
            count(1);
            initstruct(0, app, nm, stt);
            writetofile();
            return 0;
        } else {
            if (find(app) != npos)
                return npos;
            if (!((structs_type_ptr) data())->items[0].appid()) {
                initstruct(0, app, nm, stt);
                sort();
                writetofile();
                return find(app);
            } else {
                count(((*(structs_type_ptr) data()).header.count()) + 1);
                initstruct(((*(structs_type_ptr) data()).header.count() - 1), app, nm, stt);
                sort();
                writetofile();
                return find(app);
            }
        }

        return npos;
    }

    servicemanager::size_type servicemanager::remove(appidtype app) {
        if (app <= 0) return npos;
        INP_EXCLUSIVE_LOCK(memlock());
        size_type it = find(app);
        if (it == npos)
            return npos;
        uninitstruct(it);
        struct_type tmpfnd;
        size_type newcnt = static_cast<size_type> (std::remove(begin(), end(), tmpfnd) - begin());
        count(newcnt);
        sort();
        writetofile();
        return it;
    }

    void servicemanager::writeheader() {
        demon_header tmp(static_cast<size_type> ((*(structs_type_ptr) data()).header.count()));
        utilptr->writestructtofile((const void*) &tmp, 0, sizeof (demon_header));
    }

    void servicemanager::writetofile(size_type id) {
        if (id != npos) {
            struct_type tmpnew = struct_for_write(id);
            writestructtodisk(tmpnew, id);
        } else {
            writeheader();
            for (indx i = 0; i<static_cast<size_type> ((*(structs_type_ptr) data()).header.count()); ++i) {
                struct_type tmpnew = struct_for_write(i);
                writestructtodisk(tmpnew, i);
            }
        }
    }
}



#if defined(_DVN_WIN_)


#include <conio.h>
#include <kernel/constdef.h>
#include <windows.h>


DWORD dwErrCode;
SERVICE_STATUS ss;
SERVICE_STATUS_HANDLE ssHandle;


namespace dvnci {

    struct sevicestatus {

        sevicestatus() {
            dysplayname = "nodef";
            path = "";
            runstate = SERVICE_RUNSTATE_NODEF;
            servicetype = 0;
            startname = "";
        }

        int runstate;
        int servicetype;
        std::string dysplayname;
        std::string path;
        std::string startname;
    };



    bool startservice(const std::string& nameservice);
    bool stopservice(const std::string& nameservice);
    bool serviceconfig(const std::string& nameservice, sevicestatus& info);
    bool setserviceconfig(const std::string& nameservice, sevicestatus& info);
    int servicestatus(const std::string& nameservice);

    void WINAPI servicemain(DWORD dwArgc, LPTSTR *lpszArgv);
    void WINAPI servicecontrol(DWORD dwControlCode);
    void setsomeservicestatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);

    int startmain(int argc, char** argv) {

        SERVICE_TABLE_ENTRYA DispatcherTable[] = {
            { (CHAR*) DVNCI_SERVICE_NAME.c_str(),
                (LPSERVICE_MAIN_FUNCTIONA) servicemain},
            { NULL, NULL}};

        if (!StartServiceCtrlDispatcherA(DispatcherTable)) {
            OUTSTRVAL_DVNCI(StartServiceCtrlDispatcherA, DVNCI_SERVICE_NAME)
            _getch();
            return (EXIT_SUCCESS);
        }
        return (EXIT_SUCCESS);
    };

    void WINAPI servicemain(DWORD dwArgc, LPTSTR *lpszArgv) {

        ssHandle = RegisterServiceCtrlHandlerA(DVNCI_SERVICE_NAME.c_str(), servicecontrol);
        if (!ssHandle) {
            OUTSTRVAL_DVNCI(Error registering ServiceControl, DVNCI_SERVICE_NAME)
            _getch();
            return;
        }
        ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        setsomeservicestatus(SERVICE_START_PENDING, NO_ERROR, 4000);
        setsomeservicestatus(SERVICE_RUNNING, NO_ERROR, 0);
        startservice();
        return;
    }

    void registerservice() {
    }

    void unregisterservice() {
    }

    bool installservice(appidtype app, const std::string& nameservice) {

        servicemanager_ptr svm = demon_entry_factory::build(DVNCI_FULL_EXEC_DIR);

        if (!svm) {
            demon_entry_factory::createstorige(DVNCI_FULL_EXEC_DIR);
            svm = demon_entry_factory::build(DVNCI_FULL_EXEC_DIR);
        }

        if (!svm) {
            OUTSTRVAL_DVNCI(Cannot dvnci servicetable entry create, nameservice);
            return false;
        }

        svm->install_demon(app, nameservice);

        SC_HANDLE hService;
        SC_HANDLE hSCManager;


        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;
        }

        hService = CreateServiceA(hSCManager, nameservice.c_str(),
                nameservice.c_str(), SERVICE_ALL_ACCESS,
                SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START,
                SERVICE_ERROR_NORMAL,
                DVNCI_FULL_EXEC_PATH.string().c_str(),
                NULL, NULL, NULL, NULL, NULL);
        if (!hService) {
            DWORD errret = GetLastError();
            if (ERROR_SERVICE_EXISTS == errret) {
                OUTSTRVAL_DVNCI(Service allaways installed, nameservice);
                return true;
            }
            OUTSTRVAL_DVNCI(Cant service fo install, nameservice)
            CloseServiceHandle(hSCManager);
            svm->uninstall_demon(app);
            return false;
        }



        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        OUTSTRVAL_DVNCI(Service succesfull install, nameservice)
        return true;
    }

    bool uninstallservice(appidtype app) {

        servicemanager_ptr svm = demon_entry_factory::build(DVNCI_FULL_EXEC_DIR);

        if (!svm) {
            OUTSTRVAL_DVNCI(Cannot dvnci servicetable entry find, DVNCI_SERVICE_NAME);
        } else {
            svm->uninstall_demon(app);
        }



        SC_HANDLE hService;
        SC_HANDLE hSCManager;

        hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;
        }

        hService = OpenServiceA(hSCManager, DVNCI_SERVICE_NAME.c_str(), SERVICE_STOP | DELETE);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo uninstall, DVNCI_SERVICE_NAME)
            CloseServiceHandle(hSCManager);
            return false;
        }

        if (!DeleteService(hService)) {
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            OUTSTRVAL_DVNCI(Cant service fo uninstall, DVNCI_SERVICE_NAME)
            return false;
        }


        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        OUTSTRVAL_DVNCI(Service succesfull uninstall, DVNCI_SERVICE_NAME)
        return true;
    }

    bool startservice(const std::string& nameservice) {

        SC_HANDLE hService;
        SC_HANDLE hSCManager;

        hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;
        }

        hService = OpenServiceA(hSCManager, nameservice.c_str(), SERVICE_START);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo start, nameservice)
            CloseServiceHandle(hSCManager);
            return false;
        }

        if (!StartServiceA(hService, 0, NULL)) {
            DEBUG_STR_VAL_DVNCI(Cant start service, nameservice)
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return false;
        }

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;
    }

    bool stopservice(const std::string& nameservice) {
        SC_HANDLE hService;
        SC_HANDLE hSCManager;



        hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;
        }

        hService = OpenServiceA(hSCManager, nameservice.c_str(), SERVICE_STOP);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo stop, nameservice)
            CloseServiceHandle(hSCManager);
            return false;
        }

        if (!ControlService(hService, SERVICE_CONTROL_STOP, &ss)) {
            DEBUG_STR_VAL_DVNCI(Cant stop service, nameservice)
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return false;
        }

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;
    }

    bool serviceconfig(const std::string& nameservice, sevicestatus& config) {

        SC_HANDLE hService;
        SC_HANDLE hSCManager;
        LPQUERY_SERVICE_CONFIGA lpBufConfig;
        DWORD dwBytesNeeded;

        hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;
        }

        hService = OpenServiceA(hSCManager, nameservice.c_str(), SERVICE_QUERY_CONFIG);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo read config, nameservice)
            CloseServiceHandle(hSCManager);
            return false;
        }


        lpBufConfig = (LPQUERY_SERVICE_CONFIGA) malloc(4096);


        if ((lpBufConfig != NULL) && (QueryServiceConfigA(hService, lpBufConfig, 4096, &dwBytesNeeded))) {


            switch (lpBufConfig->dwStartType) {
                case SERVICE_BOOT_START:
                {
                    config.runstate = SERVICE_RUNSTATE_BOOT;
                    break;
                }
                case SERVICE_SYSTEM_START:
                {
                    config.runstate = SERVICE_RUNSTATE_SYSTEM;
                    break;
                }
                case SERVICE_AUTO_START:
                {
                    config.runstate = SERVICE_RUNSTATE_AUTO;
                    break;
                }
                case SERVICE_DEMAND_START:
                {
                    config.runstate = SERVICE_RUNSTATE_DEMAND;
                    break;
                }
                case SERVICE_DISABLED:
                {
                    config.runstate = SERVICE_RUNSTATE_OFF;
                    break;
                }
                default: config.runstate = SERVICE_RUNSTATE_NODEF;
            }
            config.dysplayname = lpBufConfig->lpDisplayName;
            config.path = lpBufConfig->lpBinaryPathName;
            config.startname = lpBufConfig->lpServiceStartName;
            free(lpBufConfig);
        } else {
            DEBUG_STR_VAL_DVNCI(Cant queryconfig service, nameservice)
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return false;
        }

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;
    }

    bool setserviceconfig(const std::string& nameservice, sevicestatus& config) {

        SC_HANDLE hService;
        SC_HANDLE hSCManager;
        LPQUERY_SERVICE_CONFIGA lpBufConfig;
        DWORD dwBytesNeeded;
        DEBUG_STR_DVNCI(set_property(num64 id, sevicestatus & val))
        hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;
        }

        hService = OpenServiceA(hSCManager, nameservice.c_str(), SERVICE_QUERY_CONFIG | SERVICE_CHANGE_CONFIG);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo read config, nameservice)
            CloseServiceHandle(hSCManager);
            return false;
        }

        lpBufConfig = (LPQUERY_SERVICE_CONFIGA) malloc(4096);

        if ((lpBufConfig) && (QueryServiceConfigA(hService, lpBufConfig, 4096, &dwBytesNeeded))) {
            bool tmp_isch = false;
            DWORD tmpsttp = lpBufConfig->dwStartType;
            switch (config.runstate) {
                case SERVICE_RUNSTATE_OFF:
                {
                    if (tmpsttp != SERVICE_DISABLED) {
                        tmp_isch = true;
                        tmpsttp = SERVICE_DISABLED;
                    };
                    break;
                }
                case SERVICE_RUNSTATE_DEMAND:
                {
                    if (tmpsttp != SERVICE_DEMAND_START) {
                        tmp_isch = true;
                        tmpsttp = SERVICE_DEMAND_START;
                    };
                    break;
                }
                case SERVICE_RUNSTATE_AUTO:
                {
                    if (tmpsttp != SERVICE_AUTO_START) {
                        tmp_isch = true;
                        tmpsttp = SERVICE_AUTO_START;
                    };
                    break;
                }
            }
            if (tmp_isch) {

                DEBUG_STR_DVNCI(ChangeServiceConfig hService)
                if (!ChangeServiceConfig(hService,
                        SERVICE_NO_CHANGE,
                        tmpsttp,
                        SERVICE_NO_CHANGE,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL,
                        NULL)) {
                    DEBUG_STR_VAL_DVNCI(Cant changeconfig service, nameservice)
                    CloseServiceHandle(hService);
                    CloseServiceHandle(hSCManager);
                    return false;
                }
            }
            free(lpBufConfig);
        } else {
            DEBUG_STR_VAL_DVNCI(Cant queryconfig service, nameservice)
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return false;
        }

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;
    }

    int servicestatus(const std::string& nameservice) {
        SC_HANDLE hService;
        SC_HANDLE hSCManager;
        SERVICE_STATUS ServiceStatus;
        int reslt = SERVICE_STATUS_NODEF;
        hSCManager = OpenSCManagerA(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return SERVICE_STATUS_NODEF;
        }

        hService = OpenServiceA(hSCManager, nameservice.c_str(), SERVICE_QUERY_STATUS);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo read status, nameservice)
            CloseServiceHandle(hSCManager);
            return SERVICE_STATUS_NODEF;
        }


        if (!QueryServiceStatus(hService, &ServiceStatus)) {
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return SERVICE_STATUS_NODEF;
        }

        switch (ServiceStatus.dwCurrentState) {
            case SERVICE_STOPPED:
            {
                reslt = SERVICE_STATUS_STOPED;
                break;
            }
            case SERVICE_RUNNING:
            {
                reslt = SERVICE_STATUS_RUN;
                break;
            }
            case SERVICE_PAUSED:
            {
                reslt = SERVICE_STATUS_PENDING;
                break;
            }
            case SERVICE_STOP_PENDING:
            case SERVICE_START_PENDING:
            case SERVICE_PAUSE_PENDING:
            case SERVICE_CONTINUE_PENDING:
            {
                reslt = SERVICE_STATUS_PENDING;
                break;
            }
            default:
            {
                reslt = SERVICE_STATUS_PENDING;
            }
        }



        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return reslt;
    }

    void WINAPI servicecontrol(DWORD dwControlCode) {

        switch (dwControlCode) {
            case SERVICE_CONTROL_STOP:
            {
                setsomeservicestatus(SERVICE_STOP_PENDING, NO_ERROR, 0);

                stopservice();
                setsomeservicestatus(SERVICE_STOPPED, NO_ERROR, 0);
                break;
            }
            case SERVICE_CONTROL_INTERROGATE:
            {
                setsomeservicestatus(ss.dwCurrentState, NO_ERROR, 0);
                break;
            }
            default:
            {
                setsomeservicestatus(ss.dwCurrentState, NO_ERROR, 0);
                break;
            }
        }
    }

    void setsomeservicestatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint) {

        static DWORD dwCheckPoint = 1;

        if (dwCurrentState == SERVICE_START_PENDING)
            ss.dwControlsAccepted = 0;
        else
            ss.dwControlsAccepted = SERVICE_ACCEPT_STOP;

        ss.dwCurrentState = dwCurrentState;
        ss.dwWin32ExitCode = dwWin32ExitCode;
        ss.dwWaitHint = dwWaitHint;


        if (dwCurrentState == SERVICE_RUNNING || dwCurrentState == SERVICE_STOPPED)
            ss.dwCheckPoint = 0;
        else
            ss.dwCheckPoint = dwCheckPoint++;

        SetServiceStatus(ssHandle, &ss);
    }

    ///////////////////////////////////////////////////

    int servicemanager::pid(appidtype app) const {
        return 0;
    }

    void servicemanager::pid(appidtype app, int pd) {
        ;
    }

    int servicemanager::starttype(appidtype app) const {
        INP_SHARE_LOCK(memlock());
        if (exists(app)) {
            sevicestatus val;
            if (serviceconfig(name(app), val))
                return val.runstate;
        }
        return 0;
    }

    void servicemanager::starttype(appidtype app, int stt) {
        INP_SHARE_LOCK(memlock())
        if (exists(app)) {
            sevicestatus val;
            if (serviceconfig(name(app), val))
                val.runstate = stt;
            setserviceconfig(name(app), val);
        }
    }

    int servicemanager::status(appidtype app) const {
        INP_SHARE_LOCK(memlock());
        if (exists(app)) {
            return servicestatus(name(app));
        }
        return SERVICE_STATUS_NODEF;
    }

    void servicemanager::status(appidtype app, int sts) {
        ;
    }

    bool servicemanager::install_demon(appidtype app, const std::string& nm, int stt) {
        if (true/*demon_fileexists(nm+platformspec())*/) {
            return (add(app, nm, stt) != npos);
        }
        return false;
    }

    bool servicemanager::uninstall_demon(appidtype app) {
        return (remove(app) != npos);
    }

    std::string servicemanager::platformspec() const {
        return "";
    }

    bool servicemanager::operation_impl(appidtype app, int oper) {

        DEBUG_VAL2_DVNCI(app, oper)
        INP_SHARE_LOCK(memlock());
        if (exists(app)) {
            switch (oper) {
                case SERVICE_OPEATION_START:
                {
                    DEBUG_VAL2_DVNCI(oper, name(app))
                    if (servicestatus(name(app)) != SERVICE_STATUS_STOPED) return false;
                    DEBUG_VAL2_DVNCI(oper, name(app))
                    return startservice(name(app));
                }
                case SERVICE_OPEATION_STOP:
                {
                    if (servicestatus(name(app)) != SERVICE_STATUS_RUN) return false;
                    return stopservice(name(app));
                }
            }
        }
        return false;
    }
}





#elif defined(_DVN_LIN_)



namespace dvnci {


    std::string LOG_DEMON_FILE = "";

    int startdemonlog() {
        if (LOG_DEMON_FILE.empty()) return 1;
        std::ofstream ofs(LOG_DEMON_FILE.c_str(), std::ios::trunc);
        if (!ofs)
            return 1;
        ofs << "Start logging: " << datetime_to_string(now()) << std::endl;
        return 0;
    }

    int writedemonlog(const std::string& msg, const std::string& opt) {
        if (LOG_DEMON_FILE.empty()) return 1;
        std::ofstream ofs(LOG_DEMON_FILE.c_str(), std::ios::in | std::ios::ate);
        if (!ofs)
            return 1;
        ofs << datetime_to_string(now()) << " : " << msg << (opt.empty() ? "" : (" :" + opt)) << std::endl;
        return 0;
    }

    pid_t demonize(const std::string& cmd, int argc, char** argv) {
        pid_t pid = 0;
        struct rlimit limits;
        struct sigaction sa;

        umask(0);

        if (getrlimit(RLIMIT_NOFILE, &limits) < 0) {
            writedemonlog("can`t get RLIMIT_NOFILE");
            exit(EXIT_FAILURE);
        }

        if ((pid = fork()) < 0) {
            writedemonlog("fork error");
            exit(EXIT_FAILURE);
        } else if (0 != pid) {
            writedemonlog("fork success");
            exit(0);
        }

        appargumentparser(argc, argv);

        writedemonlog("after fork success");

        if ((setsid()) == (pid_t) - 1) {
            writedemonlog("setsig error");
            exit(EXIT_FAILURE);
        }

        writedemonlog("after setsid success");

        sa.sa_handler = SIG_IGN;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;
        if (sigaction(SIGHUP, &sa, NULL) < 0) {
            writedemonlog("can`t ignore SIGHUP");
            exit(EXIT_FAILURE);
        }

        writedemonlog("after sidsigaction succcess");

        if ((pid = fork()) < 0) {
            writedemonlog("fork error");
            exit(EXIT_FAILURE);
        } else if (0 != pid) {
            exit(0);
        }

        appargumentparser(argc, argv);

        writedemonlog("FULL_EXEC_DIR:" + FULL_EXEC_DIR().string());


        if (chdir("/") < 0) {
            writedemonlog("can`t chdir() to /");
            exit(EXIT_FAILURE);
        }


        if (limits.rlim_max == RLIM_INFINITY)
            limits.rlim_max = 1024;

        u_int32_t idx;
        for (idx = 0; idx < limits.rlim_max; ++idx) {
            close(idx);
        }


        int fd0 = open("/dev/null", O_RDWR);
        int fd1 = dup(0);
        int fd2 = dup(0);


        writedemonlog("after close succcess");

        if (fd0 != 0 || fd1 != 1 || fd2 != 2) {
            writedemonlog("bad file descriptor");
        }
        return getpid();
    }

    int already_running(const std::string& cmd) {
        char buff[4096] = "\0";
        sprintf(buff, "%s%s", "/var/run/", cmd.c_str());
        /**  */
        int fd = open(buff, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        if (fd < 0) {
            writedemonlog("can`t open PID file");
            exit(EXIT_FAILURE);
        }
        if (lockf(fd, F_TLOCK, 0)) {
            if (errno == EACCES || errno == EAGAIN) {
                close(fd);
                return 1;
            }
            writedemonlog("can`t lock PID file");
            exit(EXIT_FAILURE);
        }

        ftruncate(fd, 0);
        sprintf(buff, "%d", (int) getpid());
        write(fd, buff, strlen(buff));

        return 0;
    }

    void* process_signal_thr(void* arg) {
        struct process_signal_args* opt = (struct process_signal_args*) arg;
        while (opt->running) {
            int signo = 0;
            if (0 != sigwait(opt->mask, &signo)) {
                writedemonlog("error in sigwait =", strerror(errno));
                exit(EXIT_FAILURE);
            }
            switch (signo) {
                case SIGHUP:
                    writedemonlog("reread configuration");
                    if (opt->reread_func_t) {
                        opt->reread_func_t();
                    }
                    break;
                case SIGTERM:
                case SIGABRT:
                    writedemonlog("receive signal SIGTERM. exiting...");
                    if (opt->terminate_func_t) {
                        opt->terminate_func_t();
                    }
                    opt->running = 0;
                    break;
                default:
                    writedemonlog("unspecified signal '%d' received. ignored.");
                    break;
            }
        }
        return 0;
    }




    void servicemain(int argc, char** argv);

    void setsomeservicestatus(int dwCurrentState, int dwWin32ExitCode, int dwWaitHint);

    void demon_reread_func() {
    }

    void demon_terminate_func() {
        stopservice();
    }

    int startmain(int argc, char** argv) {

        pid_t PIDPRC = 0;
        sigset_t mask;
        struct sigaction sa;
        pthread_t tid;
        process_signal_args thread_args;

        std::string demon_execute_cmd = (NULL == strrchr(argv[0], '/')) ? argv[0] : strrchr(argv[0], '/') + 1;

        std::string tmpdir = "";
        try {
            tmpdir = boost::filesystem::temp_directory_path().string();
        }        catch (...) {
            tmpdir = "";
        }


        dvnci::LOG_DEMON_FILE = (!tmpdir.empty()) ? tmpdir + "/" + EXEC_FILE().c_str() + ".log" : "";


        startdemonlog();
        writedemonlog("Start demonaze");
        PIDPRC = demonize(demon_execute_cmd, argc, argv);

        if (already_running(demon_execute_cmd)) {
            writedemonlog("daemon " + demon_execute_cmd + " already running");
            exit(EXIT_FAILURE);
        }

        sa.sa_handler = SIG_DFL;
        sigemptyset(&sa.sa_mask);
        sa.sa_flags = 0;

        if (sigaction(SIGHUP, &sa, NULL) < 0) {
            writedemonlog("sigaction error");
            exit(EXIT_FAILURE);
        }

        sigfillset(&mask);
        if (0 != pthread_sigmask(SIG_BLOCK, &mask, NULL)) {
            writedemonlog("pthread_sigmask error");
            exit(EXIT_FAILURE);
        }

        thread_args.mask = &mask;
        thread_args.running = 1;
        /**  */
        thread_args.reread_func_t = demon_reread_func;
        /**  */
        thread_args.terminate_func_t = demon_terminate_func;
        /**  */

#ifndef DVNCI_NUX_SVM

        servicemanager_ptr svm = demon_entry_factory::build(DVNCI_FULL_EXEC_DIR);
        if (svm) {
            if (svm->exists(DVNCI_SERVICE_APPID)) {
                svm->pid(DVNCI_SERVICE_APPID, (int) PIDPRC);
            }
        }

#endif

        if (pthread_create(&tid, NULL, process_signal_thr, &thread_args)) {
            writedemonlog("can`t create thread");
            exit(EXIT_FAILURE);
        }

        writedemonlog("start deamon test");

        startservice();

#ifndef DVNCI_NUX_SVM
        if (svm) {
            if (svm->exists(DVNCI_SERVICE_APPID)) {
                svm->pid(DVNCI_SERVICE_APPID, 0);
            }
        }

#endif        

        writedemonlog("test stop loop");
        return (EXIT_SUCCESS);
    };

    void registerservice() {
    }

    void unregisterservice() {
    }

    bool installservice(appidtype app, const std::string& nameservice) {

        servicemanager_ptr svm = demon_entry_factory::build(DVNCI_FULL_EXEC_DIR);

        if (!svm) {
            demon_entry_factory::createstorige(DVNCI_FULL_EXEC_DIR);
            svm = demon_entry_factory::build(DVNCI_FULL_EXEC_DIR);
        }

        if (!svm) {
            OUTSTRVAL_DVNCI(Cannot dvnci servicetable entry create, nameservice);
            return false;
        }

        return svm->install_demon(app, nameservice);
    }

    bool uninstallservice(appidtype app) {

        servicemanager_ptr svm = demon_entry_factory::build(DVNCI_FULL_EXEC_DIR);

        if (!svm) {
            OUTSTRVAL_DVNCI(Cannot dvnci servicetable entry find, DVNCI_SERVICE_NAME);
            return false;
        }

        return svm->uninstall_demon(app);
    }

    bool startservice(const std::string& nameservice) {
        return true;
    }

    bool stopservice(const std::string& nameservice) {
        return true;
    }


    ///////////////////////////////////////////////////

    int servicemanager::pid(appidtype app) const {
        INP_SHARE_LOCK(memlock());
        return exists(app) ? operator[](app)->pid() : 0;
    }

    void servicemanager::pid(appidtype app, int pd) {
        INP_SHARE_LOCK(memlock())
        if (exists(app))
            operator[](app)->pid(pd);
    }

    int servicemanager::starttype(appidtype app) const {
        INP_SHARE_LOCK(memlock());
        return exists(app) ? operator[](app)->starttype() : 0;
    }

    void servicemanager::starttype(appidtype app, int stt) {
        INP_SHARE_LOCK(memlock())
        if (exists(app)) {
            size_type it = find(app);
            operator[](app)->starttype(stt);
            if (it != npos)
                writetofile(it);
        }
    }

    int servicemanager::status(appidtype app) const {
        INP_SHARE_LOCK(memlock());
        if (!exists(app))
            return SERVICE_STATUS_NODEF;
        if (pid(app)) {
            return (demon_item::TERM_WAIT_STATE == waitstate(app)) ? SERVICE_STATUS_PENDING : SERVICE_STATUS_RUN;
        }
        return (demon_item::RUN_WAIT_STATE == waitstate(app)) ? SERVICE_STATUS_PENDING : SERVICE_STATUS_STOPED;
    }

    void servicemanager::status(appidtype app, int sts) {
    }

    bool servicemanager::install_demon(appidtype app, const std::string& nm, int stt) {
        return (add(app, nm, stt) != npos);
    }

    bool servicemanager::uninstall_demon(appidtype app) {
        return (remove(app) != npos);
    }

    std::string servicemanager::platformspec() const {
        return "";
    }

    bool servicemanager::operation_impl(appidtype app, int oper) {

        DEBUG_VAL2_DVNCI(app, oper)
        INP_SHARE_LOCK(memlock());
        if (exists(app)) {
            switch (oper) {
                case SERVICE_OPEATION_START:
                {
                    DEBUG_VAL2_DVNCI(oper, name(app))
                    if ((!exists(app)) || (pid(app))) return false;
                    DEBUG_VAL2_DVNCI(oper, name(app))
                    waitstate(app, demon_item::RUN_WAIT_STATE);
                    return true;
                }
                case SERVICE_OPEATION_STOP:
                {
                    DEBUG_VAL2_DVNCI(oper, name(app))
                    if ((!exists(app)) || (!pid(app))) return false;
                    DEBUG_VAL2_DVNCI(oper, name(app))
                    waitstate(app, demon_item::TERM_WAIT_STATE);
                    return true;
                }
            }
        }
        return false;
    }
}

#else
#error No define service menager
#endif


