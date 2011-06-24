



#include <conio.h>

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
            startname = "";}

        int runstate;
        int servicetype;
        std::string dysplayname;
        std::string path;
        std::string startname;};
        
        

    bool startservice(const std::string& nameservice);
    bool stopservice(const std::string& nameservice);
    bool serviceconfig(const std::string& nameservice, sevicestatus& info);
    bool setserviceconfig(const std::string& nameservice, sevicestatus& info);
    int  servicestatus(const std::string& nameservice);   

    void WINAPI servicemain(DWORD dwArgc, LPTSTR *lpszArgv);
    void WINAPI servicecontrol(DWORD dwControlCode);
    void setsomeservicestatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint);



    int  startmain(int argc, char** argv) {

        SERVICE_TABLE_ENTRY DispatcherTable[] ={{ (CHAR*) DVNCI_SERVICE_NAME.c_str(),             
                (LPSERVICE_MAIN_FUNCTION) servicemain },
                { NULL, NULL }};
        
        if (!StartServiceCtrlDispatcher(DispatcherTable)) {
            OUTSTRVAL_DVNCI(StartServiceCtrlDispatcher, DVNCI_SERVICE_NAME )
            _getch();
            return (EXIT_SUCCESS) ;}
        return (EXIT_SUCCESS) ;};

    void WINAPI servicemain(DWORD dwArgc, LPTSTR *lpszArgv) {

        ssHandle = RegisterServiceCtrlHandler(DVNCI_SERVICE_NAME.c_str(), servicecontrol);
        if (!ssHandle) {
            OUTSTRVAL_DVNCI(Error registering ServiceControl, DVNCI_SERVICE_NAME)
            _getch();
            return;}
        ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        setsomeservicestatus(SERVICE_START_PENDING, NO_ERROR, 4000);
        setsomeservicestatus(SERVICE_RUNNING, NO_ERROR, 0);
        startservice();
        return;}

    bool installservice(appidtype app, const std::string& nameservice) {
        
        //servicemanager_ptr demon_entry_factory::build(const fspath& filepath)
        SC_HANDLE hService;
        SC_HANDLE hSCManager;


        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;}

        hService = CreateService(hSCManager, nameservice.c_str(),
                nameservice.c_str(), SERVICE_ALL_ACCESS,
                SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START,
                SERVICE_ERROR_NORMAL,
                DVNCI_FULL_EXEC_PATH.string().c_str(),
                NULL, NULL, NULL, NULL, NULL);
        if (!hService) {
            OUTSTRVAL_DVNCI(Cant service fo install,  nameservice )
            CloseServiceHandle(hSCManager);
            return false;}

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        OUTSTRVAL_DVNCI(Service succesfull install, nameservice)
        return true;}

    bool uninstallservice(appidtype app) {

        SC_HANDLE hService;
        SC_HANDLE hSCManager;

        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;}

        hService = OpenService(hSCManager, DVNCI_SERVICE_NAME.c_str(), SERVICE_STOP | DELETE);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo uninstall , nameservice)
            CloseServiceHandle(hSCManager);
            return false;}

        if (!DeleteService(hService)) {
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            OUTSTRVAL_DVNCI(Cant service fo uninstall,  DVNCI_SERVICE_NAME )
            return false;}


        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        OUTSTRVAL_DVNCI(Service succesfull uninstall, DVNCI_SERVICE_NAME)
        return true;}

    bool startservice(const std::string& nameservice) {

        SC_HANDLE hService;
        SC_HANDLE hSCManager;

        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;}

        hService = OpenService(hSCManager, nameservice.c_str(), SERVICE_START);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo start , nameservice)
            CloseServiceHandle(hSCManager);
            return false;}

        if (!StartService(hService, 0, NULL)) {
            DEBUG_STR_VAL_DVNCI(Cant start service , nameservice)
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return false;}

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;}

    bool stopservice(const std::string& nameservice) {
        SC_HANDLE hService;
        SC_HANDLE hSCManager;



        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;}

        hService = OpenService(hSCManager, nameservice.c_str(), SERVICE_STOP);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo stop , nameservice)
            CloseServiceHandle(hSCManager);
            return false;}

        if (!ControlService(hService, SERVICE_CONTROL_STOP, &ss)) {
            DEBUG_STR_VAL_DVNCI(Cant stop service , nameservice)
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return false;}

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;}

    bool serviceconfig(const std::string& nameservice, sevicestatus& config) {

        SC_HANDLE hService;
        SC_HANDLE hSCManager;
        LPQUERY_SERVICE_CONFIG lpBufConfig;
        DWORD dwBytesNeeded;

        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;}

        hService = OpenService(hSCManager, nameservice.c_str(), SERVICE_QUERY_CONFIG);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo read config , nameservice)
            CloseServiceHandle(hSCManager);
            return false;}


        lpBufConfig = (LPQUERY_SERVICE_CONFIG) malloc(4096);


        if ((lpBufConfig != NULL) && (QueryServiceConfig(hService, lpBufConfig, 4096, &dwBytesNeeded))) {


            switch (lpBufConfig->dwStartType) {
                case SERVICE_BOOT_START:{
                    config.runstate = SERVICE_RUNSTATE_BOOT;
                    break;}
                case SERVICE_SYSTEM_START:{
                    config.runstate = SERVICE_RUNSTATE_SYSTEM;
                    break;}
                case SERVICE_AUTO_START:{
                    config.runstate = SERVICE_RUNSTATE_AUTO;
                    break;}
                case SERVICE_DEMAND_START:{
                    config.runstate = SERVICE_RUNSTATE_DEMAND;
                    break;}
                case SERVICE_DISABLED:{
                    config.runstate = SERVICE_RUNSTATE_OFF;
                    break;}
                default: config.runstate = SERVICE_RUNSTATE_NODEF;}
            config.dysplayname = lpBufConfig->lpDisplayName;
            config.path = lpBufConfig->lpBinaryPathName;
            config.startname = lpBufConfig->lpServiceStartName;
            free(lpBufConfig);}
        else {
            DEBUG_STR_VAL_DVNCI(Cant queryconfig service , nameservice)
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return false;}

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;}

    bool setserviceconfig(const std::string& nameservice, sevicestatus& config) {

        SC_HANDLE hService;
        SC_HANDLE hSCManager;
        LPQUERY_SERVICE_CONFIG lpBufConfig;
        DWORD dwBytesNeeded;
        DEBUG_STR_DVNCI(set_property(num64 id, sevicestatus & val))
        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;}

        hService = OpenService(hSCManager, nameservice.c_str(), SERVICE_QUERY_CONFIG | SERVICE_CHANGE_CONFIG);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo read config , nameservice)
            CloseServiceHandle(hSCManager);
            return false;}

        lpBufConfig = (LPQUERY_SERVICE_CONFIG) malloc(4096);

        if ((lpBufConfig) && (QueryServiceConfig(hService, lpBufConfig, 4096, &dwBytesNeeded))) {
            bool tmp_isch = false;
            DWORD tmpsttp = lpBufConfig->dwStartType;
            switch (config.runstate) {
                case SERVICE_RUNSTATE_OFF:{
                    if (tmpsttp != SERVICE_DISABLED) {
                        tmp_isch = true;
                        tmpsttp = SERVICE_DISABLED;};
                    break;}
                case SERVICE_RUNSTATE_DEMAND:{
                    if (tmpsttp != SERVICE_DEMAND_START) {
                        tmp_isch = true;
                        tmpsttp = SERVICE_DEMAND_START;};
                    break;}
                case SERVICE_RUNSTATE_AUTO:{
                    if (tmpsttp != SERVICE_AUTO_START) {
                        tmp_isch = true;
                        tmpsttp = SERVICE_AUTO_START;};
                    break;}}
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
                    DEBUG_STR_VAL_DVNCI(Cant changeconfig service , nameservice)
                    CloseServiceHandle(hService);
                    CloseServiceHandle(hSCManager);
                    return false;}}
            free(lpBufConfig);}
        else {
            DEBUG_STR_VAL_DVNCI(Cant queryconfig service , nameservice)
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return false;}

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return true;}

    int  servicestatus(const std::string& nameservice) {
        SC_HANDLE hService;
        SC_HANDLE hSCManager;
        SERVICE_STATUS   ServiceStatus;
        int reslt = SERVICE_STATUS_NODEF;
        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return SERVICE_STATUS_NODEF;}

        hService = OpenService(hSCManager, nameservice.c_str(), SERVICE_QUERY_STATUS);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo read status , nameservice)
            CloseServiceHandle(hSCManager);
            return SERVICE_STATUS_NODEF;}


        if (!QueryServiceStatus(hService, &ServiceStatus)) {
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            return SERVICE_STATUS_NODEF;}

        switch (ServiceStatus.dwCurrentState) {
            case SERVICE_STOPPED:{
                reslt = SERVICE_STATUS_STOPED;
                break;}
            case SERVICE_RUNNING:{
                reslt = SERVICE_STATUS_RUN;
                break;}
            case SERVICE_PAUSED:{
                reslt = SERVICE_STATUS_PENDING;
                break;}
            case SERVICE_STOP_PENDING:
            case SERVICE_START_PENDING:
            case SERVICE_PAUSE_PENDING:
            case SERVICE_CONTINUE_PENDING:{
                reslt = SERVICE_STATUS_PENDING;
                break;}
            default:{
                reslt = SERVICE_STATUS_PENDING;}}



        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        return reslt;}

    void WINAPI servicecontrol(DWORD dwControlCode) {

        switch (dwControlCode) {
            case SERVICE_CONTROL_STOP:{
                setsomeservicestatus(SERVICE_STOP_PENDING, NO_ERROR, 0);

                stopservice();
                setsomeservicestatus(SERVICE_STOPPED, NO_ERROR, 0);
                break;}
            case SERVICE_CONTROL_INTERROGATE:{
                setsomeservicestatus(ss.dwCurrentState, NO_ERROR, 0);
                break;}
            default:{
                setsomeservicestatus(ss.dwCurrentState, NO_ERROR, 0);
                break;}}}

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

        SetServiceStatus(ssHandle, &ss);}

