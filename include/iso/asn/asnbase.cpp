//  Copyright 2013 Alexeev Sergey sealeks@mail.ru

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <iso/asn/asnbase.h>
#include "boost/date_time/gregorian/gregorian.hpp"

namespace boost {
    namespace asn1 {

        template <typename T> inline static T string_to(std::string val) {
            std::string::size_type it = val.find_first_not_of('0');
            if (it == std::string::npos)
                return 0;
            val = val.substr(it);
            return boost::lexical_cast<T > (val);
        }

        class_type to_class_type(octet_type vl) {
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


        // relative oid type

        reloid_type::reloid_type(const oidindx_type * vl, std::size_t size) : std::vector<oidindx_type>(vl, vl + size) {
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
                    stream << "." << *it;
            //stream << std::endl;
            return stream;
        }




        /// bitstring type

        bitstring_type::bitstring_type(uint8_t vl, std::size_t unuse) : std::vector<octet_type>(), unuse_(unuse) {
            construct(vl, unuse);
        };

        bitstring_type::bitstring_type(uint16_t vl, std::size_t unuse) : std::vector<octet_type>(), unuse_(unuse) {
            construct(vl, unuse);
        };

        bitstring_type::bitstring_type(uint32_t vl, std::size_t unuse) : std::vector<octet_type>(), unuse_(unuse) {
            construct(vl, unuse);
        };

        bitstring_type::bitstring_type(uint64_t vl, std::size_t unuse) : std::vector<octet_type>(), unuse_(unuse) {
            construct(vl, unuse);
        };

        bitstring_type::bitstring_type(int8_t vl, std::size_t unuse) : std::vector<octet_type>(), unuse_(unuse) {
            construct(*reinterpret_cast<uint8_t*> (&vl), unuse);
        };

        bitstring_type::bitstring_type(int16_t vl, std::size_t unuse) : std::vector<octet_type>(), unuse_(unuse) {
            construct(*reinterpret_cast<uint16_t*> (&vl), unuse);
        };

        bitstring_type::bitstring_type(int32_t vl, std::size_t unuse) : std::vector<octet_type>(), unuse_(unuse) {
            construct(*reinterpret_cast<uint32_t*> (&vl), unuse);
        };

        bitstring_type::bitstring_type(int64_t vl, std::size_t unuse) : std::vector<octet_type>(), unuse_(unuse) {
            construct(*reinterpret_cast<uint64_t*> (&vl), unuse);
        };

        bitstring_type::bitstring_type(const octet_sequnce& vl, std::size_t unuse) : std::vector<octet_type>(), unuse_(unuse) {
            insert_bitstring(vl, unuse);
        };

        bitstring_type::bitstring_type(const std::vector<bool>& vl) : std::vector<octet_type>() {
            construct(vl);
        };

        bitstring_type::bitstring_type(bool vl, std::size_t n) : std::vector<octet_type>(), unuse_(7 - n % 8) {
            if ((vl) && (n < 256)) {
                insert(begin(), (n / 8 + 1), 0);
                back() = (0x1 << (7 - (n % 8)));
            }
        }

        void bitstring_type::insert_bitstring(const octet_sequnce& val, std::size_t unuse) {
            unuse_ = unuse % 8;
            std::copy(val.begin(), val.end(), std::back_inserter(*this));
        };

        bool bitstring_type::bit(std::size_t num) const {
            if (sizebits() > num) {
                octet_type vl = ((num / 8) < size()) ? (operator[](num / 8)) : 0;
                return static_cast<octet_type> (1 << (7 - (num % 8))) & vl;
            }
            return false;
        }

        void bitstring_type::bit(std::size_t num, bool val) {
            if (sizebits() > num) {
                if ((num / 8) < size()) {
                    if (val)
                        operator[](num / 8) |= static_cast<octet_type> (1 << (7 - num % 8));
                    else
                        operator[](num / 8) &= ~static_cast<octet_type> (1 << (7 - num % 8));
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
            bitstring_type::dynamic_bitset_type tmp(sizebits());
            for (std::size_t i = 0; i < sizebits(); ++i)
                tmp.operator [](i) = bit(i);
            return tmp;
        }

        bitstring_type::dynamic_bitset_type bitstring_type::dynamic_bitset() const {
            bitstring_type::dynamic_bitset_type tmp(sizebits());
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

        //bitstring_type::operator octet_sequnce() const{
        //    return  *this;
        //}    

        bitstring_type operator|(const bitstring_type& ls, const bitstring_type& rs) {
            std::size_t mxsize = ls.sizebits() < rs.sizebits() ? rs.sizebits() : ls.sizebits();
            bitstring_type::dynamic_bitset_type lsb = ls.dynamic_bitset();
            bitstring_type::dynamic_bitset_type rsb = rs.dynamic_bitset();
            lsb.resize(mxsize, false);
            rsb.resize(mxsize, false);
            return lsb | rsb;
        }

        bitstring_type operator&(const bitstring_type& ls, const bitstring_type& rs) {
            std::size_t mxsize = ls.sizebits() < rs.sizebits() ? rs.sizebits() : ls.sizebits();
            bitstring_type::dynamic_bitset_type lsb = ls.dynamic_bitset();
            bitstring_type::dynamic_bitset_type rsb = rs.dynamic_bitset();
            lsb.resize(mxsize, false);
            rsb.resize(mxsize, false);
            return lsb & rsb;
        }

        bitstring_type operator^(const bitstring_type& ls, const bitstring_type& rs) {
            std::size_t mxsize = ls.sizebits() < rs.sizebits() ? rs.sizebits() : ls.sizebits();
            bitstring_type::dynamic_bitset_type lsb = ls.dynamic_bitset();
            bitstring_type::dynamic_bitset_type rsb = rs.dynamic_bitset();
            lsb.resize(mxsize, false);
            rsb.resize(mxsize, false);
            return lsb ^ rsb;
        }

        void bitstring_type::construct(const std::vector<bool>& vl) {
            assign((vl.size() % 8) ? (vl.size() / 8 + 1) : (vl.size() / 8), 0);
            unuse_ = 8 - (vl.size() % 8);
            std::size_t sz = 0;
            for (std::vector<bool>::const_iterator it = vl.begin(); it != vl.end(); ++it)
                bit(sz++, *it);
        };

        void bitstring_type::construct(const dynamic_bitset_type& vl) {
            assign((vl.size() % 8) ? (vl.size() / 8 + 1) : (vl.size() / 8), 0);
            unuse_ = 8 - (vl.size() % 8);
            std::size_t sz = 0;
            for (std::size_t it = 0; it < vl.size(); ++it)
                bit(sz++, vl.operator [](it));
        };

        std::ostream& operator<<(std::ostream& stream, const bitstring_type& vl) {
            std::vector<bool> val = vl.operator bitstring_type::bool_vector_type();
            for (std::vector<bool>::const_iterator it = val.begin(); it != val.end(); ++it)
                stream << (*it ? '1' : '0');
            stream << std::endl;
            return stream;
        }

        // octetstring_type

        std::ostream& operator<<(std::ostream& stream, const octetstring_type& vl) {
            stream << std::string(vl.begin(), vl.end());
            return stream;
        }

        // utf8string_type

        std::ostream& operator<<(std::ostream& stream, const utf8string_type& vl) {
            stream << std::string(vl.begin(), vl.end());
            return stream;
        }


        // time types      

        static utctime_type to_z_impltime(const std::string& val, const utctime_type& tm) {
            if (val.empty())
                return tm;
            if (val.size() != 5)
                return utctime_type();
            switch (val[0]) {
                case '+':
                {
                    return (tm + (boost::posix_time::hours(string_to<int>(val.substr(1, 2))) + boost::posix_time::minutes(string_to<int>(val.substr(3, 2)))));
                }
                case '-':
                {
                    return (tm - (boost::posix_time::hours(string_to<int>(val.substr(1, 2))) + boost::posix_time::minutes(string_to<int>(val.substr(3, 2)))));
                }
            }
            return utctime_type();
        }

        static octet_sequnce from_impltime(const utctime_type& val, bool full) {
            octet_sequnce rslt;
            if (!val.is_special()) {
                std::string tmp = boost::posix_time::to_iso_string(val) + "Z";
                //std::string tmp = boost::posix_time::to_iso_string(val) + "+0400";
                //std::string tmp = "201211301232.51+0400";
                if (tmp.find('T') != std::string::npos)
                    tmp.erase(tmp.find('T'), 1);
                if (!full) {
                    if (tmp.size() > 2)
                        std::copy(tmp.begin() + 2, tmp.end(), std::back_inserter(rslt));
                }
                else
                    std::copy(tmp.begin(), tmp.end(), std::back_inserter(rslt));
            }
            return rslt;
        }

        static utctime_type to_impl_time(const octet_sequnce& val, bool full) {
            if (val.size() > 8) {
                try {
                    std::string tmp(val.begin(), val.end());
                    std::string::size_type it = tmp.find('z');
                    std::string zdelt = "";
                    if (it == std::string::npos)
                        it = tmp.find('Z');
                    if (it == std::string::npos) {
                        it = tmp.find('-');
                        if (it != std::string::npos) {
                            zdelt = tmp.substr(it);
                            tmp = tmp.substr(0, it);
                        }
                        else {
                            it = tmp.find('+');
                            if (it != std::string::npos) {
                                zdelt = tmp.substr(it);
                                tmp = tmp.substr(0, it);
                            }
                        }
                    }
                    else
                        tmp = tmp.substr(0, it);

                    if (tmp.empty())
                        return utctime_type();

                    if (!full)
                        tmp = ((tmp[0] == '9') || (tmp[0] == '8')) ? ("19" + tmp) : ("20" + tmp);

                    if (tmp.size() < 8)
                        return utctime_type();

                    utctime_type rslt(boost::gregorian::date(string_to<int>(tmp.substr(0, 4)), string_to<int>(tmp.substr(4, 2)), string_to<int>(tmp.substr(6, 2))));

                    if (tmp.size() == 8)
                        return zdelt.empty() ? rslt : to_z_impltime(zdelt, rslt);
                    else
                        tmp = tmp.substr(8);

                    if (tmp.size() < 2)
                        return utctime_type();

                    rslt += boost::posix_time::hours(string_to<int>(tmp.substr(0, 2)));

                    if (tmp.size() == 2)
                        return zdelt.empty() ? rslt : to_z_impltime(zdelt, rslt);
                    else
                        tmp = tmp.substr(2);

                    if (tmp[0] == '.') {
                        return zdelt.empty() ? (rslt + boost::posix_time::millisec(static_cast<int> (3600000 * string_to<double>("0" + tmp)))) :
                                to_z_impltime(zdelt, (rslt + boost::posix_time::millisec(static_cast<int> (3600000 * string_to<double>("0" + tmp)))));
                    }
                    else {
                        if (tmp.size() < 2)
                            return utctime_type();
                    }

                    rslt += boost::posix_time::minutes(string_to<int>(tmp.substr(0, 2)));

                    if (tmp.size() == 2)
                        return zdelt.empty() ? rslt : to_z_impltime(zdelt, rslt);
                    else
                        tmp = tmp.substr(2);

                    if (tmp[0] == '.') {
                        return zdelt.empty() ? (rslt + boost::posix_time::microsec(static_cast<int> (60000000 * string_to<double>("0" + tmp)))) :
                                to_z_impltime(zdelt, (rslt + boost::posix_time::microsec(static_cast<int> (60000000 * string_to<double>("0" + tmp)))));
                    }
                    else {
                        if (tmp.size() < 2)
                            return utctime_type();
                    }

                    rslt += boost::posix_time::seconds(string_to<int>(tmp.substr(0, 2)));

                    if (tmp.size() == 2)
                        return zdelt.empty() ? rslt : to_z_impltime(zdelt, rslt);
                    else
                        tmp = tmp.substr(2);

                    if (tmp[0] != '.')
                        return utctime_type();


                    if (tmp.size() == 1)
                        return zdelt.empty() ? rslt : to_z_impltime(zdelt, rslt);

                    rslt += boost::posix_time::microsec(static_cast<int> (string_to<double>("0" + tmp)*1000000));

                    return zdelt.empty() ? rslt : to_z_impltime(zdelt, rslt);

                }
                catch (...) {
                }
            }
            return utctime_type();
        }

        octet_sequnce from_utctime(const utctime_type& val) {
            return from_impltime(val, false);
        }

        utctime_type to_utctime(const octet_sequnce& val) {
            return to_impl_time(val, false);
        }

        octet_sequnce from_gentime(const gentime_type& val) {
            return from_impltime(val.value(), true);
        }

        gentime_type to_gentime(const octet_sequnce& val) {
            return gentime_type(to_impl_time(val, true));
        }

        std::ostream& operator<<(std::ostream& stream, const gentime_type& vl) {
            return stream << vl.value();
        }
        
    }
}

