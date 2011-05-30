/* 
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 9 Январь 2010 г., 1:20
 */


#include <kernel/constdef.h>
#include <kernel/error.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/service.h>
#include <kernel/driver_proccesstmpl.h>
#include "koyo_detail.h"

using namespace std;
using namespace dvnci;
using namespace dvnci::driver;


dvnci::executable_ptr         dvnci::mainserv;
std::string                   dvnci::dvnciservicename=NS_KOYO_SERVICE_NAME;
fspath                        basepath;


typedef device_link_executor< koyo_device_service, koyo_block_model >                        koyo_executor;
typedef group_proccessor_templ< koyo_executor, TYPE_SIMPL >                                      groupkoyo;

class koyo_service : public linkdriverservice<groupkoyo> {

public:
    koyo_service() : linkdriverservice<groupkoyo>(basepath,
            NS_KOYO_SERVICE){};};


int main(int argc, char* argv[]){
  std::string quit_in;
  basepath=dvnci::getlocalbasepath();
  dvnci::mainserv= executable_ptr(new koyo_service());
  #ifndef DVNCI_DEDUG
  if (serviceargumentparser(argc,argv)==SERVICE_OPEATION_APP){
  #endif
  try {
       DEBUG_STR_DVNCI(start app)
       boost::thread th = boost::thread(mainserv);
       while ((std::cin >> quit_in)  && ((quit_in!="q") && (quit_in!="Q")));
       mainserv.terminate();
       th.join();}
  catch(std::exception& err){
       DEBUG_VAL_DVNCI(err.what());}
  #ifndef DVNCI_DEDUG
    }
  #endif
  DEBUG_STR_DVNCI(FIN)
  return (EXIT_SUCCESS);}

