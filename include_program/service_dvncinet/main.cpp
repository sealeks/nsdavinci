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
#include <kernel/interface_proccesstmpl.h>

#include <custom/extnetintf.h>
#include "netserver.h"


using namespace std;
using namespace dvnci;
using namespace dvnci::external;
using namespace dvnci::external::net;



dvnci::executable_ptr         dvnci::mainserv;
std::string                   dvnci::DVNCI_SERVICE_NAME=NS_NET_SERVICE_NAME;
dvnci::appidtype              dvnci::DVNCI_SERVICE_APPID= NS_NET_SERVICE;
fspath                        basepath;


typedef externalintf_executor<extnetintf>                                              netexecutor;
typedef group_proccessor_templ<netexecutor , TYPE_SIMPL | TYPE_REPORT | TYPE_TEXT >    groupnet;


class net_service : public uniintfservice < groupnet > {

public:
    net_service() : uniintfservice<groupnet>(basepath,
            NS_NET_SERVICE){}

protected:

    virtual bool initialize_impl() {
      server = executable_ptr(new dvnci::custom::net::net_server_service(intf));
      th_server=boost::thread(server);
      uniintfservice<groupnet>::initialize_impl();
      return true;}

    virtual bool uninitialize_impl() {
        uniintfservice<groupnet>::uninitialize_impl();
        if (server) server->terminate();
        th_server.join();
        return true;}

private:

   boost::thread_group                threads;
   boost::thread                      th_server;
   executable_ptr                     server;};


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

