/* 
 * File:   iec60870_detail.cpp
 * Author: Alexeev
 */

#include "iec60870_detail.h"

namespace dvnci{
    namespace driver{



        iec60870_req_parcel::iec60870_req_parcel(std::string vl, tagtype tgtp, const metalink & mlnk) : basis_req_parcel(vl, tgtp, mlnk) {
                protocol_ = (mlnk.chanaltype() == NT_CHTP_RS232_4XX) ?
                        ((mlnk.protocol() == NT_MODBUS_ASCII) ? 
                            INTPR_RS_MODBUS_ASCII : INTPR_RS_MODBUS_RTU) : INTPR_TCP_MODBUS;
                indx_=NULL_BIT_NUM;
                getspecificator(vl);
                iscorrect_ = parse(vl);
        }

        size_t iec60870_req_parcel::operator-(const basis_req_parcel & rs) const {
            return BLOCKMAXDISTANCE;
        };

        bool iec60870_req_parcel::parse(std::string vl) {

            /* Name data type without _1 example M_SP_NA_1 => M_SP_NA == X_XX_XX
              X_XX_XXNNNNN[.B]                
              main templ = [CMP]_[ABSDEIMPRS][CEPTOS]_[TN][ABCDEF][0-9]{1,6}.{0,1}[0-9]{0,2}   
             */
            if (vl.size() > 7) {
                upper_and_trim(vl);
                std::string typedata = vl.substr(0, 7);
                std::string addrdata = vl.substr(7);
                parcelkind kind_ = find_parcelkind(typedata);
                if (kind_) {
                    std::string::size_type bitit = addrdata.find('.', 0);
                    if ((bitit != std::string::npos) && (bitit != (addrdata.size() - 1))) {
                        std::string bitdata = addrdata.substr(bitit + 1);
                        addrdata = addrdata.substr(0, bitit);
                        if (!dvnci::str_to(addrdata, indx_)) {
                            error(ERROR_BINDING);
                            return false;
                        }
                    }
                    if (!dvnci::str_to(addrdata, addr_)) {
                        error(ERROR_BINDING);
                        return false;
                    }
                    return true;
                }
            }
            error(ERROR_BINDING);
            return false;
        }


        

        //iec60870_com_option_setter

        boost::system::error_code iec60870_com_option_setter::store(com_port_option& opt, boost::system::error_code & ec) const {
            reset_default_nill(opt);
            switch (link.protocol()) {
                case NT_MODBUS_ASCII:
                {
                    set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                    rsparitytype tmprty = (link.inf().cominf.parity > NT_RS_EVENPARITY) ?
                            NT_RS_NOPARITY : link.inf().cominf.parity;
                    set_rs232_comoption(opt, 7, tmprty, (tmprty == NT_RS_NOPARITY) ?
                            NT_RS_TWOSTOPBITS : NT_RS_ONESTOPBIT);
                    break;
                }
                default:
                {
                    set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                    rsparitytype tmprty = (link.inf().cominf.parity > NT_RS_EVENPARITY) ?
                            NT_RS_NOPARITY : link.inf().cominf.parity;
                    set_rs232_comoption(opt, 8, tmprty, (tmprty == NT_RS_NOPARITY) ?
                            NT_RS_TWOSTOPBITS : NT_RS_ONESTOPBIT);
                }
            }

            return boost::system::error_code();
        }
        
        
        //iec60870_protocol_factory        
        
       ioprotocol_ptr iec60870_protocol_factory::build(const metalink& lnk, ns_error & err) {

                typedef rs_iostream<iec60870_com_option_setter> iec60870_rs_iostream;

                switch(lnk.chanaltype()){
                    case NT_CHTP_TCP_IP: {
   
                        basis_iostream_ptr tmp_stream = basis_iostream_ptr( 
                                new tcpip_iostream( lnk.timeout(), lnk.host(), MODBUS_TCP_PORT));                
                        return ioprotocol_ptr(
                                new tcp_iec60870_protocol<iec60870_value_manager>(tmp_stream));}

                    case NT_CHTP_RS232_4XX:{                      
                        basis_iostream_ptr tmp_stream = basis_iostream_ptr(
                                new iec60870_rs_iostream(lnk,  lnk.timeout(), lnk.chanalnum(), false));

                        switch (lnk.protocol()){
                            
                            case NT_MODBUS_ASCII: { return ioprotocol_ptr(
                                    new ascii_iec60870_protocol<iec60870_value_manager>(tmp_stream));}
                            
                            default : {return ioprotocol_ptr(
                                    new rtu_iec60870_protocol<iec60870_value_manager>(tmp_stream));}}}

                    default: {}}


                err = ERROR_IO_LINK_NOT_SUPPORT;
                return ioprotocol_ptr();}        



    }}

