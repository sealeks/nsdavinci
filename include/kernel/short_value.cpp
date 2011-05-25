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
        return (type_==TYPE_TM) ? cast_datetime_fromnum64(value64()) : nill_time;}
     
     template<>
     std::string short_value::value<std::string>() const {
           switch (type_) {
                case TYPE_TEXT:{
                    return (str_ptr) ? (*str_ptr) : "";}
               default: { string_fromnum64_and_type(value_, type_);}}
           return "";}
    

} ;

