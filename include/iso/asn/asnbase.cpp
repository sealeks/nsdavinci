/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include "asnbase.h"

namespace boost {
    namespace asio {
        namespace asn {

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




        }
    }
}

