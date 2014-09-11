/* 
 * File:   iec60870_detail.h
 * Author: Alexeev
 */

#ifndef _DVNCI_KRNL_IEC60870_DETAIL_H
#define	_DVNCI_KRNL_IEC60870_DETAIL_H

#include <kernel/driver_proccesstmpl.h>
#include <kernel/driver_blockmodel.h>
#include <iec60870/iec60870_protocol.h>

namespace dvnci {
    namespace prot80670 {


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*com_option_setter*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct iec60870_com_option_setter : public com_option_setter {

            iec60870_com_option_setter(const metalink & lnk) : com_option_setter(lnk) {
            };

            virtual boost::system::error_code store(com_port_option& opt, boost::system::error_code & ec) const;

            virtual boost::system::error_code load(com_port_option& opt, boost::system::error_code & ec) {
                return boost::system::error_code();
            }
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*iec60870_metalink_checker*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct iec60870_metalink_checker : public metalink_checker {

            virtual ns_error compare(const metalink& rs, const metalink& ls) {
                return ((ls.inf().cominf.boundrate != rs.inf().cominf.boundrate)) ? ERROR_IO_NOSYNC_LINK : 0;
            }
        };





    }
}



#endif	/* MODBUS_DETAIL_H */

