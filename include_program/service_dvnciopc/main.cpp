/* 
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 9 Январь 2010 г., 1:20
 */


#include <stdlib.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/filesystem.hpp>


#include "kernel/constdef.h"
#include "kernel/utils.h"
#include "kernel/systemutil.h"
#include "kernel/serviceapp.h"
#include "kernel/rpcioclient.h"
#include "kernel/serviceapp.h"
#include "kernel/service.h"
#include "kernel/interface_proccesstmpl.h"

#include "dvnci_opc_subsciptor.h"


using namespace std;
using namespace dvnci;
using namespace dvnci::opc;



dvnci::executable_ptr         dvnci::mainserv;
std::string                   dvnci::dvnciservicename=NS_OPC_SERVICE_NAME;
fspath                        basepath;

typedef group_proccessor_templ<dvnci_opc_subsciptor>     groupopc;

class opc_service : public uniintfservice<groupopc> {

public:
    opc_service() : uniintfservice<groupopc>(basepath,
            NS_OPC_SERVICE){};};


int main(int argc, char* argv[]){
  std::string quit_in;
  basepath=dvnci::getlocalbasepath();
  dvnci::mainserv= executable_ptr(new opc_service());
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

