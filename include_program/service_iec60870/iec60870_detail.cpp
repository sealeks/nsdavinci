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
                iscorrect_ = parse(vl);}

        size_t iec60870_req_parcel::operator-(const basis_req_parcel & rs) const  {
            
                if ((devnum() != rs.devnum()) || (kind() != rs.kind())) return BLOCKMAXDISTANCE;
                switch (kind()) {
                    case DISCRET_INPUT_MODBUS_TYPE: return static_cast<size_t> ((dvnci::abs<num32 > (addr() - rs.addr()) / 8 ) );
                    case COIL_MODBUS_TYPE: return static_cast<size_t> ((dvnci::abs<num32 > (addr() - rs.addr())  / 8 ) );
                    case INPUT_REGISTER_MODBUS_TYPE: return static_cast<size_t> (dvnci::abs<num32 > (addr() - rs.addr())) * 2;
                    case HOLDING_REGISTER_MODBUS_TYPE: return static_cast<size_t> (dvnci::abs<num32 > (addr() - rs.addr())) * 2;}
                return BLOCKMAXDISTANCE;};


        bool iec60870_req_parcel::parse(std::string vl) {

                /*DNNNN  discret intut
                  CNNNN  coils
                  INNNN[.N]  input register
                  HNNNN[.N]  holding register

                  main templ = [DCIH][0-9]{1,6}\\.{0,1}[0-9]{0,2}
                  D templ    = (?<=D)[0-9]{1,6}
                  C templ    = (?<=C)[0-9]{1,6}
                  H templ    = (?<=H)[0-9]{1,6}\\.{0,1}[0-9]{0,2}
                  I templ    = (?<=I)[0-9]{1,6}\\.{0,1}[0-9]{0,2}
                 */

                upper_and_trim(vl);
                boost::regex regexbind("[DCIH][0-9]{1,6}\\.{0,1}[0-9]{0,2}");
                boost::smatch rslt;
                size_t bitnum=NULL_BIT_NUM;
                if (boost::regex_match(vl,  rslt, regexbind)) {
                    num32 adress;
                    if (conformaddr(vl, "(?<=D)[0-9]{1,6}",  adress, bitnum, 20000)) {
                        if (bitnum!=NULL_BIT_NUM)
                            return false;
                        indx_=NULL_BIT_NUM;
                        kind_ = DISCRET_INPUT_MODBUS_TYPE;
                        addr_ = adress;
                        size_ = 1;
                        return true;}
                    if (conformaddr(vl, "(?<=C)[0-9]{1,6}", adress, bitnum, 20000)) {
                        if (bitnum!=NULL_BIT_NUM)
                            return false;
                        indx_=NULL_BIT_NUM;
                        kind_ = COIL_MODBUS_TYPE;
                        addr_ = adress;
                        size_ = 1;
                        return true;}
                    if (conformaddr(vl, "(?<=I)[0-9]{1,6}\\.{0,1}[0-9]{0,2}", adress, bitnum, 40000)) {
                        if ((bitnum!=NULL_BIT_NUM) && (bitnum>15))
                            return false;
                        indx_=bitnum;
                        kind_ = INPUT_REGISTER_MODBUS_TYPE;
                        addr_ = adress;
                        size_ = (type() == TYPE_NODEF) ? 2 : static_cast<num32> (GETDV_TYPESIZE(type()));
                        return true;}
                    if (conformaddr(vl, "(?<=H)[0-9]{1,6}\\.{0,1}[0-9]{0,2}", adress, bitnum, 40000)) {
                        if ((bitnum!=NULL_BIT_NUM) && (bitnum>15))
                            return false;
                        indx_=bitnum;
                        kind_ = HOLDING_REGISTER_MODBUS_TYPE;
                        addr_ = adress;
                        size_ = (type() == TYPE_NODEF) ? 2 : static_cast<num32> (GETDV_TYPESIZE(type()));
                        return true;}}
                error(ERROR_BINDING);
                return false;}

        bool iec60870_req_parcel::conformaddr(const std::string& vl, std::string rgxstr, num32& addr, size_t& bitnum, num32 maxadr, num32 minadr) {
                bitnum = NULL_BIT_NUM;
                boost::smatch rslt;
                boost::regex rgx(rgxstr);
                if (boost::regex_search(vl,  rslt, rgx)) {
                    if (rslt.size() == 1){
                        std::string addr_str=rslt[0];
                        std::string bit_str="";
                        std::string::size_type it = addr_str.find(".");
                        if (it!=std::string::npos){
                            if (it>=(addr_str.size()-1))
                                return false;
                            bit_str = addr_str.substr(it+1);
                            addr_str=addr_str.substr(0,it);}
                        if (str_to<num32 > (addr_str, addr))
                            if ((addr >= minadr) && (addr <= maxadr)) {
                                addr--;
                                if (bit_str=="") {
                                    bitnum = NULL_BIT_NUM;
                                    return true;}
                                if (str_to<size_t>(bit_str,bitnum)){
                                    if (bitnum<16)
                                     return true;}}}}
				return false;}
        
        
        //iec60870_com_option_setter
        
        boost::system::error_code iec60870_com_option_setter::store(com_port_option&  opt, boost::system::error_code & ec) const {
                reset_default_nill(opt);
		switch (link.protocol()){
		    case NT_MODBUS_ASCII: {
			set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                        rsparitytype tmprty = (link.inf().cominf.parity > NT_RS_EVENPARITY) ? 
                            NT_RS_NOPARITY : link.inf().cominf.parity;
                        set_rs232_comoption(opt,7, tmprty, (tmprty  == NT_RS_NOPARITY) ? 
                            NT_RS_TWOSTOPBITS : NT_RS_ONESTOPBIT);
			break;}
		    default :{
                        set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                        rsparitytype tmprty = (link.inf().cominf.parity > NT_RS_EVENPARITY) ?
                            NT_RS_NOPARITY : link.inf().cominf.parity;
                        set_rs232_comoption(opt,8, tmprty, (tmprty  == NT_RS_NOPARITY) ? 
                            NT_RS_TWOSTOPBITS : NT_RS_ONESTOPBIT);}}
                
			return boost::system::error_code();}
        
        
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

