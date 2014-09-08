
#include "iec60870_PM.h"


namespace dvnci {
    namespace prot80670 {


         /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_thread
        /////////////////////////////////////////////////////////////////////////////////////////////////        

        iec60870_thread::iec60870_thread(std::string host, std::string port, timeouttype tmo, iec60870_data_listener_ptr listr) {
            pm_ = callable_shared_ptr<iec60870_PM>(new iec60870_104PM(host, port, tmo, listr));
            ioth = boost::shared_ptr<boost::thread>(new boost::thread(pm_));
        }

         iec60870_thread::~iec60870_thread() {
             /*if (ioth)
                 ioth->join();*/
        }

        iec60870_thread_ptr iec60870_thread::create(std::string host, std::string port, timeouttype tmo,
                iec60870_data_listener_ptr listr) {
            return iec60870_thread_ptr(new iec60870_thread(host, port, tmo, listr));
        }

        void iec60870_thread::join() {
            if (ioth)
                ioth->join();
        }       

        callable_shared_ptr<iec60870_PM>iec60870_thread::pm() const {
            return pm_;
        }

        callable_shared_ptr<iec60870_PM>iec60870_thread::pm() {
            return pm_;
        }

    }
}


