/* 
 * File:   asnbase.cpp
 * Author: sealeks
 * 
 * Created on 2 Ноябрь 2012 г., 0:39
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
                stream << std::endl;
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
                    construct(*reinterpret_cast<uint8_t*>(&vl), unuse);
                };

            bitstring_type::bitstring_type(int16_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                    construct(*reinterpret_cast<uint16_t*>(&vl), unuse);
                };

            bitstring_type::bitstring_type(int32_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                    construct(*reinterpret_cast<uint32_t*>(&vl), unuse);
                };

            bitstring_type::bitstring_type(int64_t vl, std::size_t unuse) : std::vector<int8_t>(), unuse_(unuse) {
                    construct(*reinterpret_cast<uint64_t*>(&vl), unuse);
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
                        tmp.operator [](i)=bit(i);
                    return tmp;
                }                
                
               
                
                bitstring_type::operator uint8_t() const {
                    bool_vector_type tmp;
                    for (std::size_t i = 0; i < sizebits(); ++i)
                        tmp.push_back(bit(i));
                    return return_int<uint8_t>();
                }
                
                bitstring_type::operator uint16_t() const {
                    bool_vector_type tmp;
                    for (std::size_t i = 0; i < sizebits(); ++i)
                        tmp.push_back(bit(i));
                    return return_int<uint16_t>();
                }               
                
                bitstring_type::operator uint32_t() const {
                    bool_vector_type tmp;
                    for (std::size_t i = 0; i < sizebits(); ++i)
                        tmp.push_back(bit(i));
                    return return_int<uint16_t>();
                }   
                
                bitstring_type::operator uint64_t() const {
                    bool_vector_type tmp;
                    for (std::size_t i = 0; i < sizebits(); ++i)
                        tmp.push_back(bit(i));
                    return return_int<uint16_t>();
                }    
                
                bitstring_type::operator int8_t() const {
                    bool_vector_type tmp;
                    for (std::size_t i = 0; i < sizebits(); ++i)
                        tmp.push_back(bit(i));
                    return return_int<int8_t>();
                }
                
                bitstring_type::operator int16_t() const {
                    bool_vector_type tmp;
                    for (std::size_t i = 0; i < sizebits(); ++i)
                        tmp.push_back(bit(i));
                    return return_int<int16_t>();
                }               
                
                bitstring_type::operator int32_t() const {
                    bool_vector_type tmp;
                    for (std::size_t i = 0; i < sizebits(); ++i)
                        tmp.push_back(bit(i));
                    return return_int<int16_t>();
                }   
                
                bitstring_type::operator int64_t() const {
                    bool_vector_type tmp;
                    for (std::size_t i = 0; i < sizebits(); ++i)
                        tmp.push_back(bit(i));
                    return return_int<int16_t>();
                }                    
                
                
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
                stream <<  std::string(vl.begin(),vl.end()) << std::endl;
                return stream;
            }


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
            std::size_t to_x690_cast(int8_t val, row_type& src, length_type lentype ) {
                src.push_back(static_cast<row_type::value_type> (0xFF & val));
                return 1;
            }

            template<>
            std::size_t to_x690_cast(uint8_t val, row_type& src, length_type lentype) {
                return to_x690_cast(static_cast<int16_t> (val), src) ;
            }


            /// id class

            std::size_t to_x690_cast(const tag& val, row_type& src, length_type lentype) {
                if (val.simpleid()) {
                    src.push_back(static_cast<row_type::value_type> (val.simpleid()));
                    return 1;
                }
                else {
                    id_type id_ = val.id();
                    row_type tmp;
                    src.push_back (static_cast<row_type::value_type> (0x1F | val.mask()));
                    while (id_) {
                        tmp.push_back(static_cast<row_type::value_type> ((id_ & 0x7F) | 0x80));
                        id_  >>= 7;
                    }
                    endian_push_pack(tmp, src);
                    if (tmp.size())
                        src.back() &= static_cast<row_type::value_type> (0x7F);
                    return (src.size() + 1);
                }
            }

            row_type to_x690_cast(const tag& val, length_type lentype) {
                row_type tmp;
                to_x690_cast(val, tmp);
                return tmp;
            }


            ///////////////////////////////////////////////////////////////////////////////////
            // size_class to X.690

            std::size_t to_x690_cast(const size_class& val, row_type& src, length_type lentype) {
                if (!val.undefsize()) {
                    if (val.size() < 0x80) {
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
                        src.push_back (static_cast<row_type::value_type> ( '\x80' | static_cast<row_type::value_type> (tmp.size())));
                        endian_push_pack(tmp, src);
                        return (src.size() + 1);
                    }
                }
                else {
                    src.push_back (static_cast<row_type::value_type> ( static_cast<row_type::value_type> ('\x80')));
                    return 1;
                }
            }

            row_type to_x690_cast(const size_class& val, length_type lentype) {
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
                    src.push_back(static_cast<row_type::value_type> (0x42));
                    return 1;
                }
                if (std::numeric_limits<T>::infinity() == val) {
                    src.push_back(static_cast<row_type::value_type> (0x40));
                    return 1;
                }
                if (-std::numeric_limits<T>::infinity() == val) {
                    src.push_back(static_cast<row_type::value_type> (0x41));
                    return 1;
                }
                if (val == -0) {
                    src.push_back(static_cast<row_type::value_type> (0x43));
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
            std::size_t to_x690_cast(double val, row_type& src, length_type lentype) {
                return to_x690_cast_realimpl<double, int64_t, 52, 1023 > (val, src);
            }

            template<>
            std::size_t to_x690_cast(long double val, row_type& src, length_type lentype) {
                return to_x690_cast_realimpl<double, int32_t, 23, 127 > (static_cast<double> (val), src);
            }

            template<>
            std::size_t to_x690_cast(float val, row_type& src, length_type lentype) {
                return to_x690_cast_realimpl<float, int32_t, 23, 127 > (val, src);
            }

            //// bool cast

            template<>
            std::size_t to_x690_cast(bool val, row_type& src, length_type lentype) {
                src.push_back(static_cast<row_type::value_type> (val ? 0xFF : 0));
                return 1;
            }


            //// null cast            

            std::size_t to_x690_cast(const null_type& val, row_type& src, length_type lentype) {
                return 0;
            }


            //// oid cast

            static void to_x690_castoid_impl(oidindx_type vl, row_type& src) {
                row_type tmp;
                bool first = true;
                while (vl || first) {
                    first = false;
                    tmp.push_back(static_cast<row_type::value_type> ((static_cast<oidindx_type> (0x7F) & vl) | static_cast<oidindx_type> (0x80)));
                    vl >>= 7;
                }
                endian_push_pack(tmp, src);
                if (!src.empty())
                    src.back() = src.back() & static_cast<row_type::value_type> (0x7F);
            }

            std::size_t to_x690_cast(const oid_type& val, row_type& src, length_type lentype) {
                if (val.size() < 2) return 0;
                std::size_t strtsz = src.size();
                oidindx_type tmpval = 40 * val[0];
                tmpval += val[1];
                to_x690_castoid_impl(tmpval, src);
                std::size_t it = 2;
                for (oid_type::const_iterator it = (val.begin() + 2); it != val.end(); ++it)
                    to_x690_castoid_impl(*it, src);
                return (src.size() - strtsz);
            }
            
     
            //// bitstring cast
            
            std::size_t to_x690_cast(const bitstring_type& val, row_type& src, length_type lentype){
                switch(lentype){
                        case PRIMITIVE_DEFINED_SIZE:{
                       // case PRIMITIVE_UNDEFINED_SIZE
                           src.push_back(static_cast<row_type::value_type>(val.unusebits() % 8));
                           std::copy(val.begin(), val.end(), std::back_inserter(src));
                           return (val.size()+1);}
                        default :{
                            bitstring_type::const_iterator it= val.begin();
                            row_type tmp;
                            while(it!=val.end()){
                                tmp.push_back(static_cast<row_type::value_type>(TYPE_BITSTRING));
                                bitstring_type::difference_type diff=std::distance(it,val.end());
                                if (diff>999){
                                    diff=999;
                                    to_x690_cast(size_class(static_cast<std::size_t>(diff+1)),tmp);
                                    tmp.push_back(static_cast<row_type::value_type>(0));}
                                else{
                                    to_x690_cast(size_class(static_cast<std::size_t>(diff+1)),tmp);
                                    tmp.push_back(static_cast<row_type::value_type>(val.unusebits() % 8)); 
                                }                              
                                std::copy(val.begin(), val.begin()+diff, std::back_inserter(tmp));
                                it=it+diff;}
                                std::copy(tmp.begin(), tmp.end(), std::back_inserter(src));  
                                return tmp.size();
                        }}                                       
            }
            
            //// octetstring cast
            
            std::size_t to_x690_cast(const octetstring_type& val, row_type& src, length_type lentype){
                switch(lentype){
                        case PRIMITIVE_DEFINED_SIZE:{
                       // case PRIMITIVE_UNDEFINED_SIZE
                           std::copy(val.begin(), val.end(), std::back_inserter(src));
                           return (val.size());}
                        default :{
                            bitstring_type::const_iterator it= val.begin();
                            row_type tmp;
                            while(it!=val.end()){
                                tmp.push_back(static_cast<row_type::value_type>(TYPE_OCTETSTRING));
                                bitstring_type::difference_type diff=std::distance(it,val.end());
                                if (diff>1000){
                                    diff=1000;
                                    to_x690_cast(size_class(static_cast<std::size_t>(diff)),tmp);}
                                else{
                                    to_x690_cast(size_class(static_cast<std::size_t>(diff)),tmp);
                                }                              
                                std::copy(val.begin(), val.begin()+diff, std::back_inserter(tmp));
                                it=it+diff;}
                                std::copy(tmp.begin(), tmp.end(), std::back_inserter(src));  
                                return tmp.size();
                        }}                                       
            }            







            /////////////////////////////

            std::size_t size_of(const const_buffers& val) {
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
            }

            std::ostream& operator<<(std::ostream& stream, const archive& vl) {
                stream << vl.buffers();
                return stream;
            }

            std::ofstream& operator<<(std::ofstream& stream, const archive& vl) {
                stream << vl.buffers();
                return stream;
            }
            
            
            
            archive& operator<<(archive& stream, const bitstring_type& vl){
                /*encoding_rule rl = vl.size()<999 ? BER_ENCODING : stream.rule();
                stream.add( to_x690_cast(tag(tag_number<bitstring_type>::number(), from_cast(rl!=CER_ENCODING ? PRIMITIVE_ENCODING : CONSTRUCTED_ENCODING))));
                iterator_list_const_buffers it = stream.add(to_x690_cast(vl, rl!=CER_ENCODING ? PRIMITIVE_DEFINED_SIZE : CONSTRUCTED_UNDEFINED_SIZE ));       
                if (rl!=CER_ENCODING){
                         std::size_t sz = stream.size(it);
                         stream.add( to_x690_cast(size_class(sz)), it);}
                else{
                        stream.add( to_x690_cast(size_class(0 , true)), it);
                        stream.add(row_type(2,0));}    */
                return stream << implicit_value< bitstring_type, TYPE_BITSTRING>(vl);
            }  
            
            archive& operator<<(archive& stream, const octetstring_type& vl){
                /*encoding_rule rl = vl.size()<999 ? BER_ENCODING : stream.rule();
                stream.add( to_x690_cast(tag(tag_number<octetstring_type>::number(), from_cast(rl!=CER_ENCODING ? PRIMITIVE_ENCODING : CONSTRUCTED_ENCODING))));
                iterator_list_const_buffers it = stream.add(to_x690_cast(vl, rl!=CER_ENCODING ? PRIMITIVE_DEFINED_SIZE : CONSTRUCTED_UNDEFINED_SIZE));          
                if (rl!=CER_ENCODING){
                         std::size_t sz = stream.size(it);
                         stream.add( to_x690_cast(size_class(sz)), it);}
                else{
                        stream.add( to_x690_cast(size_class(0 , true)), it);
                        stream.add(row_type(2,0));} */       
                return stream  << implicit_value< octetstring_type, TYPE_OCTETSTRING>(vl);
            }             



        }
    }
}

