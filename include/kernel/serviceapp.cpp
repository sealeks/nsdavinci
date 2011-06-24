
#include <kernel/serviceapp.h>
#include <stdio.h>

namespace dvnci {
boost::thread th;


    int serviceargumentparser(int argc, char** argv) {
        DVNCI_FULL_EXEC_PATH = argc>0 ? argv[0] : "";
        DEBUG_VAL_DVNCI(DVNCI_FULL_EXEC_PATH);
        DEBUG_VAL_DVNCI(applicationservicename);
        int oper = getserviceoperation(argc>1 ? argv[1] : "");
        DEBUG_VAL_DVNCI(oper);
        switch (oper) {
            case SERVICE_OPEATION_INSTALL:{
                installservice(DVNCI_SERVICE_APPID, DVNCI_SERVICE_NAME);
                break;}
            case SERVICE_OPEATION_UNINSTALL:{
                uninstallservice(DVNCI_SERVICE_APPID);
                break;}
            case SERVICE_OPEATION_APP:{
                return SERVICE_OPEATION_APP;}
            case SERVICE_OPEATION_START:{
                startmain(argc, argv);
                break;}
            default: startmain(argc, argv);}
        return oper;}

    int getserviceoperation(std::string val) {
        lower_and_trim(val);
        if (val == "/install") return SERVICE_OPEATION_INSTALL;
        if (val == "/uninstall") return SERVICE_OPEATION_UNINSTALL;
        if (val == "/stop") return SERVICE_OPEATION_STOP;
        if (val == "/start") return SERVICE_OPEATION_START;
        if (boost::algorithm::iends_with(val, "/app")) return SERVICE_OPEATION_APP;
        return SERVICE_OPEATION_START;}

    bool startservice() {

        if (mainserv) {
            th = boost::thread(mainserv);
            th.join();}
        return true;}

    bool stopservice() {

        if (mainserv) {
            mainserv.terminate();
            th.join();}
        return true;}




}



#if defined(_DVN_WIN_)
#include <kernel/serviceapp_win.cpp>
#elif defined(_DVN_LIN_)
#include <kernel/serviceapp_lin.cpp>
#else
#error No define service menager
#endif


