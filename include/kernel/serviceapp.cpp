
#include <stdio.h>
#include <conio.h>
#include <kernel/serviceapp.h>

namespace dvnci {
    

boost::thread th;


    int serviceargumentparser(int argc, char** argv) {
        for (int i = 0; i < argc; ++i) {
            switch (i) {
                case 0:{
                    boostapplicationpath = argv[0];
                    break;}
                case 1:{
                    applicationservicespec = argv[1];
                    break;}}}
        applicationservicepath = boostapplicationpath.string();
        applicationservicename = boostapplicationpath.string();
        DEBUG_VAL_DVNCI(applicationservicepath);
        DEBUG_VAL_DVNCI(applicationservicename);
        DEBUG_VAL_DVNCI(applicationservicespec);
        int oper = getserviceoperation(applicationservicespec);
        DEBUG_VAL_DVNCI(oper);
        switch (oper) {
            case SERVICE_OPEATION_INSTALL:{
                installservice(applicationservicepath, dvnciservicename);
                break;}
            case SERVICE_OPEATION_UNINSTALL:{
                uninstallservice(dvnciservicename);
                break;}
            case SERVICE_OPEATION_APP:{
                return SERVICE_OPEATION_APP;}
            case SERVICE_OPEATION_START:{
                startmain();
                break;}
            default: startmain();}
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