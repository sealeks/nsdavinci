/* 
 * File:   modbus_detail.cpp
 * Author: Serg
 * 
 * Created on 19 ??????? 2010 ?., 17:55
 */

#include "modbus_detail.h"

namespace dvnci{
    namespace driver{



        modbus_req_parcel::modbus_req_parcel(std::string vl, tagtype tgtp, const metalink & mlnk) : basis_req_parcel(vl, tgtp, mlnk) {
                protocol_ = (mlnk.chanaltype() == NT_CHTP_RS232_4XX) ?
                        ((mlnk.protocol() == NT_MODBUS_ASCII) ? INTPR_RS_MODBUS_ASCII : INTPR_RS_MODBUS_RTU) : INTPR_TCP_MODBUS;
                indx_=NULL_BIT_NUM;
                getspecificator(vl);
                iscorrect_ = parse(vl);}

        size_t modbus_req_parcel::operator-(const basis_req_parcel & rs) const  {
                if ((devnum() != rs.devnum()) || (kind() != rs.kind())) return BLOCKMAXDISTANCE;
                switch (kind()) {
                    case DISCRET_INPUT_MODBUS_TYPE: return static_cast<size_t> ((dvnci::abs<num32 > (addr() - rs.addr()) / 8 ) );
                    case COIL_MODBUS_TYPE: return static_cast<size_t> ((dvnci::abs<num32 > (addr() - rs.addr())  / 8 ) );
                    case INPUT_REGISTER_MODBUS_TYPE: return static_cast<size_t> (dvnci::abs<num32 > (addr() - rs.addr())) * 2;
                    case HOLDING_REGISTER_MODBUS_TYPE: return static_cast<size_t> (dvnci::abs<num32 > (addr() - rs.addr())) * 2;}
                return BLOCKMAXDISTANCE;};


        bool modbus_req_parcel::parse(std::string vl) {

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

        bool modbus_req_parcel::conformaddr(const std::string& vl, std::string rgxstr, num32& addr, size_t& bitnum, num32 maxadr, num32 minadr) {
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



    }}

