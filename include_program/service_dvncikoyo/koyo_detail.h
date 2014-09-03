/* 
 * File:   modbus_detail.h
 * Author: Serg
 *
 * Created on 19 ??????? 2010 ?., 17:55
 */

#ifndef _DVNCI_KRNL_KOYO_DETAIL_H
#define	_DVNCI_KRNL_KOYO_DETAIL_H


#include <kernel/systemutil.h>
#include <kernel/driver_proccesstmpl.h>
#include <kernel/driver_blockmodel.h>
#include <driverspec/modbus_protocol.h>
#include <driverspec/directnet_protocol.h>

namespace dvnci {
    namespace driver {

        protocoltype def_koyo_protocol(const metalink& mlnk);

        const num32 NT_KOYO_GX_TYPE = 0xA;
        const num32 NT_KOYO_GY_TYPE = 0xB;
        const num32 NT_KOYO_X_TYPE = 0x1;
        const num32 NT_KOYO_Y_TYPE = 0x2;
        const num32 NT_KOYO_C_TYPE = 0x3;
        const num32 NT_KOYO_SP_TYPE = 0x4;
        const num32 NT_KOYO_T_TYPE = 0x5;
        const num32 NT_KOYO_CT_TYPE = 0x6;
        const num32 NT_KOYO_S_TYPE = 0x7;
        const num32 NT_KOYO_V_TYPE = 0x8;
        const num32 NT_KOYO_VB_TYPE = 0x9;

        const num32 NT_KOYO_GX_START = 040000;
        const num32 NT_KOYO_GY_START = 040200;
        const num32 NT_KOYO_X_START = 040400;
        const num32 NT_KOYO_Y_START = 040500;
        const num32 NT_KOYO_C_START = 040600;
        const num32 NT_KOYO_SP_START = 041200;
        const num32 NT_KOYO_T_START = 041100;
        const num32 NT_KOYO_CT_START = 041140;
        const num32 NT_KOYO_S_START = 041000;
        const num32 NT_KOYO_V_START = 0;
        const num32 NT_KOYO_VB_START = 0;

        const num32 NT_KOYO_GX_COUNT = 1024;
        const num32 NT_KOYO_GY_COUNT = 1024;
        const num32 NT_KOYO_X_COUNT = 1024;
        const num32 NT_KOYO_Y_COUNT = 1024;
        const num32 NT_KOYO_C_COUNT = 2048;
        const num32 NT_KOYO_SP_COUNT = 512;
        const num32 NT_KOYO_T_COUNT = 256;
        const num32 NT_KOYO_CT_COUNT = 256;
        const num32 NT_KOYO_S_COUNT = 1024;
        const num32 NT_KOYO_V_COUNT = 041177;
        const num32 NT_KOYO_VB_COUNT = 041177;

        const num32 NT_KOYO_GX_STOP = 040177;
        const num32 NT_KOYO_GY_STOP = 040377;
        const num32 NT_KOYO_X_STOP = 040477;
        const num32 NT_KOYO_Y_STOP = 040577;
        const num32 NT_KOYO_C_STOP = 040677;
        const num32 NT_KOYO_SP_STOP = 041237;
        const num32 NT_KOYO_T_STOP = 041117;
        const num32 NT_KOYO_CT_STOP = 041157;
        const num32 NT_KOYO_S_STOP = 041077;
        const num32 NT_KOYO_V_STOP = 041177;
        const num32 NT_KOYO_VB_STOP = 041177;


