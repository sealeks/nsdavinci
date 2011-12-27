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
        virtual void event(const vect_alarms_row& val){
            std::cout << "alarm event size =" << val.size() << std::endl;
            for (vect_alarms_row::const_iterator it = val.begin(); it != val.end(); ++it) {
                std::cout  << it->time << " " << it->tag << " " << it->text << " "<< std::endl;
            }};}; 
            
class test_trend_listener : public trend_listener{
    public:
        virtual bool event(const std::vector<short_value>& val){
            //std::cout << "alarm event size =" << val.size() << std::endl;
            for (std::vector<short_value>::const_iterator it = val.begin(); it != val.end(); ++it) {
                std::cout  << it->time() << " - " << it->value<std::string>() << std::endl;
            }
		    return true;};};    
                    
  typedef gui_executor<tagsbase >                                        test_gui_executor;
  typedef callable_shared_ptr<test_gui_executor>                         test_gui_executor_ptr;                    
                    
   struct caller{
      caller(test_gui_executor_ptr e): ex(e){}
      void operator()(){
          while(true){
          boost::xtime xt_loop;
          ex->call();
          addmillisec_to_now(xt_loop, 1000);
          boost::thread::sleep(xt_loop);}
      }
      test_gui_executor_ptr ex;
  };                   
                    

int main(int argc, char* argv[]){
  std::string quit_in;
  basepath=dvnci::getlocalbasepath();
  
  
  

  
  expression_listener_ptr  lsnr = expression_listener_ptr( new test_expression_listener());
  expression_listener_ptr  lsnr1 = expression_listener_ptr( new test_expression_listener());
  alarms_listener_ptr  lsnre = alarms_listener_ptr( new test_alarm_listener());
  
  trend_listener_ptr  lsnt = trend_listener_ptr( new test_trend_listener());
  
  tagsbase_ptr kintf = dvnci::krnl::factory::build(basepath,  0);
  
  test_gui_executor_ptr ex = test_gui_executor_ptr( new test_gui_executor(kintf));
  
  //dynamic_cast<test_gui_executor*>(ex.operator->())->regist_expr_listener("r1::a", lsnr);
  //ex->regist_expr_listener("(m1::c4 ) ? '#motral' : ((m1::c3) ? '#motroff'  : ((m1::c2) ? '#motron'  : '#motranim')", lsnr1); 
  ex->regist_expr_listener("(m1::c4 ) ? '#motral' : '#motroff'", lsnr1);
  ex->regist_trend_listener("r1::a", lsnt);
  //ex->regist_alarm_listener(lsnre); 
  

  
 
  

  try {
       DEBUG_STR_DVNCI(start app)
       boost::thread th = boost::thread(ex);
       boost::thread th2 = boost::thread(caller(ex));
       while ((std::cin >> quit_in)  && ((quit_in!="q") && (quit_in!="Q")));
       ex.terminate();
       th.join();
  }
  catch(std::exception& err){
       DEBUG_VAL_DVNCI(err.what());}

  DEBUG_STR_DVNCI(FIN)
  return (EXIT_SUCCESS);}