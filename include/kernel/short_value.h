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
#include <kernel/error.h>


namespace dvnci {

    typedef struct short_value {

        typedef boost::shared_ptr<std::string> string_ptr;

        short_value() : value_(num64_cast<double > (NULL_DOUBLE)), valid_(0), time_(castnum64_from_datetime(nill_time)), type_(0), error_(ERROR_NODATA) {
        }

        short_value(num64 val, tagtype tp, vlvtype vld = FULL_VALID, ns_error err = 0, const datetime& tm = nill_time) :
        value_(val), valid_(vld), time_(castnum64_from_datetime(tm == nill_time ? now() : tm)), type_(tp), error_(err) {
        }

        short_value(bool val) :
        value_(static_cast<num64> (val)), valid_(FULL_VALID), time_(0), type_(TYPE_DISCRET), error_(0) {
        };

        short_value(const num64& val) :
        value_(num64_cast<num64 > (val)), valid_(FULL_VALID), time_(0), type_(TYPE_NUM64), error_(0) {
        };

        short_value(const unum64& val) :
        value_(num64_cast<unum64 > (val)), valid_(FULL_VALID), time_(0), type_(TYPE_UNUM64), error_(0) {
        };

        short_value(const num32& val) :
        value_(num64_cast<num32 > (val)), valid_(FULL_VALID), time_(0), type_(TYPE_NUM32), error_(0) {
        };

        short_value(const unum32& val) :
        value_(num64_cast<unum32 > (val)), valid_(FULL_VALID), time_(0), type_(TYPE_UNUM32), error_(0) {
        };

        short_value(const num16& val) :
        value_(num64_cast<num16 > (val)), valid_(FULL_VALID), time_(0), type_(TYPE_NUM16), error_(0) {
        };

        short_value(const unum16& val) :
        value_(num64_cast<unum16 > (val)), valid_(FULL_VALID), time_(0), type_(TYPE_UNUM16), error_(0) {
        };

        short_value(const num8& val) :
        value_(num64_cast<num8 > (val)), valid_(FULL_VALID), time_(0), type_(TYPE_NUM8), error_(0) {
        };

        short_value(const unum8& val) :
        value_(num64_cast<unum8 > (val)), valid_(FULL_VALID), time_(0), type_(TYPE_UNUM8), error_(0) {
        };

        short_value(const float& val) :
        value_(num64_cast<float> (val)), valid_(FULL_VALID), time_(0), type_(TYPE_FLOAT), error_(0) {
        };

        short_value(const double& val) :
        value_(num64_cast<double> (val)), valid_(FULL_VALID), time_(0), type_(TYPE_DOUBLE), error_(0) {
        };

        short_value(const double& val, const datetime& dtm) :
        value_(num64_cast<double> (val)), valid_(FULL_VALID), time_(0), type_(TYPE_DOUBLE), error_(0) {
            time(dtm);
        };

        short_value(const datetime & val) :
        value_(castnum64_from_datetime(val)), valid_(FULL_VALID), time_(0), type_(TYPE_TM), error_(0) {
        };

        short_value(const std::string & val, vlvtype vld = FULL_VALID, ns_error err = 0, const datetime& tm = nill_time) :
        value_(0), valid_(vld), time_(castnum64_from_datetime(tm == nill_time ? now() : tm)),
        type_(TYPE_TEXT), error_(err), str_ptr(new std::string(val)) {
        };

        short_value(const std::wstring & val, vlvtype vld = FULL_VALID, ns_error err = 0, const datetime& tm = nill_time) :
        value_(0), valid_(vld), time_(castnum64_from_datetime(tm == nill_time ? now() : tm)),
        type_(TYPE_TEXT), error_(err), str_ptr(new std::string(wstr_to_utf8(val))) {
        };

        template<typename T>
                static short_value create_error(ns_error err, T val = 0, vlvtype vld = NULL_VALID) {
            short_value tmp(val);
            tmp.valid(vld);
            tmp.error(err);
            return tmp;
        }

        template<typename T>
                static short_value create_timed(T val, const datetime & tm, vlvtype vld = FULL_VALID, ns_error err=0) {
            short_value tmp(val);
            tmp.valid(vld);
            tmp.time(tm);
            tmp.error(err);
            return tmp;
        }

        template <typename T >
                T value() const {
            if (type_ != TYPE_TEXT)
                return num64_and_type_cast<T > (value_, type_);
            T tmp = 0;
            if (str_to<T > (value<std::string > (), tmp)) {
                return tmp;
            }
            error_ = ERROR_IO_DATA_CONV;
            return 0;
        }

        num64 value64() const {
            return value_;
        }

        void value64(num64 vl) {
            value_ = vl;
        }

        void valid(vlvtype val) {
            valid_ = static_cast<num64> (val);
        }

        vlvtype valid() const {
            return static_cast<vlvtype> (valid_);
        }

        void type(tagtype val) {
            type_ = static_cast<num64> (val);
        }

        tagtype type() const {
            return static_cast<tagtype> (type_);
        }

        ns_error error(ns_error val) {
            error_ = static_cast<num64> (val);
            return static_cast<ns_error> (error_);
        }

        ns_error error() const {
            return static_cast<ns_error> (error_);
        }

        void time(const datetime & val) {
            time_ = castnum64_from_datetime(val);
        }

        datetime time() const {
            return cast_datetime_fromnum64(time_);
        }

        void time_n64(num64 val) {
            time_ = val;
        }

        num64 time_n64() const {
            return time_;
        }

        ns_error covert_to_bcd();

        std::string format(const std::string& frmt) {
            return num64_and_type_cast(value_, type_, frmt);
        }

        friend bool operator!=(const short_value& ls, const short_value& rs) {
            if ((ls.type_ == rs.type_) && (ls.valid_ == rs.valid_) && (ls.error_ == rs.error_)) {
                return (ls.type_ == TYPE_TEXT) ?
                        (((ls.str_ptr && rs.str_ptr) && (*ls.str_ptr != *rs.str_ptr))) :
                        (ls.value_ != rs.value_);
            }
            return true;
        }

        friend bool operator==(const short_value& ls, const short_value& rs) {
            return !(ls != rs);
        }

        bool nan() const {
            return ((!type_) && (value<double>() != value<double>()));
        }

        bool null() const {
            return ((!error_) && (!valid_));
        }



    private:


        num64 value_;
        vlvtype valid_;
        num64 time_;
        tagtype type_;
        mutable ns_error error_;
        string_ptr str_ptr;
    } *pshort_value;

    template <>
    datetime short_value::value<datetime>() const;

    template <>
    std::string short_value::value<std::string>() const;

    template <>
    std::wstring short_value::value<std::wstring>() const;

    typedef std::vector<short_value> short_value_vect;

    typedef std::pair<std::string, num32> tag_info_pair;


    typedef std::pair<tag_info_pair, short_value_vect> short_values_row;

    struct tag_info_pair_less :
    public std::binary_function<tag_info_pair, tag_info_pair, bool> {

        bool operator()(const tag_info_pair& ls,
                const tag_info_pair& rs) const {
            return ls.first < rs.first;
        }
    };

    typedef std::map< tag_info_pair, short_value_vect, tag_info_pair_less > short_values_table;


};

#endif	/* SHORT_VALUE_H */

