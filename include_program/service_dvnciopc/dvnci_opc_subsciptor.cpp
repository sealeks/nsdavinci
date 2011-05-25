/* 
 * File:   dvnci_opc_subsciptor.cpp
 * Author: Serg
 * 
 * Created on 23 Июль 2010 г., 18:51
 */

#include "dvnci_opc_subsciptor.h"

namespace dvnci {
    namespace opc {

short_value& operator<<(short_value& lv, const opcvalue_item&  rv){
    return lv;/*short_value(rv.val,rv.type, rv.valid, 0, rv.time);*/} }
}