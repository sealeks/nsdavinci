/* 
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 9 Январь 2010 г., 1:20
 */





#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/service.h>
#include <kernel/driver_proccesstmpl.h>
#include <kernel/error.h>
#include "iec60870_detail.h"

using namespace std;
using namespace dvnci;
using namespace dvnci::driver;


dvnci::executable_ptr dvnci::mainserv;
std::string dvnci::DVNCI_SERVICE_NAME = NS_IEC60870_SERVICE_NAME;
dvnci::appidtype dvnci::DVNCI_SERVICE_APPID = NS_IEC60870_SERVICE;
fspath basepath;


typedef device_link_executor < iec60870_device_service, iec60870_block_model, iec60870_metalink_checker > iec60870_executor;
typedef group_proccessor_templ< iec60870_executor, TYPE_SIMPL > groupiec60870;

class iec60870_service : public linkdriverservice<groupiec60870> {
public:

    iec60870_service() : linkdriverservice<groupiec60870>(basepath,
    NS_IEC60870_SERVICE) {
    };
};

int main(int argc, char* argv[]) {
    std::string quit_in;
    basepath = dvnci::getlocalbasepath();
    dvnci::mainserv = executable_ptr(new iec60870_service());
#ifndef DVNCI_DEDUG
    if (serviceargumentparser(argc, argv) == SERVICE_OPEATION_APP) {
#endif
        try {
            DEBUG_STR_DVNCI(start app)
            boost::thread th = boost::thread(mainserv);
            while ((std::cin >> quit_in) && ((quit_in != "q") && (quit_in != "Q")));
            mainserv.terminate();
            th.join();
        } catch (std::exception& err) {
            DEBUG_VAL_DVNCI(err.what());
        }
#ifndef DVNCI_DEDUG
    }
#endif
    DEBUG_STR_DVNCI(FIN)
    return (EXIT_SUCCESS);
}

