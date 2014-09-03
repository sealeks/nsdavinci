/* 
 * File:   dbfactory.h
 * Author: Serg
 *
 * Created on 20 Июль 2010 г., 1:05
 */

#ifndef _GG_DB_FACTORY_H
#define	_GG_DB_FACTORY_H

#include <dbaccess/dbdriver.h>


namespace dvnci {
    namespace database {

        typedef sync_share_ptr_tmpl<dbdriver> dbdriver_ptr;

        class bdconnectionfactory {

        public:

            static dbdriver_ptr build(num32 provider, std::string constr, bool ex_write = false);
        };
    }
}



#endif	/* DBFACTORY_H */

