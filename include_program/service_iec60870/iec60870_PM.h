/* 
 * File:   ns_ioclient.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 ???? 2010 ?., 0:05
 */

#ifndef _DVNCI_KRNL_NS_IEC60850PM_H
#define	_DVNCI_KRNL_NS_IEC60850PM_H

#include "iec60870_104PM.h"

namespace dvnci {
    namespace prot80670 {


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_thread
        /////////////////////////////////////////////////////////////////////////////////////////////////        

        class iec60870_thread;

        typedef boost::weak_ptr< iec60870_thread> iec60870_thread_wptr;
        typedef boost::shared_ptr< iec60870_thread> iec60870_thread_ptr;

        class iec60870_thread : public boost::enable_shared_from_this<iec60870_thread> {

        public:

            iec60870_thread(std::string host, std::string port, timeouttype tmo,
                    iec60870_data_listener_ptr listr = iec60870_data_listener_ptr());

            ~iec60870_thread();
            
            void join();            

            static iec60870_thread_ptr create(std::string host, std::string port, timeouttype tmo,
                    iec60870_data_listener_ptr listr = iec60870_data_listener_ptr());

            iec60870_PM_ptr pm() const;

            iec60870_PM_ptr pm();

        private:
           
            iec60870_PM_ptr pm_;
            callable_shared<iec60870_PM> cpm_;
            boost::shared_ptr<boost::thread> ioth;
        };



    }
}


#endif	/* _NS_IOCLIENT_H */

