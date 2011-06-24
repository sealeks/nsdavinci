


#include <kernel/nix_demon_templ.h>



namespace dvnci {


    void servicemain(int argc, char** argv);
    void servicecontrol(int dwControlCode);
    void setsomeservicestatus(int dwCurrentState, int dwWin32ExitCode, int dwWaitHint);
    
    void demon_reread_func() {}

    void demon_terminate_func() {
	stopservice();}

    int  startmain(int argc, char** argv) {
        
	sigset_t mask;
	struct sigaction sa;
	pthread_t tid;
	process_signal_args thread_args;

	std::string demon_execute_cmd = (NULL == strrchr(argv[0], '/')) ? argv[0] : strrchr(argv[0], '/')+1;
        
        std::string tmpdir="";
        try{
        tmpdir = boost::filesystem::temp_directory_path().string();}
        catch(...){
            tmpdir="";}
        
                
        dvnci::LOG_DEMON_FILE = (!tmpdir.empty()) ? tmpdir + "/" + demon_execute_cmd + ".log" : "";
        
        startdemonlog();        
        writedemonlog("Start demonaze");
	demonize(demon_execute_cmd);

	if ( already_running(demon_execute_cmd) ) {
		writedemonlog("daemon "+ demon_execute_cmd +" already running");
		exit(EXIT_FAILURE);}

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
        
	if ( sigaction(SIGHUP, &sa, NULL) < 0 ) {
		writedemonlog("sigaction error");
		exit(EXIT_FAILURE);}

	sigfillset(&mask);
	if ( 0 != pthread_sigmask(SIG_BLOCK, &mask, NULL) ) {
		writedemonlog("pthread_sigmask error");
		exit(EXIT_FAILURE);}

	thread_args.mask = &mask;
	thread_args.running = 1;
	/**  */
	thread_args.reread_func_t = demon_reread_func;
	/**  */
	thread_args.terminate_func_t = demon_terminate_func;
	/**  */
	if ( pthread_create(&tid, NULL, process_signal_thr, &thread_args) ) {
		writedemonlog("can`t create thread");
		exit(EXIT_FAILURE);
	}

	/* тут код программы */
        
        writedemonlog("start deamon test");

        startservice();
    
        writedemonlog("test stop loop");
        return (EXIT_SUCCESS) ;};

    void servicemain(int dwArgc, char** lpszArgv) {

       /* ssHandle = RegisterServiceCtrlHandler(dvnciservicename.c_str(), servicecontrol);
        if (!ssHandle) {
            OUTSTRVAL_DVNCI(Error registering ServiceControl, dvnciservicename)
            _getch();
            return;}
        ss.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
        setsomeservicestatus(SERVICE_START_PENDING, NO_ERROR, 4000);
        setsomeservicestatus(SERVICE_RUNNING, NO_ERROR, 0);
        startservice();*/
        return;}

    bool installservice(appidtype app, const std::string& nameservice) {
        /*SC_HANDLE hService;
        SC_HANDLE hSCManager;


        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;}

        hService = CreateService(hSCManager, nameservice.c_str(),
                nameservice.c_str(), SERVICE_ALL_ACCESS,
                SERVICE_WIN32_OWN_PROCESS, SERVICE_DEMAND_START,
                SERVICE_ERROR_NORMAL,
                pathservice.c_str(),
                NULL, NULL, NULL, NULL, NULL);
        if (!hService) {
            OUTSTRVAL_DVNCI(Cant service fo install,  nameservice )
            CloseServiceHandle(hSCManager);
            return false;}

        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        OUTSTRVAL_DVNCI(Service succesfull install, nameservice)*/
        return true;}

    bool uninstallservice(appidtype app) {

        /*SC_HANDLE hService;
        SC_HANDLE hSCManager;

        hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
        if (!hSCManager) {
            DEBUG_STR_DVNCI(Cant open Service Control Manager);
            return false;}

        hService = OpenService(hSCManager, nameservice.c_str(), SERVICE_STOP | DELETE);
        if (!hService) {
            DEBUG_STR_VAL_DVNCI(Cant open service fo uninstall , nameservice)
            CloseServiceHandle(hSCManager);
            return false;}

        if (!DeleteService(hService)) {
            CloseServiceHandle(hService);
            CloseServiceHandle(hSCManager);
            OUTSTRVAL_DVNCI(Cant service fo uninstall,  nameservice )
            return false;}


        CloseServiceHandle(hService);
        CloseServiceHandle(hSCManager);
        OUTSTRVAL_DVNCI(Service succesfull uninstall, nameservice)*/
        return true;}

    bool startservice(const std::string& nameservice) {


        return true;}

    bool stopservice(const std::string& nameservice) {

        return true;}


///////////////////////////////////////////////////

        
        
        int servicemanager::pid(appidtype app) const {
            INP_SHARE_LOCK(memlock());
            return exists(app) ? operator[](app)->pid() : 0;}  
        
        void servicemanager::pid(appidtype app, int pd) {
            INP_EXCLUSIVE_LOCK(memlock())
            if (exists(app))  
                operator[](app)->pid(pd);;}  
        
        int demon_entry_table::starttype(appidtype app) const {
            INP_SHARE_LOCK(memlock());
            return exists(app) ? operator[](app)->starttype() : 0;}
        
        void servicemanager::starttype(appidtype app, int stt) {
            INP_EXCLUSIVE_LOCK(memlock())
            if (exists(app)){
                size_type it=find(app);
                operator[](app)->starttype(stt);
                if (it!=npos) 
                    writetofile(it);}}      
        
        int servicemanager::status(appidtype app) const {
            INP_SHARE_LOCK(memlock());
            return exists(app) ? operator[](app)->status() : 0;}  
        
        void servicemanager::status(appidtype app, int sts) {
            INP_EXCLUSIVE_LOCK(memlock())
            if (exists(app))  
                operator[](app)->status(sts);}         
        

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
                    //if (servicestatus(name(app)) != SERVICE_STATUS_STOPED) return false;
                    DEBUG_VAL2_DVNCI(oper, name(app))
                    return startservice(name(app));}
                case SERVICE_OPEATION_STOP:{
                    //if (servicestatus(name(name(app))) != SERVICE_STATUS_RUN) return false;
                    return stopservice(name(app));}}}
            return false;}

}




