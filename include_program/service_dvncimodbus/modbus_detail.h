/* 
 * File:   modbus_detail.h
 * Author: Serg
 *
 * Created on 19 ??????? 2010 ?., 17:55
 */

#ifndef _DVNCI_KRNL_MODBUS_DETAIL_H
#define	_DVNCI_KRNL_MODBUS_DETAIL_H

#include <kernel/driver_proccesstmpl.h>
#include <kernel/driver_blockmodel.h>
#include <driverspec/modbus_protocol.h>

namespace dvnci {
    namespace driver {

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*modbus_req_parcel*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct modbus_req_parcel : public basis_req_parcel {

        public:

            modbus_req_parcel(std::string vl, tagtype tgtp, const metalink & mlnk);

            virtual size_t operator-(const basis_req_parcel & rs) const;

            bool parse(std::string vl);

        protected:

            bool conformaddr(const std::string& vl, std::string rgxstr, num32& addr, size_t& bitnum, num32 maxadr, num32 minadr = 1);
        };


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*modbus_block_model*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class modbus_block_model : public flatmemory_block_model<modbus_req_parcel> {

        public:

            modbus_block_model(executor* exectr, tagsbase_ptr inf, const metalink& mlnk) :
            flatmemory_block_model<modbus_req_parcel>(exectr, inf, mlnk) {

                blocksize = ((mlnk.protocol() == NT_MODBUS_ASCII) && (mlnk.chanaltype() != NT_CHTP_TCP_IP)) ?
                        in_bounded<size_t > (8, MAX_MODBUS_BLOCK_SIZE / 2, static_cast<size_t> (mlnk.blocksize())) :
                        in_bounded<size_t > (8, MAX_MODBUS_BLOCK_SIZE, static_cast<size_t> (mlnk.blocksize()));
            };
        };



        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*com_option_setter*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct modbus_com_option_setter : public com_option_setter {

            modbus_com_option_setter(const metalink & lnk) : com_option_setter(lnk) {
            };

            virtual boost::system::error_code store(com_port_option& opt, boost::system::error_code & ec) const;

            virtual boost::system::error_code load(com_port_option& opt, boost::system::error_code & ec) {
                return boost::system::error_code();
            }
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*modbus_metalink_checker*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct modbus_metalink_checker : public metalink_checker {

            virtual ns_error compare(const metalink& rs, const metalink& ls) {
                return ((ls.inf().cominf.boundrate != rs.inf().cominf.boundrate)) ? ERROR_IO_NOSYNC_LINK : 0;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*modbus_protocol_factory*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct modbus_protocol_factory : public protocol_factory {

            virtual ioprotocol_ptr build(const metalink& lnk, ns_error & err);
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*modbus_device_service*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class modbus_device_service : public templ_device_service<modbus_protocol_factory> {

        public:

            modbus_device_service(const metalink& lnk) :
            templ_device_service<modbus_protocol_factory>(lnk) {
            };
        };



    }
}



#endif	/* MODBUS_DETAIL_H */

