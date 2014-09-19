
#include <iec60870/iec60870_factory.h>


namespace dvnci {
    namespace prot80670 {


         /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_thread
        /////////////////////////////////////////////////////////////////////////////////////////////////        

        iec60870_factory::iec60870_factory(const std::string& host, const std::string& port,
               const iec_option& opt, iec60870_data_listener_ptr listr) : 
        pm_(new iec60870_104PM(host, port, opt, listr)) , cpm_(pm_){
            ioth = boost::shared_ptr<boost::thread>(new boost::thread(cpm_));
        }
        
        iec60870_factory::iec60870_factory(IEC_PROTOCOL prot, chnlnumtype chnm,  
                const iec_option& opt, iec60870_data_listener_ptr listr) {
                
        typedef iec60870_101PM<lasz_one, ctsz_one, select_double, ioa_double> iec60870_101PM_tst;

            pm_ = iec60870_PM_ptr(new iec60870_101PM_tst(chnm, opt, listr));
            cpm_ = pm_;
            ioth = boost::shared_ptr<boost::thread>(new boost::thread(cpm_));
        }        

         iec60870_factory::~iec60870_factory() {

        }

        iec60870_thread_ptr iec60870_factory::create(const std::string& host, const std::string& port,
               const iec_option& opt,  iec60870_data_listener_ptr listr) {
            return iec60870_thread_ptr(new iec60870_factory(host, port, opt, listr));
        }
        
        iec60870_thread_ptr iec60870_factory::create(IEC_PROTOCOL prot, chnlnumtype chnm,  const iec_option& opt,
                    iec60870_data_listener_ptr listr){
            return iec60870_thread_ptr(new iec60870_factory(prot, chnm, opt, listr));            
        }   
        
        void iec60870_factory::join() {
            if (ioth)
                ioth->join();
        }       

        iec60870_PM_ptr iec60870_factory::pm() const {
            return pm_;
        }

        iec60870_PM_ptr iec60870_factory::pm() {
            return pm_;
        }

    }
}


