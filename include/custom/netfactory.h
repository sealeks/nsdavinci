/* 
 * File:   factory.h
 * Author: Serg
 *
 * Created on 20 Июль 2010 г., 16:36
 */

#ifndef _DVNCI_CUSTOMNETFACTORY_H
#define	_DVNCI_CUSTOMNETFACTORY_H

#include <custom/localnetintf.h>
#include <custom/remotenetintf.h>

namespace dvnci {
    namespace custom {
        namespace net {

            typedef intrusive_sync_share_ptr_tmpl<netintf> netintf_ptr;

            class factory {

            public:

                static netintf_ptr build(tagsbase_ptr intf) {
                    netintf_ptr tmpintf = netintf_ptr(new localnetintf(intf));
                    return tmpintf;
                }

                static netintf_ptr build(const std::string host, const std::string port, const std::string user, const std::string password, timeouttype tmout = DEFAULT_DVNCI_TIMOUT) {
                    netintf_ptr tmpintf = netintf_ptr(new remotenetintf(host, port, user, password, tmout));
                    ;
                    return tmpintf;
                }
            };
        }
    }
}

#endif	/* FACTORY_H */

