/* 
 * File:   iec60870_detail.cpp
 * Author: Alexeev
 */

#include <iec60870/iec60870_detail.h>
#include <kernel/basis_iostream.h>



namespace dvnci {
    namespace prot80670 {

        using namespace dvnci::driver;
        //iec60870_com_option_setter

        boost::system::error_code iec60870_com_option_setter::store(com_port_option& opt, boost::system::error_code & ec) const {
                      set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                      rsparitytype tmprty =  NT_RS_EVENPARITY;
                      set_rs232_comoption(opt, 8, tmprty, NT_RS_ONESTOPBIT);
            return boost::system::error_code();
        }





    }
}

