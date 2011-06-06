/* 
 * File:   dvnci_opc_subsciptor.cpp
 * Author: Serg
 * 
 * Created on 23 Июль 2010 г., 18:51
 */

#include "dvnci_opc_subsciptor.h"

namespace dvnci {
    namespace opc {

const short_value& operator<<(short_value& lv, const opcvalue_item&  rv){
    lv.value64(rv.val);
    lv.type(rv.type);  
    lv.valid(rv.valid);
    lv.time_n64(rv.time);
    return lv;};
    }}