/* 
 * File:   asnbase.cpp
 * Author: sealeks
 * 
 * Created on 2 Ноябрь 2012 г., 0:39
 */

#include "itu_X690.h"

namespace boost {
    namespace asio {
        namespace asn {
            namespace x690 {

                void endian_conv(row_type& val) {
#ifdef BIG_ENDIAN_ARCHITECTURE                               
#else
                    std::reverse(val.begin(), val.end());
#endif               
                }

                row_type endian_conv_conv(const row_type& val) {
#ifdef BIG_ENDIAN_ARCHITECTURE
                    return val;
#else
                    row_type tmp(val.size());
                    std::copy(val.rbegin(), val.rend(), std::back_inserter(tmp));
                    return tmp;
#endif                                
                }

                void endian_push_pack(const row_type& val,  row_type& dst) {
#ifdef BIG_ENDIAN_ARCHITECTURE
                    std::copy(val.begin(), val.end(), std::back_inserter(dst))
#else
                    std::copy(val.rbegin(), val.rend(), std::back_inserter(dst));
#endif    
                }


                /////////////////////////////

                template<>
                std::size_t to_x690_cast(int8_t val, row_type& src) {
                    src.push_back(static_cast<row_type::value_type> (0xFF & val));
                    return 1;
                }

                template<>
                std::size_t to_x690_cast(uint8_t val, row_type& src) {
                    return to_x690_cast(static_cast<int16_t> (val), src) ;
                }


                /// id class

                std::size_t to_x690_cast(const tag& val, row_type& src) {
                    if (val.simpleid()) {
                        src.push_back(static_cast<row_type::value_type> (val.simpleid()));
                        return 1;
                    }
                    else {
                        id_type id_ = val.id();
                        row_type tmp;
                        src.push_back (static_cast<row_type::value_type> (0x1F | val.mask()));
                        while (id_) {
                            tmp.push_back(static_cast<row_type::value_type> ((id_ & 0x7F) | CONTENT_CONIIUE));
                            id_  >>= 7;
                        }
                        endian_push_pack(tmp, src);
                        if (tmp.size())
                            src.back() &= static_cast<row_type::value_type> (0x7F);
                        return (src.size() + 1);
                    }
                }

                row_type to_x690_cast(const tag& val) {
                    row_type tmp;
                    to_x690_cast(val, tmp);
                    return tmp;
                }


                ///////////////////////////////////////////////////////////////////////////////////
                // size_class to X.690

                std::size_t to_x690_cast(const size_class& val, row_type& src) {
                    if (!val.undefsize()) {
                        if (val.size() < MAX_SIMPLELENGTH_SIZE ) {
                            src.push_back (static_cast<row_type::value_type> ( static_cast<row_type::value_type> (val.size())));
                            return 1;
                        }
                        else {
                            row_type tmp;
                            size_type vl = val.size();
                            while (vl) {
                                tmp.push_back(static_cast<row_type::value_type> (0xFF & vl));
                                vl  >>= 8;
                            }
                            src.push_back (static_cast<row_type::value_type> ( CONTENT_CONIIUE  | static_cast<row_type::value_type> (tmp.size())));
                            endian_push_pack(tmp, src);
                            return (src.size() + 1);
                        }
                    }
                    else {
                        src.push_back (static_cast<row_type::value_type> ( static_cast<row_type::value_type> (UNDEF_BLOCK_SIZE)));
                        return 1;
                    }
                }

                row_type to_x690_cast(const size_class& val) {
                    row_type tmp;
                    to_x690_cast(val, tmp);
                    return tmp;
                }


                //// real cast

