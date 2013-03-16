/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include <iso/iso.h>

namespace boost {
    namespace itu {

        error_code errorcode_by_reason(octet_type val) {
            switch (val) {
                case DR_REASON_CONGST: return ER_EAGAIN;
                case DR_REASON_ADDRESS: return ER_NAADDRESS;
                case DR_REASON_NORM: return ER_RELEASE;
                case DR_REASON_RCNGS: return ER_REQBUSY;
                case DR_REASON_NEGOT: return ER_REQBUSY;
                default:
                {
                }
            }
            return ER_PROTOCOL;
        }

    }
}