        const num32 NT_KOYO_GX_MODBUS = 0;
        const num32 NT_KOYO_GY_MODBUS = 0;
        const num32 NT_KOYO_X_MODBUS = 2048;
        const num32 NT_KOYO_Y_MODBUS = 2048;
        const num32 NT_KOYO_C_MODBUS = 3072;
        const num32 NT_KOYO_SP_MODBUS = 3072;
        const num32 NT_KOYO_T_MODBUS = 6144;
        const num32 NT_KOYO_CT_MODBUS = 6400;
        const num32 NT_KOYO_S_MODBUS = 5120;


        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Koyo ?????a ??????*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct koyo_req_parcel : public basis_req_parcel {

        public:

            koyo_req_parcel(std::string vl, tagtype tgtp, const metalink & mlnk);

            virtual size_t operator-(const basis_req_parcel & rs) const;

            bool parse(std::string vl) {
                if (parse_impl(vl)) {
                    if (protocol() != NT_KOYO_MODBUS) return true;
                    if (modbus_transform()) return true;
                }
                error(ERROR_BINDING);
                return false;
            }

            bool parse_impl(std::string vl);

        protected:

            bool conform_bit_koyo_addr(const std::string& vl, num32 startaddr, num32 maxcnt, std::string rgxstr, num32& addr, size_t & bitnum);
            bool conform_v_koyo_addr(const std::string& vl, num32 startaddr, num32 maxcnt, std::string rgxstr, num32& addr, size_t & bitnum);
            bool modbus_transform();
        };


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Koyo ????????? ????? ??????*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class koyo_block_model : public flatmemory_block_model<koyo_req_parcel> {

        public:

            koyo_block_model(executor* exectr, tagsbase_ptr inf, const metalink& mlnk) :
            flatmemory_block_model<koyo_req_parcel>(exectr, inf, mlnk) {
                switch (def_koyo_protocol(mlnk)) {
                    case NT_KOYO_DIRECTNET_ECOM:
                    {
                        blocksize = in_bounded<size_t > (8, MAX_ECOM_BLOCK_SIZE, static_cast<size_t> (mlnk.blocksize()));
                        break;
                    }
                    case NT_KOYO_MODBUS:
                    {
                        blocksize = in_bounded<size_t > (8, MAX_MODBUS_BLOCK_SIZE, static_cast<size_t> (mlnk.blocksize()));
                        break;
                    }
                    case NT_KOYO_DIRECTNET_ASCII:
                    {
                        blocksize = in_bounded<size_t > (8, MAX_KOYO_BLOCK_SIZE / 2, static_cast<size_t> (mlnk.blocksize()));
                        break;
                    }
                    default:
                    {
                        blocksize = in_bounded<size_t > (8, MAX_KOYO_BLOCK_SIZE, static_cast<size_t> (mlnk.blocksize()));
                        return;
                    }
                }
            };
        };



        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*?????????? ???????? Com ????? Koyo*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct koyo_com_option_setter : public com_option_setter {

            koyo_com_option_setter(const metalink & lnk) : com_option_setter(lnk) {
            };

            virtual boost::system::error_code store(com_port_option& opt, boost::system::error_code & ec) const;

            virtual boost::system::error_code load(com_port_option& opt, boost::system::error_code & ec) {
                return boost::system::error_code();
            }
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*koyo_metalink_checker*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct koyo_metalink_checker : public metalink_checker {

            virtual ns_error compare(const metalink& rs, const metalink & ls) {
                return ((ls.inf().cominf.boundrate != rs.inf().cominf.boundrate)) ? ERROR_IO_NOSYNC_LINK : 0;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*koyo_device_service*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct koyo_protocol_factory : public protocol_factory {

            virtual ioprotocol_ptr build(const metalink& lnk, ns_error & err);
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*koyo_device_service*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class koyo_device_service : public templ_device_service<koyo_protocol_factory> {

        public:

            koyo_device_service(const metalink& lnk) : templ_device_service<koyo_protocol_factory>(lnk) {
                util_interval(((lnk.protocol() == NT_KOYO_DIRECTNET_HEX) || ((lnk.protocol() == NT_KOYO_DIRECTNET_ASCII)) ||
                        (lnk.chanaltype() == NT_CHTP_UDP_IP)) ?
                        UTIL_INTERVAL_DAY : UTIL_INTERVAL_NONE);
            };
        };

    }
}



#endif	/* MODBUS_DETAIL_H */

