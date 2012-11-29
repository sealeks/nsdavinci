/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include "asnbase.h"
#include "boost/date_time/gregorian/gregorian.hpp"

namespace boost {
    namespace asio {
        namespace asn {

            /*  template <typename T> inline static T string_to(std::string val) {
                       if (val.find_first_of('0')!=0){
                           if (val.find_first_of('0')==std::string::npos){
                               return 0;}
                           else
                               val = val.substr(val.find_first_of('0'));
                       }
                       return  boost::lexical_cast<T > (val);
               } */


            class_type to_class_type( int8_t vl) {
                switch (vl & 0xC0) {
                    case 0x40: return APPLICATION_CLASS;
                    case 0x80: return CONTEXT_CLASS;
                    case 0xC0: return PRIVATE_CLASS;
                    default:
                    {
                    }
                }
                return UNIVERSAL_CLASS;
            }


            // oid type

            oid_type::oid_type(const oidindx_type *  vl, std::size_t size) : std::vector<oidindx_type>(vl, vl + size) {
            }

            oid_type::oid_type(const boost::array<oidindx_type, 2 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            oid_type::oid_type(const boost::array<oidindx_type, 3 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            oid_type::oid_type(const boost::array<oidindx_type, 4 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            oid_type::oid_type(const boost::array<oidindx_type, 5 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            oid_type::oid_type(const boost::array<oidindx_type, 6 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            oid_type::oid_type(const boost::array<oidindx_type, 7 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            oid_type::oid_type(const boost::array<oidindx_type, 8 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            oid_type::oid_type(const boost::array<oidindx_type, 9 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            oid_type::oid_type(const boost::array<oidindx_type, 10 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            std::ostream& operator<<(std::ostream& stream, const oid_type& vl) {
                for (oid_type::const_iterator it = vl.begin(); it != vl.end(); ++it)
                    if (it == vl.begin())
                        stream << *it;
                    else
                        stream <<  "." << *it;
                //stream << std::endl;
                return stream;
            }

            // relative oid type

            reloid_type::reloid_type(const oidindx_type *  vl, std::size_t size) : std::vector<oidindx_type>(vl, vl + size) {
            }

            reloid_type::reloid_type(const boost::array<oidindx_type, 2 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            reloid_type::reloid_type(const boost::array<oidindx_type, 3 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            reloid_type::reloid_type(const boost::array<oidindx_type, 4 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            reloid_type::reloid_type(const boost::array<oidindx_type, 5 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            reloid_type::reloid_type(const boost::array<oidindx_type, 6 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            reloid_type::reloid_type(const boost::array<oidindx_type, 7 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            reloid_type::reloid_type(const boost::array<oidindx_type, 8 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            reloid_type::reloid_type(const boost::array<oidindx_type, 9 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            reloid_type::reloid_type(const boost::array<oidindx_type, 10 > & vl) : std::vector<oidindx_type>(vl.begin(), vl.end()) {
            }

            std::ostream& operator<<(std::ostream& stream, const reloid_type& vl) {
                for (reloid_type::const_iterator it = vl.begin(); it != vl.end(); ++it)
                    if (it == vl.begin())
                        stream << *it;
                    else
                        stream <<  "." << *it;
                //stream << std::endl;
                return stream;
            }




            /// bitstring type

            bitstring_type::bitstring_type(uint8_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                construct(vl, unuse);
            };

            bitstring_type::bitstring_type(uint16_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                construct(vl, unuse);
            };

            bitstring_type::bitstring_type(uint32_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                construct(vl, unuse);
            };

            bitstring_type::bitstring_type(uint64_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                construct(vl, unuse);
            };

            bitstring_type::bitstring_type(int8_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                construct(*reinterpret_cast<uint8_t*> (&vl), unuse);
            };

            bitstring_type::bitstring_type(int16_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                construct(*reinterpret_cast<uint16_t*> (&vl), unuse);
            };

            bitstring_type::bitstring_type(int32_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                construct(*reinterpret_cast<uint32_t*> (&vl), unuse);
            };

            bitstring_type::bitstring_type(int64_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                construct(*reinterpret_cast<uint64_t*> (&vl), unuse);
            };

            bitstring_type::bitstring_type(const row_type& vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                insert_bitstring(vl, unuse);
            };

            bitstring_type::bitstring_type(const std::vector<bool>& vl) : std::vector<int8_t>() {
                construct(vl);
            };

            void  bitstring_type::insert_bitstring(const row_type& val, std::size_t unuse) {
                unuse_ = unuse % 8;
                std::copy(val.begin(), val.end(), std::back_inserter(*this));
            };

            bool bitstring_type::bit(std::size_t num) const {
                if  (sizebits() > num) {
                    int8_t vl = ((num / 8) < size()) ?  (operator[](num / 8)) : 0;
                    return static_cast<int8_t> (1 << (7 - (num % 8))) & vl;
                }
                return false;
            }

            void  bitstring_type::bit(std::size_t num, bool val) {
                if  (sizebits() > num) {
                    if ((num / 8) < size()) {
                        if (val)
                            operator[](num / 8) |= static_cast<int8_t> (1 << ( 7 - num % 8));
                        else
                            operator[](num / 8) &= ~static_cast<int8_t> (1 << (7 - num % 8));
                    }
                }
            }

            bitstring_type::operator bitstring_type::bool_vector_type() const {
                bitstring_type::bool_vector_type tmp;
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.push_back(bit(i));
                return tmp;
            }

            bitstring_type::operator bitstring_type::dynamic_bitset_type() const {
                bitstring_type::dynamic_bitset_type  tmp(sizebits());
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.operator [](i) = bit(i);
                return tmp;
            }

            bitstring_type::operator uint8_t() const {
                bool_vector_type tmp;
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.push_back(bit(i));
                return return_int<uint8_t > ();
            }

            bitstring_type::operator uint16_t() const {
                bool_vector_type tmp;
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.push_back(bit(i));
                return return_int<uint16_t > ();
            }

            bitstring_type::operator uint32_t() const {
                bool_vector_type tmp;
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.push_back(bit(i));
                return return_int<uint16_t > ();
            }

            bitstring_type::operator uint64_t() const {
                bool_vector_type tmp;
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.push_back(bit(i));
                return return_int<uint16_t > ();
            }

            bitstring_type::operator int8_t() const {
                bool_vector_type tmp;
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.push_back(bit(i));
                return return_int<int8_t > ();
            }

            bitstring_type::operator int16_t() const {
                bool_vector_type tmp;
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.push_back(bit(i));
                return return_int<int16_t > ();
            }

            bitstring_type::operator int32_t() const {
                bool_vector_type tmp;
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.push_back(bit(i));
                return return_int<int16_t > ();
            }

            bitstring_type::operator int64_t() const {
                bool_vector_type tmp;
                for (std::size_t i = 0; i < sizebits(); ++i)
                    tmp.push_back(bit(i));
                return return_int<int16_t > ();
            }

            //bitstring_type::operator row_type() const{
            //    return  *this;
            //}               

            void bitstring_type::construct(const std::vector<bool>& vl) {
                assign( (vl.size() % 8) ? (vl.size() / 8 + 1) : (vl.size() / 8), 0);
                unuse_ = 8 - (vl.size() % 8);
                std::size_t sz = 0;
                for (std::vector<bool>::const_iterator it = vl.begin(); it != vl.end(); ++it)
                    bit(sz++, *it);
            };

            void bitstring_type::construct(const dynamic_bitset_type& vl) {
                assign( (vl.size() % 8) ? (vl.size() / 8 + 1) : (vl.size() / 8), 0);
                unuse_ = 8 - (vl.size() % 8);
                std::size_t sz = 0;
                for (std::size_t it = 0; it < vl.size() ; ++it)
                    bit(sz++, vl.operator [](it));
            };

            std::ostream& operator<<(std::ostream& stream, const bitstring_type& vl) {
                std::vector<bool> val = vl.operator  bitstring_type::bool_vector_type();
                for (std::vector<bool>::const_iterator it = val.begin(); it != val.end(); ++it)
                    stream << (*it ? '1' : '0');
                stream << std::endl;
                return stream;
            }

            // octetstring_type

            std::ostream& operator<<(std::ostream& stream, const octetstring_type& vl) {
                stream <<  std::string(vl.begin(), vl.end());
                return stream;
            }

            // utf8string_type

            std::ostream& operator<<(std::ostream& stream, const utf8string_type& vl) {
                stream <<  std::string(vl.begin(), vl.end());
                return stream;
            }


            // time types            

            row_type from_gentime(const utctime_type& val) {
                row_type rslt;
                if (!val.is_special()) {
                    std::string tmp = boost::posix_time::to_iso_string(val);
                    if (tmp.find('T') != std::string::npos)
                        tmp.erase(tmp.find('T'), 1);
                    if (tmp.size() > 2)
                        std::copy(tmp.begin() + 2, tmp.end(), std::back_inserter(rslt));
                }
                return rslt;
            }

            utctime_type to_gentime(const row_type& val) {
                if (val.size() < 8) {

                    try {
                        std::string zdelt = "";
                        std::string tmp(val.begin(), val.end());
                        std::string::size_type  it = tmp.find('z');
                        if (it == std::string::npos)
                            it = tmp.find('Z');
                        if (it == std::string::npos) {
                            it = tmp.find('-');
                            if (it != std::string::npos) {
                                zdelt = tmp.substr(it + 0);
                                zdelt = (zdelt.find_first_not_of('0') != std::string::npos) ? ("-" + zdelt.substr(zdelt.find_first_not_of('0'))) : "";
                                tmp = tmp.substr(0, it);
                            }
                            else {
                                it = tmp.find('+');
                                if (it != std::string::npos) {
                                    zdelt = tmp.substr(it + 1);
                                    zdelt = (zdelt.find_first_not_of('0') != std::string::npos) ? ("+" + zdelt.substr(zdelt.find_first_not_of('0'))) : "";
                                    tmp = tmp.substr(0, it);
                                }
                            }
                        }
                        else
                            tmp = tmp.substr(0, it);
                        
                        if (tmp.size() < 1)
                            return utctime_type();
                        
                        tmp = ((tmp[0]=='9') || (tmp[0]=='8')) ? ("19" + tmp) : ("20"+tmp);  
                        
                        if (tmp.size() < 8)
                            return utctime_type();
                        
                        std::string rslt = tmp.substr(0, 8) + "T" + tmp.substr(8);
                        
                        return  boost::posix_time::from_iso_string(rslt);
                        
                    }
                    catch (...) {
                    }
                }
                return utctime_type();
            }




        }
    }
}

