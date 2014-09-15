
#include "iec60870_PM.h"


namespace dvnci {
    namespace prot80670 {


         /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_thread
        /////////////////////////////////////////////////////////////////////////////////////////////////        

        iec60870_thread::iec60870_thread(const std::string& host, const std::string& port,
               const iec_option& opt, iec60870_data_listener_ptr listr) : 
        pm_(new iec60870_104PM(host, port, opt, listr)) , cpm_(pm_){
            ioth = boost::shared_ptr<boost::thread>(new boost::thread(cpm_));
        }
        
        iec60870_thread::iec60870_thread(IEC_PROTOCOL prot, chnlnumtype chnm, const metalink & lnk, 
                const iec_option& opt, iec60870_data_listener_ptr listr) {
                
        typedef iec60870_101PM<lasz_one, ctsz_one, select_double, ioa_double> iec60870_101PM_tst;

            pm_ = iec60870_PM_ptr(new iec60870_101PM_tst(chnm, lnk, opt, listr));
            cpm_ = pm_;
            ioth = boost::shared_ptr<boost::thread>(new boost::thread(cpm_));
        }        

         iec60870_thread::~iec60870_thread() {

        }

        iec60870_thread_ptr iec60870_thread::create(const std::string& host, const std::string& port,
               const iec_option& opt,  iec60870_data_listener_ptr listr) {
            return iec60870_thread_ptr(new iec60870_thread(host, port, opt, listr));
        }
        
        iec60870_thread_ptr iec60870_thread::create(IEC_PROTOCOL prot, chnlnumtype chnm, const metalink & lnk, const iec_option& opt,
                    iec60870_data_listener_ptr listr){
            return iec60870_thread_ptr(new iec60870_thread(prot, chnm, lnk, opt, listr));            
        }   
        
        void iec60870_thread::join() {
            if (ioth)
                ioth->join();
        }       

        iec60870_PM_ptr iec60870_thread::pm() const {
            return pm_;
        }

        iec60870_PM_ptr iec60870_thread::pm() {
            return pm_;
        }

    }
}


