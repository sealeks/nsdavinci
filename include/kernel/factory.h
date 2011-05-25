/* 
 * File:   factory.h
 * Author: Serg
 *
 * Created on 16 Сентябрь 2010 г., 18:15
 */

#ifndef _DVNCI_KRNL_FACTORY_H
#define	_DVNCI_KRNL_FACTORY_H

#include <kernel/constdef.h>
#include <kernel/memfile.h>

namespace dvnci {
    namespace krnl {

        class factory {
        public:

            static tagsbase_ptr build(fspath basepatht, appidtype appid = 0, eventtypeset evts = 0) {
                try {
                    tagsbase* tmp = new tagsbase(basepatht, appid, evts);
                    DEBUG_STR_DVNCI(SUCCESSFULL_INIT_INTERFACE)
                    return tagsbase_ptr(tmp);}
                catch (...) {
                    DEBUG_STR_DVNCI(ERROR_INIT_INTERFACE)
                    return tagsbase_ptr();}}};
    }}


#endif	/* FACTORY_H */

