/* 
 * File:   nix_demon_templ.cpp
 * Author: sealeks
 * 
 * Created on 22 Июнь 2011 г., 17:39
 */

#include <kernel/nix_demon_templ.h>

#if defined(_DVN_LIN_)




namespace dvnci {
    
std::string LOG_DEMON_FILE = "";
    
int startdemonlog() { //функция записи строки в лог
      if (LOG_DEMON_FILE.empty()) return 1;
      std::ofstream ofs( LOG_DEMON_FILE.c_str() , std::ios::trunc );
        if (!ofs)
            return 1;    
      ofs  << "Start logging: " << datetime_to_string(now()) <<std::endl;
      return 0;}  


    
    
    
int writedemonlog(const std::string& msg,  const std::string& opt) { 
      if (LOG_DEMON_FILE.empty()) return 1;
      std::ofstream ofs( LOG_DEMON_FILE.c_str() , std::ios::in | std::ios::ate );
        if (!ofs)
            return 1;    
      ofs << datetime_to_string(now()) << " : " << msg  << (opt.empty() ? "" : ( " :" + opt)) <<std::endl;
      return 0;}    


void demonize(const std::string& cmd) {
	pid_t pid;
	struct rlimit limits;
	struct sigaction sa;

	umask(0);

	if ( getrlimit(RLIMIT_NOFILE, &limits) < 0 ) {
		writedemonlog("can`t get RLIMIT_NOFILE");
		exit(EXIT_FAILURE);}

	if ( (pid = fork()) < 0 ) {
		writedemonlog("fork error");
		exit(EXIT_FAILURE);
	} else if ( 0 != pid ) {
                writedemonlog("fork success");
		exit(0);}
        
        writedemonlog("after fork success");

	if ( (setsid()) == (pid_t)-1 ) {
		writedemonlog("setsig error");
		exit(EXIT_FAILURE);}
        
        writedemonlog("after setsid success");

	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if ( sigaction(SIGHUP, &sa, NULL) < 0 ) {
		writedemonlog("can`t ignore SIGHUP");
		exit(EXIT_FAILURE);}    
                
        writedemonlog("after sidsigaction succcess");

	if ( (pid = fork()) < 0 ) {
		writedemonlog("fork error");
		exit(EXIT_FAILURE);
	} else if ( 0 != pid ) {
		exit(0);
	}


	if ( chdir("/") < 0 ) {
		writedemonlog("can`t chdir() to /");
		exit(EXIT_FAILURE);
	}
        

	if ( limits.rlim_max == RLIM_INFINITY )
		limits.rlim_max = 1024;

	u_int32_t idx;
	for ( idx = 0; idx < limits.rlim_max; ++idx ) {
		close(idx);
	}
        
        writedemonlog("after closeloop succcess");

	int fd0 = open("/dev/null", O_RDWR);
	int fd1 = dup(0);
	int fd2 = dup(0);
        
                
        writedemonlog("after close succcess");

	//openlog(cmd.c_str(), LOG_CONS, LOG_DAEMON);
	if ( fd0 != 0 || fd1 != 1 || fd2 != 2 ) {
                writedemonlog("bad file descriptor");
		//syslog(LOG_ERR, "bad file descriptors: %d, %d, %d", fd0, fd1, fd2);
		//exit(EXIT_FAILURE);
	}
}



int already_running(const std::string& cmd) {
	char buff[4096] = "\0";
	sprintf(buff, "%s%s", "/var/run/", cmd.c_str());
	/**  */
	int fd = open(buff, O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if ( fd < 0 ) {
		writedemonlog("can`t open PID file");
		exit(EXIT_FAILURE);
	}
	if ( lockf(fd, F_TLOCK, 0) ) {
		if ( errno == EACCES || errno == EAGAIN ) {
			close(fd);
			return 1;
		}
		writedemonlog("can`t lock PID file");
		exit(EXIT_FAILURE);
	}

	ftruncate(fd, 0);
	sprintf(buff, "%d", (int)getpid());
	write(fd, buff, strlen(buff));

	return 0;
}


void* process_signal_thr(void* arg) {
	struct process_signal_args* opt = (struct process_signal_args*)arg;
	while ( opt->running ) {
		int signo = 0;
		if ( 0 != sigwait(opt->mask, &signo) ) {
			writedemonlog("error in sigwait =", strerror(errno));
			exit(EXIT_FAILURE);
		}
		switch ( signo ) {
			case SIGHUP:
				writedemonlog("reread configuration");
				if ( opt->reread_func_t ) {
					opt->reread_func_t();
				}
				break;
			case SIGTERM:
                        case SIGABRT:    
				writedemonlog("receive signal SIGTERM. exiting...");
				if ( opt->terminate_func_t ) {
					opt->terminate_func_t();
				}
				opt->running = 0;
				break;
			default:
				writedemonlog("unspecified signal '%d' received. ignored.");
				break;
		}
	}
	return 0;
}
    
}

#endif