///////////////////////////////////////////////////

    
        int servicemanager::pid(appidtype app) const {
            return 0;}  
        
        void servicemanager::pid(appidtype app, int pd) {;}  
        
        
        
        int servicemanager::starttype(appidtype app) const {
            INP_SHARE_LOCK(memlock());
            if (exists(app)){
                sevicestatus val;
                if (serviceconfig(name(app), val))
                   return val.runstate;}
            return 0;}
            
            
        
        void servicemanager::starttype(appidtype app, int stt) {
            INP_EXCLUSIVE_LOCK(memlock())
            if (exists(app)){
                sevicestatus val;
                if (serviceconfig(name(app), val))
                    val.runstate=stt;
                    setserviceconfig(name(app), val);}}            
        
        
        
       int servicemanager::status(appidtype app) const {
            INP_SHARE_LOCK(memlock());
            if (exists(app)){
                return servicestatus(name(app));}
       return SERVICE_STATUS_NODEF;}  
        
       void servicemanager::status(appidtype app, int sts) {;}         
        
        
        
       bool servicemanager::install_demon(appidtype app, const std::string& nm, int stt){
           if (demon_fileexists(nm+platformspec())) {
                return (add(app, nm, stt)!=npos);}
           return false;}
       
       bool servicemanager::uninstall_demon(appidtype app){
           return (remove(app)!=npos);}      
        
        
        std::string servicemanager::platformspec() const {
            return "";}
        
        bool  servicemanager::operation_impl(appidtype app, int oper) {
            
            DEBUG_VAL2_DVNCI(app, oper)
            INP_SHARE_LOCK(memlock());
            if (exists(app)){
            switch (oper) {
                case SERVICE_OPEATION_START:{
                    DEBUG_VAL2_DVNCI(oper, name(app))
                    if (servicestatus(name(app)) != SERVICE_STATUS_STOPED) return false;
                    DEBUG_VAL2_DVNCI(oper, name(app))
                    return startservice(name(app));}
                case SERVICE_OPEATION_STOP:{
                    if (servicestatus(name(app)) != SERVICE_STATUS_RUN) return false;
                    return stopservice(name(app));}}}
            return false;}
        
}





