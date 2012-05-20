/*
 * File:   main.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * 
 */

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/service.h>
#include <kernel/interface_proccesstmpl.h>
#include <kernel/expression.h>
#include <kernel/factory.h>
#include <kernel/memfile.h>
#include <kernel/short_value.h>


#include <custom/gui_executor.h>

using namespace std;
using namespace dvnci;
using namespace dvnci::custom;

dvnci::executable_ptr         dvnci::mainserv;
std::string                   dvnci::DVNCI_SERVICE_NAME="gui";
dvnci::appidtype              dvnci::DVNCI_SERVICE_APPID= 0;
fspath                        basepath;

class test_expression_listener : public expression_listener{
    public:
        virtual void event(const short_value& val){
            std::cout << "event value =" << val.value<std::string>() << std::endl;};};  
            
class test_alarm_listener : public alarms_listener{
    public:
		test_alarm_listener() : alarms_listener("m1"){}
        virtual void event(const vect_alarms_row& val){
            std::cout << "alarm event size =" << val.size() << std::endl;
            for (vect_alarms_row::const_iterator it = val.begin(); it != val.end(); ++it) {
                std::cout  << it->time << " " << it->tag << " " << it->text << " "<< std::endl;
            }};}; 
            
class test_journal_listener : public journal_listener{
    public:
        virtual void event(const vect_journal_row& val){
            std::cout << "journal event size =" << val.size() << std::endl;
            for (vect_journal_row::const_iterator it = val.begin(); it != val.end(); ++it) {
                std::cout  << it->time << " " << it->tag << " " << it->text << " "<< std::endl;
            }};};     
            
class test_debug_listener : public debug_listener{
    public:
        virtual void event(const vect_debug_row& val){
            std::cout << "debug event size =" << val.size() << std::endl;
            for (vect_debug_row::const_iterator it = val.begin(); it != val.end(); ++it) {
                std::cout  << it->time << " " << it->message << " " << it->level << " "<< std::endl;
            }};};             
            
class test_trend_listener : public trend_listener{
    public:
        test_trend_listener(const str_vect& tgs, num64 histmilisec = 0): trend_listener(tgs, histmilisec){}
        virtual void event(const short_values_table& val){
            //std::cout << "alarm event size =" << val.size() << std::endl;
            std::cout << "#############################"  << std::endl;
            for (short_values_table::const_iterator it = val.begin(); it != val.end(); ++it) {
                    const short_values_row& row=*it;
                    std::cout << "--------------------------------"  << std::endl;
                    std::cout << "tag =" << row.first.first <<  " start =" << row.first.second << std::endl;
                    for (short_value_vect::const_iterator itval = row.second.begin(); itval != row.second.end(); ++itval) {                
                            std::cout  << itval->time() << " - " << itval->value<std::string>() << std::endl;}
            }};};    
                    
  typedef gui_executor<tagsbase >                                        test_gui_executor;
  typedef callable_shared_ptr<test_gui_executor>                         test_gui_executor_ptr;                    
                    
   struct caller{
      caller(test_gui_executor_ptr e): terminate_(true), ex(e){}
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
	   test_gui_executor_ptr ex;
  };     

   typedef callable_shared_ptr<caller>                         caller_ptr;
          



  struct guichrome_terminated_thread{
	  guichrome_terminated_thread(test_gui_executor_ptr inf_): inf(inf_),th(inf_) {}

	  ~guichrome_terminated_thread(){
	     inf.terminate();
         th.join();
	     inf.reset();}

  private:
	  test_gui_executor_ptr inf;
	  boost::thread th;
  };
  




int main(int argc, char* argv[]){
	std::string quit_in;{
            
 std::cout << "journal event size ="  << std::endl;           
            
  basepath=dvnci::getlocalbasepath();
  
  std::cout << "basepath ="  <<  basepath << std::endl;  
  
  
 str_vect tgs;
  tgs.push_back("r1::a");
  tgs.push_back("r2::ah");
  tgs.push_back("r3::ah");
  tgs.push_back("r4::ah");
  tgs.push_back("r5::ah");
  
  expression_listener_ptr  lsnr = expression_listener_ptr( new test_expression_listener());
  expression_listener_ptr  lsnr1 = expression_listener_ptr( new test_expression_listener());
  alarms_listener_ptr  lsnre = alarms_listener_ptr( new test_alarm_listener());
  journal_listener_ptr  lsnrj = journal_listener_ptr( new test_journal_listener());
  debug_listener_ptr  lsnrd = debug_listener_ptr( new test_debug_listener());
  
  trend_listener_ptr  lsnt = trend_listener_ptr( new test_trend_listener(tgs,100000));
  
  tagsbase_ptr kintf = dvnci::krnl::factory::build(basepath,  0);
  
  std::cout << "intf ="  <<  ((size_t)kintf) << std::endl;
  
  test_gui_executor_ptr ex = test_gui_executor_ptr( new test_gui_executor(kintf));
  

  
  //dynamic_cast<test_gui_executor*>(ex.operator->())->regist_expr_listener("r1::a", lsnr);
  //ex->regist_expr_listener("(m1::c4 ) ? '#motral' : ((m1::c3) ? '#motroff'  : ((m1::c2) ? '#motron'  : '#motranim')", lsnr1); 
    //ex->regist_expr_listener("m1::c1", lsnr1);
  // ex->regist_trend_listener(lsnt);
  //ex->regist_alarm_listener(lsnre); 
  ex->regist_journal_listener(lsnrj);
  //ex->regist_debug_listener(lsnrd);
  


  
 
  

  try {
       DEBUG_STR_DVNCI(start app);
       guichrome_terminated_thread termth(ex);
	   {caller_ptr  clr = caller_ptr( new caller(ex));
       boost::thread th2 = boost::thread(clr);
	   
	   while ((std::cin >> quit_in)  && ((quit_in!="q") && (quit_in!="Q")));
	   clr.terminate();
	   th2.join();}

       //ex.terminate();
	   
       //th.join();
	   
  }
  catch(std::exception& err){
	  std::cout <<err.what() << std::endl;;}}
  //ex.reset();
  DEBUG_STR_DVNCI(FIN)
  return (EXIT_SUCCESS);}