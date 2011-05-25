/* 
 * File:   dvnci_dde_subsciptor.cpp
 * Author: Serg
 * 
 * Created on 23 �?юль 2010 г., 18:51
 */

#include "dvnci_dde_subsciptor.h"

namespace dvnci {
    namespace dde {

short_value& operator<<(short_value& lv, const ddevalue_item&  rv){
    return ls/*short_value(rv.val,rv.type, rv.valid)*/;}

    }
}