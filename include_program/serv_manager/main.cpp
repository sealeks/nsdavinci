/* 
 * File:   main.cpp
 * Author: sealeks
 *
 * Created on 22 Июнь 2011 г., 18:10
 */

#include <cstdlib>

#include <kernel/constdef.h>
#include <kernel/serviceapp.h>
#include <kernel/templ.h>


namespace dvnci{
extern std::string LOG_DEMON_FILE;
}

#ifndef DVNCI_NUX_SVM
#define DVNCI_NUX_SVM
#endif

dvnci::executable_ptr     dvnci::mainserv;
std::string               dvnci::DVNCI_SERVICE_NAME = "serv_manager";
dvnci::appidtype          dvnci::DVNCI_SERVICE_APPID= 0;


using namespace dvnci;
    
   
volatile int runflag = 1;

/***************************************************************************/

void reread_func() {}

void terminate_func() {
	runflag = 0;}

//std::string demon_execute_cmd = "";





namespace dvnci {

        class svmservice : public executable {

        public:


            svmservice() :
                    executable(), mntr(0) {};

            virtual ~svmservice() {}

            virtual bool operator()() {
                boost::xtime xt;
                while (!terminated()) {
                    if (init()) {
                        if  (terminated()) break;
                        if (checksevices()) {
                            writedemonlog("CHECKMAINLOOOOP");
                            addmillisec_to_now(xt, 3);}
                        else{
                            addmillisec_to_now(xt, 100);}
                        if (terminated()) break;}
                    else{
                        addmillisec_to_now(xt, 10000);}
                boost::thread::sleep(xt);}
                uninitialize();
                return true;}

        protected:


            virtual bool initialize() {
               svm_=demon_entry_factory::build(FULL_EXEC_DIR());
               writedemonlog("INITSERVISE: " + FULL_EXEC_DIR().string());
               if (!svm_) { 
                   writedemonlog("FAILINIT INITSERVISE :" + FULL_EXEC_DIR().string());
                   return false;}
               startsevices();
               mntr=svm_->monitor();
               return true;}

            virtual bool uninitialize() {
                if (!svm_) return true;
                stopsevices();
                svm_.reset();
                return true;}
            
            bool startsevices() {
              INP_SHARE_LOCK(svm_->memlock());
              for (servicemanager::struct_type_ptr it=svm_->begin();it!=svm_->end();++it){
                  if ((it->appid()) && (it->starttype()==SERVICE_RUNSTATE_AUTO))
                      startsevice(svm_->name(it->appid()));}
              return true;}
            
            bool stopsevices() {
              INP_SHARE_LOCK(svm_->memlock());
              for (servicemanager::struct_type_ptr it=svm_->begin();it!=svm_->end();++it){
                  if ((it->appid()) && (it->pid()))
                      stopsevice(it->pid());}
              return true;}
            
            bool startsevice(const std::string& nm) {
                
               writedemonlog("Start application" + nm);  
               writedemonlog("Start FULL_EXEC_DIR :" + FULL_EXEC_DIR().string());
               
               std::string exc=(FULL_EXEC_DIR() / nm.c_str()).string();
               if (!boost::filesystem::exists(exc.c_str())){
                   writedemonlog("NO find exec =" + exc);
                   return false;}
               writedemonlog("Start application execl =" + exc);
               int rslt = system(exc.c_str());
               return !rslt;}
            
            bool stopsevice(pid_t pid) {
              if (!pid) 
                  return false; 
              kill(pid, SIGTERM);
              return true;}
            
            bool checksevices() {
              INP_SHARE_LOCK(svm_->memlock());
              if (mntr==svm_->monitor()) return false;
              for (servicemanager::struct_type_ptr it=svm_->begin();it!=svm_->end();++it){
                  if ((it->appid()) && (it->waitstate())){
                      switch(it->waitstate()) {
                         case demon_item::RUN_WAIT_STATE: {
                             startsevice(svm_->name(it->appid()));}
                         case demon_item::TERM_WAIT_STATE: {
                             stopsevice(svm_->pid(it->appid()));}}
                      svm_->waitstate(it->appid(),0);}}
                      mntr=svm_->monitor();
                      return true;}                                    

        protected:
            servicemanager_ptr svm_;
            volatile int mntr;
         };}




int main(int argc, char** argv) {
    

    
    std::string quit_in;
    
    std::string  SERVMAN_REALPATH="";
    
    fspath testpath = argc > 0 ? argv[0] : "";
    
    if ((!testpath.string().empty()) && (argc>0)) {
        if (testpath.is_absolute()){
            SERVMAN_REALPATH=testpath.string();}
        else{
            char buf[PATH_MAX];
	    char *p;
            if (!(p = realpath(argv[0], buf)))
                {;}
            else{
                testpath=p;
                SERVMAN_REALPATH=testpath.string();}
                SERVMAN_REALPATH=SERVMAN_REALPATH;}}
    else{
        SERVMAN_REALPATH=testpath.string();}
    
    
    char  *generatearg[]={(char*)SERVMAN_REALPATH.c_str(), argc > 1 ? argv[1] : NULL };
    

    mainserv = executable_ptr(new svmservice());
    
#ifndef DVNCI_DEDUG
    if (serviceargumentparser( (argc > 1 ? 2 : 1), (char**)&generatearg) == SERVICE_OPEATION_APP) {
#else
    appargumentparser((argc > 1 ? 2 : 1), (char**)&generatearg);
#endif    
        try {
            DEBUG_STR_DVNCI(start app)
            boost::thread th = boost::thread(mainserv);
            while ((std::cin >> quit_in)  && ((quit_in != "q") && (quit_in != "Q")));
            mainserv.terminate();
            th.join();}
        catch (std::exception& err) {
            DEBUG_VAL_DVNCI(err.what());}
#ifndef DVNCI_DEDUG
    /**/;}
#endif
    DEBUG_STR_DVNCI(FIN)
    return (EXIT_SUCCESS);}


