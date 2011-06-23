/* 
 * File:   nix_demon_templ.h
 * Author: sealeks
 *
 * Created on 22 Июнь 2011 г., 17:39
 */

#ifndef NIX_DEMON_TEMPL_H
#define	NIX_DEMON_TEMPL_H

#include <kernel/constdef.h>

#if defined(_DVN_LIN_)

#include <kernel/utils.h>
#include <kernel/systemutil.h>

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <syslog.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string>
#include <fstream>

namespace dvnci {
    
  extern std::string LOG_DEMON_FILE;
  
    
  struct process_signal_args {
	void(*reread_func_t)();
	void(*terminate_func_t)();
	sigset_t* mask;
	volatile int running;};      
    
   int  startdemonlog();
   int  writedemonlog(const std::string& msg,  const std::string& opt = ""); 
   
   void demonize(const std::string& cmd);
   int  already_running(const std::string& cmd);
   void* process_signal_thr(void* arg);
   
   
   

    
    
}

#endif

#endif	/* NIX_DEMON_TEMPL_H */

