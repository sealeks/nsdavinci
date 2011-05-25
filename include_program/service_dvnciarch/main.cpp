/* 
 * File:   main.cpp
 * Author: Serg
 *
 * Created on 21 Июнь 2010 г., 15:08
 */

//#define IS_DVNCI_SERVICE

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/service.h>
#include <kernel/system_proccesstmpl.h>

#include <dbaccess/dbconnectionfactory.h>
#include "reporttype_executor.h"
#include "dbwriter.h"


using namespace dvnci;
using namespace std;
using namespace dvnci::database;

dvnci::indx GPRSS_REPORTTYPE=-2;

dvnci::executable_ptr         dvnci::mainserv;
std::string                   dvnci::dvnciservicename=NS_PERSISTENCE_SERVICE_NAME;
fspath                        basepath;



class archiveservice : public basisservice {

   typedef system_executor<reporttype_executor>                                       report_executor;
   typedef group_proccessor_templ<report_executor,    TYPE_REPORT>                    allreporttag;

   typedef callable_shared_ptr<dvnci::database::db_writer>                            dbwriter_ptr;
   typedef callable_shared_ptr<dvnci::database::trend_observer>                       observer_ptr;

public:

    archiveservice() : basisservice(basepath,
            (sIMMILog | sIMMITagManage | sIMMIGroupManage | sIMMIDBManage ),
            NS_PERSISTENCE_SERVICE) , provider_database(0), connection_string(""), dbdrv() {}

protected:

    virtual bool initialize_impl() {

       setdbdriver();

       if (!dbdrv) return false;

       if (!dbdrv->isconnected()) dbdrv->connect();
       if (!dbdrv->isconnected()) return false;

       writer = dbwriter_ptr(new dvnci::database::db_writer(intf));
       th_writer=boost::thread(writer);

       observer = observer_ptr(new dvnci::database::trend_observer(intf,writer.operator ->()));
       th_observer = boost::thread(observer);

       group_proccessor_ptr tmp=group_proccessor_ptr(new allreporttag(intf));
       threads_map.insert(idtype_threads_map_pair(GPRSS_REPORTTYPE,tmp));
       th_map.insert(idtype_thread_pair(GPRSS_REPORTTYPE,threadgroup_ptr(new boost::thread(tmp))));

       return true;}

    virtual bool uninitialize_impl() {
        if (observer) observer->terminate();
        th_observer.join();
        if (writer) writer->terminate();
        th_writer.join();
        return true;}

   void setdbdriver() {
        if (intf) {
            std::string con_str = intf->conf_property(NS_CNFG_DBCONSTR);
            dbprovtype  provider_db = intf->conf_numproperty<dbprovtype>(NS_CNFG_DBMANAGER);
            if ((provider_database != provider_db) || (connection_string != con_str)) {
                dbdriver_ptr newdrv;
                if (dbdrv) {
                    THD_EXCLUSIVE_LOCK(dbdrv);
                    if  (dbdrv->isconnected())
                         dbdrv->disconnect();
                    if ((provider_db != 0) && (!con_str.empty()))
                        newdrv = bdconnectionfactory::build(provider_db, con_str);
                    dbdrv.swap(newdrv);
                    reporttype_executor::setdbdriver(dbdrv);
                    db_writer::setdbdriver(dbdrv);}
                else {
                    if ((provider_db != 0) && (!con_str.empty()))
                        newdrv = bdconnectionfactory::build(provider_db, con_str);
                    dbdrv.swap(newdrv);
                    if (dbdrv) {
                        THD_EXCLUSIVE_LOCK(dbdrv);
                        reporttype_executor::setdbdriver(dbdrv);
                        db_writer::setdbdriver(dbdrv);}}}
            provider_database = provider_db;
            connection_string = con_str;}}

    virtual void execute_thread(indx id) {}

    virtual void serv_func(num32  mess,indx id, indx some){
      switch (mess){
          case MSG_DVNCLOG: { 
              if (observer){
                  if (some){
                      observer->add_trend(id);}
                  else{
                      observer->remove_trend(id);}}
              break;}
          case MSG_DVNCICONNSTRCH:{
              setdbdriver();}
          default: basisservice::serv_func(mess,id, some);}}


private:

    dbprovtype     provider_database;
    std::string    connection_string;
    dbwriter_ptr   writer;
    boost::thread  th_writer;
    observer_ptr   observer;
    boost::thread  th_observer;
    dbdriver_ptr dbdrv;};





int main(int argc, char** argv) {
  std::string quit_in;
  basepath=dvnci::getlocalbasepath();
  DEBUG_VAL_DVNCI(basepath.string())
#ifdef DVNCI_DEDUGFILE
    ofstream file("C:\\aaaaaaaaaaaaaaaaaaaa.txt");
    std::cout.rdbuf(file.rdbuf());
#endif
  mainserv= executable_ptr(new archiveservice());
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