                template<typename T, typename B, std::size_t MANT, std::size_t EXPB>
                static std::size_t to_x690_cast_realimpl(T val, row_type& src) {
                    std::size_t strtsz = src.size();
                    if (val == 0)
                        return 0;
                    if (val != val) {
                        src.push_back(static_cast<row_type::value_type> (NAN_REAL_ID));
                        return 1;
                    }
                    if (std::numeric_limits<T>::infinity() == val) {
                        src.push_back(static_cast<row_type::value_type> (INFINITY_REAL_ID));
                        return 1;
                    }
                    if (-std::numeric_limits<T>::infinity() == val) {
                        src.push_back(static_cast<row_type::value_type> (NEGATINFINITY_REAL_ID));
                        return 1;
                    }
                    if (val == -0) {
                        src.push_back(static_cast<row_type::value_type> (NEGATNULL_REAL_ID));
                        return 1;
                    }
                    row_type tmp;
                    bool negat = false;
                    B  base0 = *reinterpret_cast<B*> (&val);
                    if (base0 < 0) {
                        negat = true;
                        base0 &= ~(B(1) << (sizeof (B)*8 - 1));
                    }

                    B  base =  ~(B(1) << (sizeof (B)*8 - 1));
                    base >>= (sizeof (B)*8 - MANT - 1);
                    base &= base0;
                    base |= (B(1) << MANT);

                    int32_t  exp = static_cast<int32_t> (base0 >> MANT) - MANT - EXPB;

                    row_type::value_type sign = static_cast<row_type::value_type> (0x80  | ((negat) ? 0x40 : 0x0));

                    while (!static_cast<row_type::value_type> (base & '\xFF')) {
                        exp += 8;
                        base = base >> 8;
                    }

                    while (!static_cast<row_type::value_type> (base & '\x1')) {
                        exp += 1;
                        base = base >> 1;
                    }

                    tmp.clear();
                    std::size_t expsz = to_x690_cast(exp, tmp);

                    //if (!expsz) throw;

                    switch (expsz) {
                        case 1:
                        {
                            src.push_back(static_cast<row_type::value_type> (sign));
                            break;
                        }
                        case 2:
                        {
                            sign |= 0x1;
                            src.push_back(static_cast<row_type::value_type> (sign));
                            break;
                        }
                        case 3:
                        {
                            sign |= 0x2;
                            src.push_back(static_cast<row_type::value_type> (sign));
                            break;
                        }
                        default:
                        {
                            src.push_back(static_cast<row_type::value_type> (expsz));
                        }
                    }

                    std::copy(tmp.begin(), tmp.end(), std::back_inserter(src));


                    tmp.clear();
                    while (base) {
                        tmp.push_back(static_cast<row_type::value_type> (base) & '\xFF');
                        base = base >> 8;
                    }
                    endian_push_pack(tmp, src);
                    return (src.size() - strtsz);
                }

                template<>
                std::size_t to_x690_cast(double val, row_type& src) {
                    return to_x690_cast_realimpl<double, int64_t, DOUBLE_MANTISSA_SIZE, DOUBLE_EXPONENTA_DELT > (val, src);
                }

                template<>
                std::size_t to_x690_cast(long double val, row_type& src) {
                    return to_x690_cast_realimpl<double, int64_t, DOUBLE_MANTISSA_SIZE, DOUBLE_EXPONENTA_DELT > (static_cast<double> (val), src);
                }

                template<>
                std::size_t to_x690_cast(float val, row_type& src) {
                    return to_x690_cast_realimpl<float, int32_t, FLOAT_MANTISSA_SIZE, FLOAT_EXPONENTA_DELT > (val, src);
                }

                //// bool cast

                template<>
                std::size_t to_x690_cast(bool val, row_type& src) {
                    src.push_back(static_cast<row_type::value_type> (val ? 0xFF : 0));
                    return 1;
                }


                //// null cast            

                std::size_t to_x690_cast(const null_type& val, row_type& src) {
                    return 0;
                }


                //// oid cast

