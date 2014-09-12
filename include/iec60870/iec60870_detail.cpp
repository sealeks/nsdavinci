/* 
 * File:   iec60870_detail.cpp
 * Author: Alexeev
 */

#include "iec60870_detail.h"

namespace dvnci {
    namespace prot80670 {

        //    iec_option

        iec_option::iec_option(ADDRESS_sizetype adr, COT_sizetype ct, SECTOR_sizetype sct, IOA_sizetype ioa) : opton_("\x0") {
            opton_[0] |= adr;
            opton_[0] |= ((ct - 1) << 2);
            opton_[0] |= ((sct - 1) << 3);
            opton_[0] |= ((ioa - 1) << 4);
        }

        ADDRESS_sizetype iec_option::addr() const {
            if (opton_.empty() || ((opton_[0]&3) == 3))
                return lasz_none;
            return static_cast<ADDRESS_sizetype> (opton_[0]&3);
        }

        void iec_option::addr(ADDRESS_sizetype vl) {
            if (opton_.empty())
                opton_ = "\x0";
            opton_[0] |= static_cast<std::string::value_type> (vl);
        }

        COT_sizetype iec_option::cot() const {
            if (opton_.empty())
                return ctsz_one;
            return static_cast<COT_sizetype> ((((opton_[0]&4) >> 2) & 1) + 1);
        }

        void iec_option::cot(COT_sizetype vl) {
            if (opton_.empty())
                opton_ = "\x0";
            opton_[0] |= ((static_cast<std::string::value_type> (vl) - 1) << 2);
        }

        SECTOR_sizetype iec_option::sector() const {
            if (opton_.empty())
                return select_one;
            return static_cast<SECTOR_sizetype> ((((opton_[0]&8) >> 3) & 1) + 1);
        }

        void iec_option::sector(SECTOR_sizetype vl) {
            if (opton_.empty())
                opton_ = "\x0";
            opton_[0] |= ((static_cast<std::string::value_type> (vl) - 1) << 3);
        }

        IOA_sizetype iec_option::ioa() const {
            if (opton_.empty())
                return ioa_one;
            std::string::value_type tmp = (((opton_[0]&8) >> 4) & 1) + 1;
            if (tmp > 3)
                tmp = 3;
            return static_cast<IOA_sizetype> (tmp);
        }

        void iec_option::ioa(IOA_sizetype vl) {
            if (opton_.empty())
                opton_ = "\x0";
            opton_[0] |= ((static_cast<std::string::value_type> (vl) - 1) << 4);
        }

        std::size_t iec_option::trycount() const {
            return get<1, 3, 20, 3>();
        }

        void iec_option::trycount(std::size_t vl) {
            return set<1, 3, 20>(vl);
        } 
        
        std::size_t iec_option::t0() const {
            return get<2,1, 127, 30>();
        }

        void iec_option::t0(std::size_t vl) {
            return set<2, 1, 127>(vl);
        }        
        
        std::size_t iec_option::t1() const {
            return get<3, 3, 127, 10>();
        }

        void iec_option::t1(std::size_t vl) {
            return set<3, 3, 127>(vl);
        }        
        
        std::size_t iec_option::t2() const {
            return get<4, 1, 127,15>();
        }

        void iec_option::t2(std::size_t vl) {
            return set<4, 1, 127>(vl);
        }        
        
        std::size_t iec_option::t3() const {
            return get<5, 1, 127, 20>();
        }

        void iec_option::t3(std::size_t vl) {
            return set<5, 1, 127>(vl);
        }        

        std::size_t iec_option::k() const {
            return get<6, 1, 127,12>();
        }

        void iec_option::k(std::size_t vl) {
            return set<6, 1, 127>(vl);
        }        
        
        std::size_t iec_option::w() const {
            return get<7, 1, 127,8>();
        }

        void iec_option::w(std::size_t vl) {
            return set<7, 1, 127>(vl);
        }             
        
        
        std::string iec_option::to_value() {
            addr(addr());
            cot(cot());
            sector(sector());
            ioa(ioa());
            trycount(trycount());
            t0(t0());      
            t1(t1());      
            t2(t2());      
            t3(t3());      
            k(k());      
            w(w());             
            return opton_;
        }        
        
        
        
        
        
        

        //iec60870_com_option_setter

        boost::system::error_code iec60870_com_option_setter::store(com_port_option& opt, boost::system::error_code & ec) const {
            reset_default_nill(opt);
            /*  switch (link.protocol()) {
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
              }*/

            return boost::system::error_code();
        }





    }
}

