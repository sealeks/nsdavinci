/* 
 * File:   modbus_detail.cpp
 * Author: Serg
 * 
 * Created on 19 ??????? 2010 ?., 17:55
 */

#include "koyo_detail.h"

namespace dvnci {
    namespace driver {

        protocoltype def_koyo_protocol(const metalink& mlnk) {
            switch (mlnk.chanaltype()) {
                case NT_CHTP_RS232_4XX:
                {
                    return (mlnk.protocol() <= NT_KOYO_DIRECTNET_ASCII) ? mlnk.protocol() : NT_KOYO_MODBUS;
                    break;
                }
                case NT_CHTP_TCP_IP:
                {
                    return NT_KOYO_MODBUS;
                }
                case NT_CHTP_UDP_IP:
                {
                    return NT_KOYO_DIRECTNET_ECOM;
                }
                default:
                {
                    return -1;
                }
            }
        }

        koyo_req_parcel::koyo_req_parcel(std::string vl, tagtype tgtp, const metalink & mlnk) : basis_req_parcel(vl, tgtp, mlnk) {
            protocol_ = def_koyo_protocol(mlnk);
            if (protocol_ < 0) {
                iscorrect_ = false;
                if (protocol_ = NT_KOYO_DIRECTNET_ECOM) devnum_ = 1;
                error(ERROR_IO_LINK_NOT_SUPPORT);
                return;
            }
            indx_ = NULL_BIT_NUM;
            getspecificator(vl);
            iscorrect_ = parse(vl);
        }

        size_t koyo_req_parcel::operator-(const basis_req_parcel & rs) const {
            if (protocol() == NT_KOYO_MODBUS) {
                if ((devnum() != rs.devnum()) || (kind() != rs.kind())) return BLOCKMAXDISTANCE;
                switch (kind()) {
                    case DISCRET_INPUT_MODBUS_TYPE: return static_cast<size_t> ((dvnci::abs<num32 > (addr() - rs.addr()) / 8));
                    case COIL_MODBUS_TYPE: return static_cast<size_t> ((dvnci::abs<num32 > (addr() - rs.addr()) / 8));
                    case INPUT_REGISTER_MODBUS_TYPE: return static_cast<size_t> (dvnci::abs<num32 > (addr() - rs.addr())) * 2;
                    case HOLDING_REGISTER_MODBUS_TYPE: return static_cast<size_t> (dvnci::abs<num32 > (addr() - rs.addr())) * 2;
                }
            } else {
                return static_cast<size_t> (dvnci::abs<num32 > (addr() - rs.addr())) * 2;
            }
            return BLOCKMAXDISTANCE;
        };

