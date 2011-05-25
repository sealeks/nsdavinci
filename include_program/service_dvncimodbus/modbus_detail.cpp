/* 
 * File:   modbus_detail.cpp
 * Author: Serg
 * 
 * Created on 19 ќкт€брь 2010 г., 17:55
 */

#include "modbus_detail.h"

namespace dvnci{
    namespace driver{



        modbus_block_item::modbus_block_item(std::string vl, tagtype tgtp, const metalink & mlnk) : basis_block_item(vl, tgtp, mlnk) {
                protocol_ = (mlnk.chanaltype() == NT_CHTP_RS232_4XX) ?
                        ((mlnk.protocol() == NT_MODBUS_ASCII) ? INTPR_RS_MODBUS_ASCII : INTPR_RS_MODBUS_RTU) : INTPR_TCP_MODBUS;
                iscorrect_ = checktagtype();
                if (!iscorrect_) return;
                tp_=NULL_BIT_NUM;
                getspecificator(vl);
                iscorrect_ = parse(vl);}

        size_t modbus_block_item::operator-(const basis_block_item & rs) const  {
                if ((devnum() != rs.devnum()) || (type() != rs.type())) return MAXDISTANSE;
                switch (type_) {
                    case DISCRET_INPUT_MODBUS_TYPE: return static_cast<size_t> ((dvnci::abs<num32 > (addr() - rs.addr()) / 8 ) );
                    case COIL_MODBUS_TYPE: return static_cast<size_t> ((dvnci::abs<num32 > (addr() - rs.addr())  / 8 ) );
                    case INPUT_REGISTER_MODBUS_TYPE: return static_cast<size_t> (dvnci::abs<num32 > (addr() - rs.addr())) * 2;
                    case HOLDING_REGISTER_MODBUS_TYPE: return static_cast<size_t> (dvnci::abs<num32 > (addr() - rs.addr())) * 2;}
                return MAXDISTANSE;};


        bool modbus_block_item::parse(std::string vl) {

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
                        tp_=NULL_BIT_NUM;
                        type_ = DISCRET_INPUT_MODBUS_TYPE;
                        addr_ = adress;
                        size_ = 1;
                        return true;}
                    if (conformaddr(vl, "(?<=C)[0-9]{1,6}", adress, bitnum, 20000)) {
                        if (bitnum!=NULL_BIT_NUM)
                            return false;
                        tp_=NULL_BIT_NUM;
                        type_ = COIL_MODBUS_TYPE;
                        addr_ = adress;
                        size_ = 1;
                        return true;}
                    if (conformaddr(vl, "(?<=I)[0-9]{1,6}\\.{0,1}[0-9]{0,2}", adress, bitnum, 40000)) {
                        if ((bitnum!=NULL_BIT_NUM) && (bitnum>15))
                            return false;
                        tp_=bitnum;
                        type_ = INPUT_REGISTER_MODBUS_TYPE;
                        addr_ = adress;
                        size_ = (tgtype_ == TYPE_NODEF) ? 2 : static_cast<num32> (GETDV_TYPESIZE(tgtype_));
                        return true;}
                    if (conformaddr(vl, "(?<=H)[0-9]{1,6}\\.{0,1}[0-9]{0,2}", adress, bitnum, 40000)) {
                        if ((bitnum!=NULL_BIT_NUM) && (bitnum>15))
                            return false;
                        tp_=bitnum;
                        type_ = HOLDING_REGISTER_MODBUS_TYPE;
                        addr_ = adress;
                        size_ = (tgtype_ == TYPE_NODEF) ? 2 : static_cast<num32> (GETDV_TYPESIZE(tgtype_));
                        return true;}}
                error_ = ERROR_BINDING;
                return false;}

        bool modbus_block_item::conformaddr(const std::string& vl, std::string rgxstr, num32& addr, size_t& bitnum, num32 maxadr, num32 minadr) {
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

