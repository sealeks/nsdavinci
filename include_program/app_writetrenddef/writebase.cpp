//
// Copyright (C) 2004-2008 Maciej Sobczak, Stephen Hutton
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/factory.h>

#include <dbaccess/dbconnectionfactory.h>
#include <dbaccess/db_task_executor.h>

dvnci::tagsbase_ptr intf;

using namespace std;
using namespace dvnci;
using namespace dvnci::database;


namespace dvnci {
    namespace database {

        class connect_db_task_test : public connect_db_task {
        public:

            connect_db_task_test(num32 provider,const std::string& connectstring) : connect_db_task(provider,connectstring) {
            };
            
            virtual void event(const str_trenddef_map& val, dvnci::ns_error error) {
                std::cout  << " error = " << error << std::endl;
                      for (str_trenddef_map::const_iterator itval = val.begin(); itval != val.end(); ++itval) {                
                            std::cout  <<  itval->first << " - " << itval->second.cod << std::endl;}                
            }
        };



        class trend_db_task_test : public trend_db_task {
        public:

            trend_db_task_test(const str_set& tag, dvnci::datetime start,
                    dvnci::datetime stop) : trend_db_task(tag,start,stop){
            };
            
            virtual void event(const result_trend_pair_map& val, dvnci::ns_error error) {
                std::cout  << " error = " << error << std::endl;
                     for (result_trend_pair_map::const_iterator it = val.begin(); it != val.end(); ++it) {  
                     std::cout  << " ------------------------------------------------------------------------------- " << std::endl;    
                     std::cout  << " tag = " << it->first.name << " min = " << it->first.mineu << " nax = " << it->first.maxeu << std::endl;    
                     for (dt_val_map::const_iterator itval = it->second->begin(); itval != it->second->end(); ++itval) {                
                            std::cout  << local_to_utc( itval->first) << " - " << itval->second << std::endl;}}            
            }


        };
        
        
        class select_db_task_test : public select_db_task {
        public:

            select_db_task_test(const std::string& req) : select_db_task(req){
            };
            
            virtual void event(const sql_result_ptr& val, dvnci::ns_error error) {
                     std::cout  << " error = " << error << std::endl; 
                     std::cout  << "  " << "  " << std::endl;
                     std::cout  << " ------------------------------------------------------------------------------- " << std::endl;
                     for (sql_header_vect::const_iterator it = val->first.begin(); it != val->first.end(); ++it)
                         std::cout  << "  " << it->first << "(" << it->second << ")";
                     std::cout  << std::endl;
                     std::cout  << " ------------------------------------------------------------------------------- " << std::endl; 
                     for (str_table::const_iterator itv = val->second.begin(); itv != val->second.end(); ++itv){
                         for (str_vect::const_iterator it = itv->begin(); it != itv->end(); ++it)
                         std::cout  << "  " << *it;
                                              std::cout  << std::endl;
                     }}

        };
        
        class select_db_journal_task_test : public select_db_journal_task {
        public:

            select_db_journal_task_test(dvnci::datetime start,
                    dvnci::datetime stop, const std::string& filter="") : select_db_journal_task(start,stop,filter){
            };
            
            virtual void event(const vect_journal_row_ptr& val, dvnci::ns_error error) {
                std::cout  << " error = " << error << std::endl;
                     for (vect_journal_row::const_iterator it = val->begin(); it != val->end(); ++it) {  
                     std::cout  << " ------------------------------------------------------------------------------- " << std::endl;    
                     std::cout  << " cod = " << it->index<< " tag = " << it->tag << " text = " << it->text << std::endl;}            
            }


        };        
        
        
    }
}


struct caller{
      caller(db_task_executor_ptr e): terminate_(true), ex(e){}
      ~caller(){
	     std::cout << "caller destructor" << std::endl;};
      bool operator()(){
          while(terminate_){
          boost::xtime xt_loop;
          ex->call();
          addmillisec_to_now(xt_loop, 1000);
          boost::thread::sleep(xt_loop);}
		  return true;
      }
	  void terminate(){
		  terminate_=false;
	  }
   private:
	   bool terminate_;
	   db_task_executor_ptr ex;
  };
  
 typedef callable_shared_ptr<caller>                         caller_ptr;
 
 
   struct dbchrome_terminated_thread{
	  dbchrome_terminated_thread(db_task_executor_ptr inf_): inf(inf_),th(inf_) {}

	  ~dbchrome_terminated_thread(){
	     inf->terminate();
         th.join();}

  private:
	  db_task_executor_ptr inf;
	  boost::thread th;
  };


int main(int argc, char** argv)
{
   fspath basepath=dvnci::getlocalbasepath();
   intf= dvnci::krnl::factory::build(dvnci::getlocalbasepath(), 10000, 0);

   std::string con_str=intf->conf_property(NS_CNFG_DBCONSTR);
   //num32 provider_db=intf->conf_intproperty(NS_CNFG_DBMANAGER);

   cout << " connected by "<< con_str << endl;

   dbdriver_ptr testdrv=bdconnectionfactory::build(dvnci::PROPERTY_DB_PROVIDER_POSTGRESS,con_str);
   if (testdrv){
   testdrv->connect();
   if (testdrv->isconnected()){
       cout << "is connected" << endl;



       //std::cout << testdrv->insert_trendef<dvnci::tagsbase_ptr>(intf) << std::endl;
       /*datetime tm = now();
       tm=incmonth(tm,-2);
       datetime tmr = now();
       normalizeperiod(tm,REPORTTYPE_MIN);
       boost::xtime xt;

       for (int i=0;i<1000;i++){
           boost::xtime_get(&xt, boost::TIME_UTC);
           xt.sec += 1;
           tm = now();
           tm=incmonth(tm,-2);
           std::cout << tm <<" " <<testdrv->insert_report(1, REPORTTYPE_MIN, 0 , tm)   << std::endl;
           boost::thread::sleep(xt);}*/
       

   }}
   
   std::string quit_in;
   connect_db_task_ptr  connlist = connect_db_task_ptr( new connect_db_task_test(dvnci::PROPERTY_DB_PROVIDER_POSTGRESS,con_str));
   db_task_executor_ptr func = db_task_executor_ptr(new db_task_executor(connlist));
   dbchrome_terminated_thread termth(func);
   caller_ptr  clr = caller_ptr( new caller(func));
   boost::thread th2 = boost::thread(clr);
   
   	   while ((std::cin >> quit_in)  && ((quit_in!="q") && (quit_in!="Q"))){
               if (quit_in!=""){
                   /*str_set keys;
                   keys.insert("sys::p6");
                   keys.insert("sys::p5");
                   trend_db_task_ptr tst = trend_db_task_ptr( new trend_db_task_test(keys, incday(now(), -4), now()));*/
                   /*select_db_task_ptr tst = select_db_task_ptr( new select_db_task_test("select * from trenddef"));
                   func->insert_select_task(tst);*/
                   select_db_journal_task_ptr tst = select_db_journal_task_ptr( new select_db_journal_task_test(incday(now(), -4), now()));
                   func->insert_journal_task(tst);
               }
           }
	   clr.terminate();
	   th2.join();

   return EXIT_FAILURE;
}
