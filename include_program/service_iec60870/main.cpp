#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/service.h>
#include <kernel/interface_proccesstmpl.h>

#include "extiec60850intf.h"


using namespace std;
using namespace dvnci;
using namespace dvnci::external;



dvnci::executable_ptr     dvnci::mainserv;
std::string                  dvnci::DVNCI_SERVICE_NAME=NS_IEC60850_SERVICE_NAME;
dvnci::appidtype      dvnci::DVNCI_SERVICE_APPID= NS_IEC60850_SERVICE;
fspath                        basepath;


typedef externalintf_executor<exiec60850intf>                                             iec60850executor;
typedef group_proccessor_templ<iec60850executor , TYPE_SIMPL | TYPE_TEXT >    groupiec60850;


class net_service : public uniintfservice < groupiec60850 > {

public:
    net_service() : uniintfservice<groupiec60850>(basepath,
            NS_IEC60850_SERVICE){}

protected:

    virtual bool initialize_impl() {
      uniintfservice<groupiec60850>::initialize_impl();
      return true;}

    virtual bool uninitialize_impl() {
        uniintfservice<groupiec60850>::uninitialize_impl();
        if (server) server->terminate();
        //th_server.join();
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

