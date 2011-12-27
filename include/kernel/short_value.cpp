/* 
 * File:   short_value.cpp
 * Author: Alexeev
 * 
 * Created on 23 Май 2011 г., 18:09
 */

#include <kernel/short_value.h>


namespace dvnci {

    template<>
    datetime short_value::value<datetime>() const {
        return (type_ == TYPE_TM) ? cast_datetime_fromnum64(value64()) : nill_time;}
    
    

    template<>
    std::string short_value::value<std::string>() const {
        switch (type_) {
            case TYPE_TEXT:{
                return (str_ptr) ? (*str_ptr) : "";}
            default:{
                return num64_and_type_cast<std::string > (value_, type_);}}
        return "";}
    
    template<>
    std::wstring short_value::value<std::wstring>() const {
        switch (type_) {
            case TYPE_TEXT:{
                return (str_ptr) ? utf8_to_wstr(*str_ptr) : L"";}
            default:{
                return num64_and_type_cast<std::wstring > (value_, type_);}}
        return L"";}
    
    
    
    

    ns_error short_value::covert_to_bcd() {
        switch (type()) {
            case TYPE_DISCRET:{
                return error();}
            case TYPE_NUM64:{
                num64 tmp = value<num64 > ();
                if (!dec_to_bcd<num64 > (tmp)) {
                    error(ERROR_IO_DATA_CONV);}
                else {
                    *this = short_value(tmp);}
                return error();}
            case TYPE_UNUM64:{
                unum64 tmp = value<unum64 > ();
                if (!dec_to_bcd<unum64 > (tmp)) {
                    error(ERROR_IO_DATA_CONV);}
                else {
                    *this = short_value(tmp);}
                return error();}
            case TYPE_NUM32:{
                num32 tmp = value<num32 > ();
                if (!dec_to_bcd<num32 > (tmp)) {
                    error(ERROR_IO_DATA_CONV);}
                else {
                    *this = short_value(tmp);}
                return error();}
            case TYPE_UNUM32:{
                unum32 tmp = value<unum32 > ();
                if (!dec_to_bcd<unum32 > (tmp)) {
                    error(ERROR_IO_DATA_CONV);}
                else {
                    *this = short_value(tmp);}
                return error();}
            case TYPE_NUM16:{
                num16 tmp = value<num16 > ();
                if (!dec_to_bcd<num16 > (tmp)) {
                    error(ERROR_IO_DATA_CONV);}
                else {
                    *this = short_value(tmp);}
                return error();}
            case TYPE_UNUM16:{
                unum16 tmp = value<unum16 > ();
                if (!dec_to_bcd<unum16 > (tmp)) {
                    error(ERROR_IO_DATA_CONV);}
                else {
                    *this = short_value(tmp);}
                return error();}
            case TYPE_NUM8:{
                num8 tmp = value<num8 > ();
                if (!dec_to_bcd<num8 > (tmp)) {
                    error(ERROR_IO_DATA_CONV);}
                else {
                    *this = short_value(tmp);}
                return error();}
            case TYPE_UNUM8:{
                unum8 tmp = value<unum8 > ();
                if (!dec_to_bcd<unum8 > (tmp)) {
                    error(ERROR_IO_DATA_CONV);}
                else {
                    *this = short_value(tmp);}
                return error();}
            case TYPE_NODEF:
            case TYPE_DOUBLE:
            case TYPE_FLOAT:{
                unum64 tmp = value<unum64 > ();
                if (!dec_to_bcd<unum64 > (tmp)) {
                    error(ERROR_IO_DATA_CONV);}
                else {
                    *this = short_value(tmp);}
                return error();};
            default:{
                error(ERROR_IO_DATA_CONV);}}
        return error();}
    


} ;

