/* 
 * File:   main.cpp
 * Author: sealeks
 *
 * Created on 22 Июнь 2011 г., 18:10
 */

#include <cstdlib>

#include <kernel/constdef.h>
#include <kernel/nix_demon_templ.h>

namespace dvnci{
extern std::string LOG_DEMON_FILE;
}


using namespace dvnci;
    
   

volatile int runflag = 1;

/***************************************************************************/

void reread_func() {}

void terminate_func() {
	runflag = 0;}

//std::string demon_execute_cmd = "";




int main(int argc, char** argv) {
    
        
        
	sigset_t mask;
	struct sigaction sa;
	pthread_t tid;
	process_signal_args thread_args;

	std::string demon_execute_cmd = (NULL == strrchr(argv[0], '/')) ? argv[0] : strrchr(argv[0], '/')+1;
        
        std::string tmpdir="";
        try{
        tmpdir = boost::filesystem::temp_directory_path().string();}
        catch(...){
            tmpdir="";}
        

        
                
        dvnci::LOG_DEMON_FILE = (!tmpdir.empty()) ? tmpdir + "/" + demon_execute_cmd + ".log" : "";
        
        startdemonlog();        
        writedemonlog("Start demonaze");
	demonize(demon_execute_cmd);

	if ( already_running(demon_execute_cmd) ) {
		writedemonlog("daemon "+ demon_execute_cmd +" already running");
		exit(EXIT_FAILURE);
	}

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
        
	if ( sigaction(SIGHUP, &sa, NULL) < 0 ) {
		writedemonlog("sigaction error");
		exit(EXIT_FAILURE);}

	sigfillset(&mask);
	if ( 0 != pthread_sigmask(SIG_BLOCK, &mask, NULL) ) {
		writedemonlog("pthread_sigmask error");
		exit(EXIT_FAILURE);}

	thread_args.mask = &mask;
	thread_args.running = 1;
	/**  */
	thread_args.reread_func_t = reread_func;
	/**  */
	thread_args.terminate_func_t = terminate_func;
	/**  */
	if ( pthread_create(&tid, NULL, process_signal_thr, &thread_args) ) {
		writedemonlog("can`t create thread");
		exit(EXIT_FAILURE);
	}

	/* тут код программы */
        
        writedemonlog("start deamon test");

    while(runflag) {

        writedemonlog("test loop");
        sleep(10);//ждем 10 минут до следующей итерации
    }
    
    writedemonlog("test stop loop");

}
