/* 
 * File:   factory.h
 * Author: Serg
 *
 * Created on 20 Июль 2010 г., 16:36
 */

#ifndef _DVNCI_NETFACTORY_H
#define	_DVNCI_NETFACTORY_H

#include <netinterface/localnetintf.h>
#include <netinterface/remotenetintf.h>

namespace dvnci {
    namespace net {
        class factory {
        public:

            static netintf_ptr build(tagsbase_ptr intf_, dbtsk_exec_ptr tsk_exec = dbtsk_exec_ptr(), bool needconnect = true) {
                netintf_ptr tmpintf = netintf_ptr(new localnetintf(intf_, tsk_exec));
                if (needconnect) tmpintf->connect();
                return tmpintf;}

            static netintf_ptr build(const std::string host, const std::string port, const std::string user, const std::string password,  bool needconnect = false, int tmout = DEFAULT_DVNCI_TIMOUT) {
                netintf_ptr tmpintf = netintf_ptr(new remotenetintf(host, port, user, password, tmout));
                if (needconnect) tmpintf->connect();
                return tmpintf;}} ;

}}

#endif	/* FACTORY_H */

