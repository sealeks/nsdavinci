/* 
 * File:   iec60870_detail.cpp
 * Author: Alexeev
 */

#include "iec60870_detail.h"

namespace dvnci {
    namespace prot80670 {
        
        //    iec_option

        

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

