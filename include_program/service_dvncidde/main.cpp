/* 
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 9 Январь 2010 г., 1:20
 */

#include "kernel/constdef.h"
#include "kernel/systemutil.h"
#include "kernel/serviceapp.h"
#include "kernel/service.h"
#include "kernel/interface_proccesstmpl.h"

#include "dvnci_dde_subsciptor.h"


using namespace std;
using namespace dvnci;
using namespace dvnci::dde;



dvnci::executable_ptr         dvnci::mainserv;
std::string                   dvnci::DVNCI_SERVICE_NAME=NS_DDE_SERVICE_NAME;
dvnci::appidtype              dvnci::DVNCI_SERVICE_APPID= NS_DDE_SERVICE;
fspath                        basepath;

typedef group_proccessor_templ<dvnci_dde_subsciptor>     groupdde;

class net_service : public uniintfservice<groupdde> {

public:
    net_service() : uniintfservice<groupdde>(basepath,
            NS_DDE_SERVICE){};};


int main(int argc, char* argv[]){
  std::string quit_in;
  basepath=dvnci::getlocalbasepath();
  dvnci::mainserv= executable_ptr(new net_service());
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