        bool koyo_req_parcel::parse_impl(std::string vl) {

            /*XOOO  discret input
              Y000  discret output
              C000
              SP000
              T000
              CTOOO
              S000
              V00000
              V00000.NN

              main templ = [XYCSTV][PT][0-7]{1,6}
              X templ    = (?<=X)[0-7]{1,4}
              Y templ    = (?<=Y)[0-7]{1,4}
              C templ    = (?<=C)[0-7]{1,4}
              SP templ    = (?<=SP)[0-7]{1,3}
              T templ    = (?<=T)[0-7]{1,3}
              CT templ    = (?<=CT)[0-7]{1,3}
              S templ    = (?<=S)[0-7]{1,3}
              V templ    = (?<=V)[0-7]{1,5}
              VB templ    = (?<=V)[0-7]{1,5}\.[0-9]{1,2}
             */

            upper_and_trim(vl);
            boost::regex regexbind("[XYCSTVG][PTXY]{0,1}[0-7]{1,6}\\.{0,1}[0-9]{0,2}");
            boost::smatch rslt;
            if (boost::regex_match(vl, rslt, regexbind)) {
                num32 adress;
                size_t bitnum = 0;
                if (conform_v_koyo_addr(vl, NT_KOYO_V_START, NT_KOYO_V_COUNT, "(?<=V)[0-7]{1,5}\\.{0,1}[0-9]{0,2}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    if (bitnum == NULL_BIT_NUM)
                        size_ = (type() == TYPE_NODEF) ? 2 : static_cast<num32> (GETDV_TYPESIZE(type()));
                    else
                        size_ = 2;
                    return true;
                }

                if (conform_bit_koyo_addr(vl, NT_KOYO_X_START, NT_KOYO_X_COUNT, "(?<=X)[0-7]{1,4}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    size_ = 2;
                    return true;
                }
                if (conform_bit_koyo_addr(vl, NT_KOYO_Y_START, NT_KOYO_Y_COUNT, "(?<=Y)[0-7]{1,4}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    size_ = 2;
                    return true;
                }
                if (conform_bit_koyo_addr(vl, NT_KOYO_C_START, NT_KOYO_C_COUNT, "(?<=C)[0-7]{1,4}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    size_ = 2;
                    return true;
                }
                if (conform_bit_koyo_addr(vl, NT_KOYO_SP_START, NT_KOYO_SP_COUNT, "(?<=SP)[0-7]{1,4}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    size_ = 2;
                    return true;
                }
                if (conform_bit_koyo_addr(vl, NT_KOYO_T_START, NT_KOYO_T_COUNT, "(?<=T)[0-7]{1,4}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    size_ = 2;
                    return true;
                }
                if (conform_bit_koyo_addr(vl, NT_KOYO_CT_START, NT_KOYO_CT_COUNT, "(?<=CT)[0-7]{1,4}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    size_ = 2;
                    return true;
                }
                if (conform_bit_koyo_addr(vl, NT_KOYO_S_START, NT_KOYO_S_COUNT, "(?<=S)[0-7]{1,4}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    size_ = 2;
                    return true;
                }
                if (conform_bit_koyo_addr(vl, NT_KOYO_GX_START, NT_KOYO_GX_COUNT, "(?<=GX)[0-7]{1,4}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    size_ = 2;
                    return true;
                }
                if (conform_bit_koyo_addr(vl, NT_KOYO_GY_START, NT_KOYO_GY_COUNT, "(?<=GY)[0-7]{1,4}", adress, bitnum)) {
                    kind_ = 0;
                    addr_ = adress;
                    indx_ = bitnum;
                    size_ = 2;
                    return true;
                }
            }
            error(ERROR_BINDING);
            return false;
        }

        bool koyo_req_parcel::conform_bit_koyo_addr(const std::string& vl, num32 startaddr, num32 maxcnt, std::string rgxstr, num32& addr, size_t& bitnum) {
            boost::smatch rslt;
            boost::regex rgx(rgxstr);
            if (boost::regex_search(vl, rslt, rgx)) {
                if (rslt.size() == 1) {
                    num32 tmpaddr = 0;
                    if (octstr_to<num32 > (rslt[0], tmpaddr))
                        if (tmpaddr <= maxcnt) {
                            addr = startaddr + (tmpaddr / 16);
                            bitnum = tmpaddr % 16;
                            return true;
                        };
                }
            }
            return false;
        }

        bool koyo_req_parcel::conform_v_koyo_addr(const std::string& vl, num32 startaddr, num32 maxcnt, std::string rgxstr, num32& addr, size_t& bitnum) {
            boost::smatch rslt;
            boost::regex rgx(rgxstr);
            if (boost::regex_search(vl, rslt, rgx)) {
                if (rslt.size() == 1) {
                    std::string addr_str = rslt[0];
                    std::string bit_str = "";
                    std::string::size_type it = addr_str.find(".");
                    if (it != std::string::npos) {
                        if (it >= (addr_str.size() - 1))
                            return false;
                        bit_str = addr_str.substr(it + 1);
                        addr_str = addr_str.substr(0, it);
                    }
                    if (octstr_to<num32 > (addr_str, addr))
                        if (addr <= maxcnt) {
                            if (bit_str == "") {
                                bitnum = NULL_BIT_NUM;
                                return true;
                            }
                            if (str_to<size_t > (bit_str, bitnum)) {
                                if (bitnum < 16)
                                    return true;
                            };
                        }
                }
            }
            return false;
        }

        bool koyo_req_parcel::modbus_transform() {
            if (indx() == NULL_BIT_NUM) {
                kind_ = HOLDING_REGISTER_MODBUS_TYPE;
                addr_ += 0;
                return true;
            } else {
                if (indx() > 15) return false;
                if ((addr() >= NT_KOYO_C_START) && (addr() <= NT_KOYO_C_STOP)) {
                    kind_ = COIL_MODBUS_TYPE;
                    size_ = 1;
                    addr_ = NT_KOYO_C_MODBUS + (addr() - NT_KOYO_C_START) * 16 + indx();
                    return true;
                }
                if ((addr() >= NT_KOYO_X_START) && (addr() <= NT_KOYO_X_STOP)) {
                    kind_ = DISCRET_INPUT_MODBUS_TYPE;
                    size_ = 1;
                    addr_ = NT_KOYO_X_MODBUS + (addr() - NT_KOYO_X_START) * 16 + indx();
                    return true;
                }
                if ((addr() >= NT_KOYO_Y_START) && (addr() <= NT_KOYO_Y_STOP)) {
                    kind_ = COIL_MODBUS_TYPE;
                    addr_ = NT_KOYO_Y_MODBUS + (addr() - NT_KOYO_Y_START) * 16 + indx();
                    return true;
                }
                if ((addr() >= NT_KOYO_SP_START) && (addr() <= NT_KOYO_SP_STOP)) {
                    kind_ = DISCRET_INPUT_MODBUS_TYPE;
                    addr_ = NT_KOYO_SP_MODBUS + (addr() - NT_KOYO_SP_START) * 16 + indx();
                    return true;
                }
                if ((addr() >= NT_KOYO_T_START) && (addr() <= NT_KOYO_T_STOP)) {
                    kind_ = COIL_MODBUS_TYPE;
                    addr_ = NT_KOYO_T_MODBUS + (addr() - NT_KOYO_T_START) * 16 + indx();
                    return true;
                }
                if ((addr() >= NT_KOYO_CT_START) && (addr() <= NT_KOYO_CT_STOP)) {
                    kind_ = COIL_MODBUS_TYPE;
                    addr_ = NT_KOYO_CT_MODBUS + (addr() - NT_KOYO_CT_START) * 16 + indx();
                    return true;
                }
                if ((addr() >= NT_KOYO_S_START) && (addr() <= NT_KOYO_S_STOP)) {
                    kind_ = COIL_MODBUS_TYPE;
                    addr_ = NT_KOYO_S_MODBUS + (addr() - NT_KOYO_S_START) * 16 + indx();
                    return true;
                }
                if ((addr() >= NT_KOYO_GX_START) && (addr() <= NT_KOYO_GX_STOP)) {
                    kind_ = DISCRET_INPUT_MODBUS_TYPE;
                    size_ = 1;
                    addr_ = NT_KOYO_GX_MODBUS + (addr() - NT_KOYO_GX_START) * 16 + indx();
                    return true;
                }
                if ((addr() >= NT_KOYO_GY_START) && (addr() <= NT_KOYO_GY_STOP)) {
                    kind_ = COIL_MODBUS_TYPE;
                    addr_ = NT_KOYO_GY_MODBUS + (addr() - NT_KOYO_GY_START) * 16 + indx();
                    return true;
                }
            }
            kind_ = HOLDING_REGISTER_MODBUS_TYPE;
            return true;
        }



        //koyo_com_option_setter

        boost::system::error_code koyo_com_option_setter::store(com_port_option& opt, boost::system::error_code & ec) const {
            reset_default_nill(opt);
            switch (link.protocol()) {
                case NT_KOYO_DIRECTNET_HEX:
                {
                    set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                    rsparitytype tmprty = (link.inf().cominf.parity > NT_RS_EVENPARITY) ? NT_RS_NOPARITY : link.inf().cominf.parity;
                    set_rs232_comoption(opt, 8, tmprty,
                            (tmprty == NT_RS_NOPARITY) ? NT_RS_TWOSTOPBITS : NT_RS_ONESTOPBIT);
                }
                case NT_KOYO_DIRECTNET_ASCII:
                {
                    set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                    rsparitytype tmprty = (link.inf().cominf.parity > NT_RS_EVENPARITY) ? NT_RS_NOPARITY : link.inf().cominf.parity;
                    set_rs232_comoption(opt, 8, tmprty,
                            (tmprty == NT_RS_NOPARITY) ? NT_RS_TWOSTOPBITS : NT_RS_ONESTOPBIT);
                }
                default:
                {
                    set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                    rsparitytype tmprty = (link.inf().cominf.parity > NT_RS_EVENPARITY) ? NT_RS_NOPARITY : link.inf().cominf.parity;
                    set_rs232_comoption(opt, 8, tmprty,
                            (tmprty == NT_RS_NOPARITY) ? NT_RS_TWOSTOPBITS : NT_RS_ONESTOPBIT);
                }
            }
            return boost::system::error_code();
        }



        //koyo_protocol_factory

        ioprotocol_ptr koyo_protocol_factory::build(const metalink& lnk, ns_error & err) {

            typedef rs_iostream<koyo_com_option_setter> koyo_rs_iostream;

            switch (lnk.chanaltype()) {
                case NT_CHTP_TCP_IP:
                {
                    basis_iostream_ptr tmp_stream = basis_iostream_ptr(
                            new tcpip_iostream(lnk.timeout(), lnk.host(), MODBUS_TCP_PORT));
                    return ioprotocol_ptr(new tcp_modbus_protocol<modbus_value_manager > (tmp_stream));
                }

                case NT_CHTP_UDP_IP:
                {
                    basis_iostream_ptr tmp_stream = basis_iostream_ptr(
                            new udpip_iostream(lnk.timeout(), lnk.host(), ECOM_UDP_PORT, ECOM_BUFF_SIZE));
                    return ioprotocol_ptr(new ecom_protocol(tmp_stream));
                }

                case NT_CHTP_RS232_4XX:
                {


                    basis_iostream_ptr tmp_stream = basis_iostream_ptr(new koyo_rs_iostream(lnk,
                            lnk.timeout(), lnk.chanalnum(), false));

                    switch (lnk.protocol()) {

                        case NT_KOYO_DIRECTNET_HEX:
                        {
                            return ioprotocol_ptr(new hex_direcnet_protocol(tmp_stream));
                        }
                        case NT_KOYO_DIRECTNET_ASCII:
                        {
                            return ioprotocol_ptr(new ascii_direcnet_protocol(tmp_stream));
                        }
                        default:
                        {
                            return ioprotocol_ptr(new rtu_modbus_protocol<modbus_value_manager > (tmp_stream));
                        }
                    }
                }

                default:
                {
                }
            }

            err = ERROR_IO_LINK_NOT_SUPPORT;
            return ioprotocol_ptr();
        };



    }
}

