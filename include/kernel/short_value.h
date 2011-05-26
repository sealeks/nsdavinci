/* 
 * File:   short_value.h
 * Author: Alexeev
 *
 * Created on 23 Май 2011 г., 18:09
 */

#ifndef _KERNEL_SHORT_VALUE_H
#define	_KERNEL_SHORT_VALUE_H


#include <kernel/constdef.h>
#include <kernel/utils.h>


namespace dvnci {
    
    typedef struct short_value {
        
        typedef boost::shared_ptr<std::string>         string_ptr;
        
        

        short_value() : value_(to_num64_cast<double > (NULL_DOUBLE)), valid_(0), time_(castnum64_from_datetime(nill_time)), type_(0), error_(0) {}

        short_value(num64 val, tagtype tp, vlvtype vld = FULL_VALID, ns_error err = 0, const datetime& tm = nill_time) :
        value_(val), valid_(vld), time_(castnum64_from_datetime(tm == nill_time ? now() : tm)), type_(tp), error_(err) {}
        
        short_value( bool val) :   
        value_(static_cast<num64> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_DISCRET), error_(0) {};

        short_value( num64 val) :         
        value_(to_num64_cast<num64> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_NUM64), error_(0) {};

        short_value( unum64 val) :
        value_(to_num64_cast<unum64> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_UNUM64), error_(0) {};

        short_value( num32 val) : 
        value_(to_num64_cast<num32> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_NUM32), error_(0) {};    

        short_value( unum32 val) : 
        value_(to_num64_cast<unum32> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_UNUM32), error_(0) {};     

        short_value( num16 val) :
        value_(to_num64_cast<num16> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_NUM16), error_(0) {}; 

        short_value( unum16 val) : 
        value_(to_num64_cast<unum16> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_UNUM16), error_(0) {}; 

        short_value( num8 val) : 
        value_(to_num64_cast<num8> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_NUM8), error_(0) {};     

        short_value( unum8 val) : 
        value_(to_num64_cast<unum8> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_UNUM8), error_(0) {};     

        short_value( float val) : 
        value_(to_num64_cast<float> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_FLOAT), error_(0) {};  

        short_value( double val) :
        value_(to_num64_cast<double> (val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_DOUBLE), error_(0) {};      

        short_value( const datetime& val) : 
        value_(castnum64_from_datetime(val)),  valid_(FULL_VALID) , time_(0), type_(TYPE_TM), error_(0) {};
        
        short_value(const std::string& val) : 
        value_(0),  valid_(FULL_VALID) , time_(0), type_(TYPE_TEXT), error_(0), str_ptr( new std::string(val)) {};  


        template <typename T >
        T value() const {
            return num64_and_type_cast<T > (value_, type_);}

        num64 value64() const {
            return value_;}
        
        void value64(num64 vl) {
            value_=vl;}
      

        void valid(vlvtype val) {
            valid_ = static_cast<num64> (val);}

        vlvtype valid() const {
            return static_cast<vlvtype> (valid_);}

        void type(tagtype val) {
            type_ = static_cast<num64> (val);}

        tagtype type() const {
            return static_cast<tagtype> (type_);}

        ns_error error(ns_error val) {
            error_ = static_cast<num64> (val);
            return static_cast<ns_error> (error_);}

        ns_error error() const {
            return static_cast<ns_error> (error_);}

        void time(const datetime & val) {
            time_ = castnum64_from_datetime(val);}

        datetime time() const {
            return cast_datetime_fromnum64(time_);}

        void time_n64(num64 val) {
            time_ = val;}

        num64 time_n64() const {
            return time_;}

    private:
        num64      value_;
        vlvtype    valid_;
        num64      time_;
        tagtype    type_;
        ns_error   error_;
        string_ptr str_ptr;} *pshort_value;
        
     template <>
     datetime short_value::value<datetime>() const;
     
     template <>
     std::string short_value::value<std::string>() const;
     
} ;

#endif	/* SHORT_VALUE_H */

