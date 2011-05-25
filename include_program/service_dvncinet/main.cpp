/* 
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 9 Январь 2010 г., 1:20
 */

#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/service.h>

#include <kernel/interface_proccesstmpl.h>

#include "netserver.h"

using namespace dvnci;
using namespace std;
using namespace dvnci::net;

//std::string remote_port=DEFAULT_REMOTE_PORT;


using boost::asio::ip::tcp;

dvnci::executable_ptr         dvnci::mainserv;
std::string                   dvnci::dvnciservicename=NS_NET_SERVICE_NAME;
fspath                        basepath;

typedef dvnci::net::dvnci_net_subsciptor                                         net_executor;
typedef group_proccessor_templ<net_executor>                                     groupnet;

class net_service : public uniintfservice < groupnet > {

public:
    net_service() : uniintfservice<groupnet>(basepath,
            (sIMMITagManage | sIMMIGroupManage),
            NS_NET_SERVICE){}

protected:

    virtual bool initialize_internal() {
      server = executable_ptr(new net_server_service(intf));
      th_server=boost::thread(server);
      //uniintfservice<groupnet>::initialize_internal();
      return true;}

    virtual bool uninitialize_internal() {
        //uniintfservice<groupnet>::uninitialize_internal();
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