                static void to_x690_castoid_impl(oidindx_type vl, row_type& src) {
                    row_type tmp;
                    bool first = true;
                    while (vl || first) {
                        first = false;
                        tmp.push_back(static_cast<row_type::value_type> ((static_cast<oidindx_type> (0x7F) & vl) | static_cast<oidindx_type> (CONTENT_CONIIUE)));
                        vl >>= 7;
                    }
                    endian_push_pack(tmp, src);
                    if (!src.empty())
                        src.back() = src.back() & static_cast<row_type::value_type> (0x7F);
                }

                std::size_t to_x690_cast(const oid_type& val, row_type& src) {
                    if (val.size() < 2) return 0;
                    std::size_t strtsz = src.size();
                    oidindx_type tmpval = 40 * val[0];
                    tmpval += val[1];
                    to_x690_castoid_impl(tmpval, src);
                    for (oid_type::const_iterator it = (val.begin() + 2); it != val.end(); ++it)
                        to_x690_castoid_impl(*it, src);
                    return (src.size() - strtsz);
                }
                
                std::size_t to_x690_cast(const reloid_type& val, row_type& src) {
                    if (val.empty()) return 0;
                    std::size_t strtsz = src.size();                    
                    for (oid_type::const_iterator it = (val.begin()); it != val.end(); ++it)
                        to_x690_castoid_impl(*it, src);
                    return (src.size() - strtsz);
                }
                




                /////////////////////////////

          /*    std::size_t size_of(const const_buffers& val) {
                    std::size_t rslt = 0;
                    for (const_buffers::const_iterator it = val.begin(); it != val.end(); ++it)
                        rslt += boost::asio::buffer_size(*it);
                    return rslt;
                }

                std::size_t size_of(const const_buffers_ptr& val) {
                    if (val) return 0;
                    std::size_t rslt = 0;
                    for (const_buffers::const_iterator it = val->begin(); it != val->end(); ++it)
                        rslt += boost::asio::buffer_size(*it);
                    return rslt;
                }*/  

                std::ostream& operator<<(std::ostream& stream, const archive& vl) {
                    stream << vl.buffers();
                    return stream;
                }

                std::ofstream& operator<<(std::ofstream& stream, const archive& vl) {
                    stream << vl.buffers();
                    return stream;
                }


                // STRING REALISZATION

                template<>
                void x690_string_to_stream_cast(const bitstring_type& val, archive& stream, int8_t lentype) {
                    if (!lentype) {
                        stream.add(row_type(1, static_cast<row_type::value_type> (val.unusebits() % 8)));
                        stream.add(val);
                        return;
                    }
                    else {

                        typedef bitstring_type::const_iterator     const_iterator_type;
                        typedef bitstring_type::difference_type   difference_type;

                        const_iterator_type it = val.begin();
                        while (it != val.end()) {
                            stream.add(row_type(1, static_cast<row_type::value_type> (TYPE_BITSTRING)));
                            difference_type  diff = std::distance(it, val.end());
                            if (diff > (CER_STRING_MAX_SIZE - 1)) {
                                diff = (CER_STRING_MAX_SIZE - 1);
                                stream.add(to_x690_cast(size_class(static_cast<std::size_t> (diff + 1))));
                                stream.add(row_type(1, static_cast<row_type::value_type> (0)));
                            }
                            else {
                                stream.add(to_x690_cast(size_class(static_cast<std::size_t> (diff + 1))));
                                stream.add(row_type(1, static_cast<row_type::value_type> (val.unusebits() % 8)));
                            }
                            stream.add(row_type(val.begin(), val.begin() + diff));
                            it = it + diff;
                        }
                    }
                }

                template<>
                archive& operator<<(archive& stream, const implicit_value<bitstring_type>& vl) {
                    stringtype_writer(stream, vl.value(), vl.id(), vl.mask());
                    return stream;
                }

                template<>
                archive& operator<<(archive& stream, const implicit_value<octetstring_type>& vl) {
                    stringtype_writer(stream, vl.value(), vl.id(), vl.mask());
                    return stream;
                }

            }

        }
    }
}
