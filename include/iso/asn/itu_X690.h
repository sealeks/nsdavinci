/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef ITU_X690BOOST__H
#define	ITU_X690BOOST__H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)


#include <iso/asn/asnbase.h>
#include <iso/archive_stream.h>



#include <boost/asio/detail/push_options.hpp>



namespace boost {
    namespace asio {
        namespace asn {
            namespace x690 {


                typedef  boost::asio::iso::list_mutable_buffers                                                                                           list_mutable_buffers;
                typedef  boost::asio::iso::list_const_buffers                                                                                               list_const_buffers;

                typedef enum {
                    BER_ENCODING,
                    CER_ENCODING,
                    DER_ENCODING
                }   encoding_rule;




                const int8_t NEGATIVE_MARKER = '\x80';
                const int8_t POSITIVE_START = '\xFF';

                const int8_t CONTENT_CONIIUE = '\x80';
                const int8_t UNDEF_BLOCK_SIZE = '\x80';



                const int8_t NAN_REAL_ID = '\x42';
                const int8_t INFINITY_REAL_ID = '\x40';
                const int8_t  NEGATINFINITY_REAL_ID = '\x41';
                const int8_t  NEGATNULL_REAL_ID = '\x43';


                const std::size_t MAX_SIMPLELENGTH_SIZE = 0x80;


                const std::size_t FLOAT_MANTISSA_SIZE = 23;
                const std::size_t FLOAT_EXPONENTA_DELT = 127;

                const std::size_t DOUBLE_MANTISSA_SIZE = 52;
                const std::size_t DOUBLE_EXPONENTA_DELT = 1023;

                const std::size_t LONGDOUBLE_MANTISSA_SIZE = 112;
                const std::size_t LONGDOUBLE_EXPONENTA_DELT = 16383;


                //const std::size_t CER_STRING_MAX_SIZE = 1000;
                const std::size_t CER_STRING_MAX_SIZE = 2;




                //////  Endian conv;

                void endian_conv(row_type& val);

                row_type endian_conv_conv(const row_type& val);

                void endian_push_pack(const row_type& val,  row_type& dst);


                /////// timeconv



                //  size_class

                class size_class {
                public:

                    size_class() : size_(0), undefsize_(true) {
                    }

                    size_class(size_type  vl) : size_(vl), undefsize_(false) {
                    }

                    bool undefsize() const {
                        return undefsize_;
                    }

                    size_type size() const {
                        return size_;
                    }


                private:
                    size_type size_;
                    bool   undefsize_;

                } ;

                inline std::ostream& operator<<(std::ostream& stream, const size_class& vl) {
                    return  vl.undefsize() ?  (stream << "SIZE:  undef"  << '\n') : (stream << "SIZE:  " << vl.size()  << '\n');
                }


                ///////////////////





                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
                /*OUTPUT STREAM                                                                                                                                                                                           */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////




                /////  CAST FROM AND TO TYPE

                ///////////////////////////////////////////////////////////////////////////////////////////////
                // integer to X.690

                template<typename T>
                std::size_t to_x690_cast(T val, row_type& src) {
                    row_type tmp;
                    bool negat = (val < 0);



#ifdef BIG_ENDIAN_ARCHITECTURE      
                    !!! not implement
#else

                    if (negat)
                        if (val & (T(1) << (sizeof (T)*8 - 1))) {
                            val &= ~(T(1) << (sizeof (T)*8 - 1));
                            tmp.push_back(static_cast<row_type::value_type> (POSITIVE_START & val));
                            val >>= 8;
                            val |= (T(1) << ((sizeof (T) - 1)*8 - 1));
                        }
                    while (val) {
                        tmp.push_back(static_cast<row_type::value_type> (POSITIVE_START & val));
                        val >>= 8;
                    }
                    if (negat && !tmp.empty())
                        while ((tmp.size() > 1) && (tmp.back() == static_cast<row_type::value_type> (POSITIVE_START)))
                            tmp.pop_back();

                    if ((tmp.empty() || (!negat && (tmp.back() & NEGATIVE_MARKER))))
                        tmp.push_back(static_cast<row_type::value_type> (0));
                    else {
                        if (negat && !(tmp.back() & NEGATIVE_MARKER))
                            tmp.push_back(static_cast<row_type::value_type> (POSITIVE_START));
                    }
                    endian_push_pack(tmp, src);

#endif                              
                    return tmp.size();
                }

                template<>
                std::size_t to_x690_cast(int8_t val, row_type& src);

                template<>
                std::size_t to_x690_cast(uint8_t val, row_type& src);





                ///////////////////////////////////////////////////////////////////////////////////
                // tag to X.690


                std::size_t to_x690_cast(const tag& val, row_type& src);

                row_type to_x690_cast(const tag& val);


                ///////////////////////////////////////////////////////////////////////////////////
                // size_class to X.690


                std::size_t to_x690_cast(const size_class& val, row_type& src);

                row_type to_x690_cast(const size_class& val);


                ///////////////////////////////////////////////////////////////////////////////////
                // real to X.690


                template<>
                std::size_t to_x690_cast(double val, row_type& src);

                template<>
                std::size_t to_x690_cast(float val, row_type& src);

                template<>
                std::size_t to_x690_cast(long double val, row_type& src);



                ///////////////////////////////////////////////////////////////////////////////////
                // bool to X.690

                template<>
                std::size_t to_x690_cast(bool val, row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // null to X.690

                std::size_t to_x690_cast(const null_type& val, row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // enumerated_type to X.690

                std::size_t to_x690_cast(const enumerated_type& val, row_type& src);


                ///////////////////////////////////////////////////////////////////////////////////
                // oid to X.690


                std::size_t to_x690_cast(const oid_type& val, row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // relative oid to X.690


                std::size_t to_x690_cast(const reloid_type& val, row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // utctime to X.690


                std::size_t to_x690_cast(const utctime_type& val, row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // gentime to X.690


                std::size_t to_x690_cast(const gentime_type& val, row_type& src);

                template<typename T>
                row_type to_x690_cast(const T& val) {
                    row_type rslt;
                    to_x690_cast(val, rslt);
                    return rslt;
                }


                //////////////////////////////////////////////////////////////////////////////////////////
                ///  archiver                

                class oarchive : public boost::asio::iso::base_oarchive  {
                    typedef std::pair<iterator , iterator>                                                                                   iterator_pair;
                    typedef std::pair<tag , iterator_pair>                                                                                  tlv_iterators_pair;
                    typedef std::vector<tlv_iterators_pair>                                                                               tlv_vector;
                    typedef std::pair<bool, tlv_vector>                                                                                    stack_item;   //  bool   = true  is set
                    typedef std::stack<stack_item >                                                                                         stack_type;

                public:

                    oarchive(encoding_rule rul = BER_ENCODING) : boost::asio::iso::base_oarchive() , rule_(rul) {
                    }

                    encoding_rule rule() const {
                        return rule_;
                    }

                    template<typename T>
                    void operator&( const T& vl) {
                        *this  <<  implicit_value<T > (vl);
                    }

                    template<typename T>
                    void operator&( const explicit_value<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T, class Tag, id_type ID,  class_type TYPE >
                    void operator&( const explicit_typedef <T, Tag, ID, TYPE>& vl) {
                        *this  <<  explicit_value<T > (vl.value(), ID, TYPE);
                    }

                    template<typename T>
                    void operator&( const optional_explicit_value<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T>
                    void operator&( const implicit_value<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T, class Tag, id_type ID,  class_type TYPE >
                    void operator&( const implicit_typedef <T, Tag, ID, TYPE>& vl) {
                        *this  <<  implicit_value<T > (vl.value(), ID, TYPE);
                    }

                    template<typename T>
                    void operator&( const optional_implicit_value<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T>
                    void operator&( const std::vector<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T>
                    void operator&( const vector_set_of<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T>
                    void operator&(const choice_value<T >& vl) {
                        *this  <<  vl;
                    }

                    iterator  addtag(const  tag& tg,  bool settype);

                    void  pop_stack();

                    virtual void clear();

                    bool canonical() const {
                        return rule_ == CER_ENCODING;
                    }

                private:

                    void sort_tlv(tlv_vector& vct);


                    stack_type            stack_;
                    encoding_rule        rule_;

                } ;



                ////////////////////////////////////////////////////////////////////

                template<typename T>
                inline oarchive& operator<<(oarchive& stream, const T& vl) {
                    stream.add(to_x690_cast(vl));
                    return stream;
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const explicit_value<T>& vl) {

                    stream.addtag(tag( vl.id() , vl.mask() | CONSTRUCTED_ENCODING), (tag_traits<T>::number() == TYPE_SET));
                    oarchive::list_buffers::iterator it = stream.last();

                    std::size_t sz = stream.size();
                    stream & vl.value();

                    sz = stream.size(sz);
                    ++it;

                    if ((stream.canonical())) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2, 0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    stream.pop_stack();
                    return stream;
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const explicit_value< std::vector<T> >& vl) {
                    return stream << implicit_value<std::vector<T> >(vl.value(), vl.id(), vl.type() );
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const explicit_value< vector_set_of<T> >& vl) {
                    return stream << implicit_value<vector_set_of<T> >(vl.value(), vl.id(), vl.type() );
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const implicit_value<T>& vl) {

                    stream.addtag(tag(vl.id(), vl.mask() | CONSTRUCTED_ENCODING), (tag_traits<T>::number() == TYPE_SET));
                    oarchive::list_buffers::iterator it = stream.last();

                    std::size_t sz = stream.size();
                    const_cast<T*> (&(vl.value()))->serialize(stream);
                    sz = stream.size(sz);
                    ++it;


                    if   (stream.canonical()) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2, 0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    stream.pop_stack();
                    return stream;
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const implicit_value<std::vector<T> >& vl) {

                    stream.addtag( tag(vl.id(), vl.mask() | CONSTRUCTED_ENCODING), false );
                    oarchive::list_buffers::iterator it = stream.last();

                    std::size_t sz = stream.size();
                    typedef typename std::vector<T>::const_iterator   vect_type_iterator;
                    for (vect_type_iterator itr = vl.value().begin() ; itr != vl.value().end() ; ++itr)
                        stream & (*itr );
                    sz = stream.size(sz);
                    ++it;

                    if   (stream.canonical()) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2, 0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    stream.pop_stack();
                    return stream;
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const implicit_value<vector_set_of<T> >& vl) {

                    stream.addtag( tag(vl.id(), vl.mask() | CONSTRUCTED_ENCODING) , false );
                    oarchive::list_buffers::iterator it = stream.last();

                    std::size_t sz = stream.size();
                    typedef typename vector_set_of<T>::const_iterator   vect_type_iterator;
                    for (vect_type_iterator itr = vl.value().begin() ; itr != vl.value().end() ; ++itr)
                        stream & (*itr );
                    sz = stream.size(sz);
                    ++it;

                    if   (stream.canonical()) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2, 0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    stream.pop_stack();
                    return stream;
                }

                template<typename T>
                oarchive& primitive_sirialize(oarchive& stream, const implicit_value<T>& vl) {

                    stream.addtag( tag(vl.id(), vl.mask()), (tag_traits<T>::number() == TYPE_SET));
                    oarchive::list_buffers::iterator it = stream.last();

                    std::size_t sz = stream.size();
                    stream << vl.value();
                    sz = stream.size(sz);
                    ++it;

                    stream.add( to_x690_cast(size_class(sz)), it);
                    stream.pop_stack();
                    return stream;
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const optional_explicit_value<T>& vl) {
                    if (vl.value())
                        stream << explicit_value<T > (*vl.value(), vl.id(), vl.type());
                    return stream;
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const optional_implicit_value<T>& vl) {
                    if (vl.value())
                        stream << implicit_value<T > (*vl.value(), vl.id(), vl.type());
                    return stream;
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const choice_value<T>& vl) {
                    return stream;
                }



                ////////////////// STRING REALIZATION

                template<typename T>
                void x690_string_to_stream_cast(const T& val, oarchive& stream, int8_t lentype) {
                    if (!lentype) {
                        stream.add(val);
                        return;
                    }
                    else {

                        typedef typename T::const_iterator     const_iterator_type;
                        typedef typename T::difference_type   difference_type;

                        const_iterator_type it = val.begin();
                        while (it != val.end()) {
                            //stream.add(row_type(1, static_cast<row_type::value_type> ( tag_traits<T>::number())));
                            stream.addtag(tag(tag_traits<T>::number()), false);
                            difference_type  diff = std::distance(it, val.end());
                            if (diff > CER_STRING_MAX_SIZE) {
                                diff = CER_STRING_MAX_SIZE;
                                stream.add(to_x690_cast(size_class(static_cast<std::size_t> (diff))));
                            }
                            else {
                                stream.add(to_x690_cast(size_class(static_cast<std::size_t> (diff))));
                            }
                            stream.add(row_type(it , it + diff));
                            it = it + diff;
                            stream.pop_stack();
                        }
                    }
                }


                template<>
                void x690_string_to_stream_cast(const bitstring_type& val, oarchive& stream, int8_t lentype);

                template<typename T>
                oarchive& stringtype_writer(oarchive& stream, const T& vl, id_type  id , int8_t mask) {



                    int8_t construct = vl.size()<( tag_traits<T>::number() == TYPE_BITSTRING ? (CER_STRING_MAX_SIZE - 1) : CER_STRING_MAX_SIZE )
                            ?  PRIMITIVE_ENCODING  :  (stream.canonical() ?  CONSTRUCTED_ENCODING : PRIMITIVE_ENCODING) ;

                    stream.addtag( tag(id , mask | construct ), false );
                    oarchive::list_buffers::iterator it = stream.last();

                    std::size_t sz = stream.size();
                    x690_string_to_stream_cast(vl, stream, construct);
                    sz = stream.size(sz);
                    ++it;

                    if  (construct) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2, 0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    stream.pop_stack();
                    return stream;
                }



                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<int8_t>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<uint8_t>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<int16_t>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<uint16_t>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<int32_t>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<uint32_t>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<int64_t>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<uint64_t>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<enumerated_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<float>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<double>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<long double>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<bool>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<oid_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<reloid_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<bitstring_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<octetstring_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<utf8string_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<numericstring_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<printablestring_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<t61string_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<videotexstring_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<ia5string_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<graphicstring_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<visiblestring_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<generalstring_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<universalstring_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<bmpstring_type>& vl);


                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<utctime_type>& vl);

                template<>
                oarchive& operator<<(oarchive& stream, const implicit_value<gentime_type>& vl);




                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
                /*INPUT STREAM                                                                                                                                                                                               */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                bool find_marked_sequece( const list_mutable_buffers& val, list_mutable_buffers::const_iterator bit, row_type& raw,  std::size_t start = 0);


                /////  CAST FROM AND TO TYPE

                ///////////////////////////////////////////////////////////////////////////////////////////////
                // integer from X.690          

                template<typename T>
                bool from_x690_cast(T& vl, const row_type& dt) {
                    row_type  val = dt;
#ifdef BIG_ENDIAN_ARCHITECTURE 
                    !!! not implement
#else              
                    endian_conv(val);
                    if (sizeof (T) > val.size())
                        val.resize(sizeof (T), row_type::value_type((val.empty() || (val.back() & NEGATIVE_MARKER )) ? POSITIVE_START : 0));
                    vl = (*(T*) (&val[0]));
#endif                  
                    return true;
                }




                ///////////////////////////////////////////////////////////////////////////////////
                // tag from X.690

                std::size_t tag_from_x690_cast(const tag& val, const row_type& src);

                std::size_t tag_x690_cast(tag& val, const list_mutable_buffers& src, list_mutable_buffers::const_iterator bit,  std::size_t beg = 0);

                ///////////////////////////////////////////////////////////////////////////////////
                // size_class from X.690

                std::size_t size_x690_cast(size_class& val, const list_mutable_buffers& src, list_mutable_buffers::const_iterator bit,  std::size_t beg = 0);

                ///////////////////////////////////////////////////////////////////////////////////
                // real from X.690

                template<>
                bool from_x690_cast(float& vl, const row_type& val);

                template<>
                bool from_x690_cast(double& vl, const row_type& val);

                template<>
                bool from_x690_cast(long double& vl, const row_type& val);


                ///////////////////////////////////////////////////////////////////////////////////
                // bool from X.690

                template<>
                bool from_x690_cast(bool& vl, const row_type& val);


                ///////////////////////////////////////////////////////////////////////////////////
                // null from X.690

                template<>
                bool from_x690_cast(null_type& val, const row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // enumerated_type from X.690

                template<>
                bool from_x690_cast(enumerated_type& val, const row_type& src);


                ///////////////////////////////////////////////////////////////////////////////////
                // oid from X.690

                template<>
                bool from_x690_cast(oid_type& val, const row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // relative from to X.690

                template<>
                bool from_x690_cast(reloid_type& val, const row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // utctime_type from to X.690

                template<>
                bool from_x690_cast(utctime_type& val, const row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // gentime_type from to X.690

                template<>
                bool from_x690_cast(gentime_type& val, const row_type& src);



                //////////////////////////////////////////////////////////
                //   archiver

                class iarchive : public boost::asio::iso::base_iarchive  {
                    typedef  std::pair<bool, std::size_t>  tlv_size;   //  bool = true is valid size, else undef size
                    typedef  std::pair<bool, tlv_size >     tlv_item;   //  bool = true is set type                    
                    typedef  std::stack<tlv_item>             tlv_stack;


                public:

                    iarchive(encoding_rule rul = BER_ENCODING) : boost::asio::iso::base_iarchive() , rule_(rul) {
                    }

                    encoding_rule rule() const {
                        return rule_;
                    }

                    template<typename T>
                    void operator&(const T& vl) {
                        *this  >>  implicit_value<T > (vl);
                    }

                    template<typename T>
                    void operator&(const explicit_value<T >& vl) {
                        *this  >> vl;
                    }

                    template<typename T, class Tag, id_type ID,  class_type TYPE >
                    void operator&( const explicit_typedef <T, Tag, ID, TYPE>& vl) {
                        *this  >> explicit_value<T > (vl.value(), ID, TYPE);
                    }

                    template<typename T>
                    void operator&(const optional_explicit_value<T >& vl) {
                        *this  >>  vl;
                    }

                    template<typename T>
                    void operator&(const implicit_value<T >& vl) {
                        *this  >>  vl;
                    }

                    template<typename T, class Tag, id_type ID,  class_type TYPE >
                    void operator&( const implicit_typedef <T, Tag, ID, TYPE>& vl) {
                        *this  >> implicit_value<T > (vl.value(), ID, TYPE);
                    }

                    template<typename T>
                    void operator&(const optional_implicit_value<T >& vl) {
                        *this  >>  vl;
                    }

                    template<typename T>
                    void operator&( const std::vector<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T>
                    void operator&(const choice_value<T >& vl) {
                        *this  >>  vl;
                    }


                    tag test_tl(size_class& sz) {

                        tag tmptag;
                        std::size_t sztag = tag_x690_cast(tmptag, buffers(), buffers().begin());
                        if (sztag) {
                            size_class tmpsize;
                            std::size_t szsize = size_x690_cast(sz, buffers(),  buffers().begin() , sztag);
                            if (szsize) {
                                return tmptag;
                            }
                        }
                        return tag();
                    }

                    tag test_tl() {
                        size_class sz;
                        return test_tl(sz);
                    }

                    bool parse_tl(const tag& tg, size_class& rsltsz , bool settype) {


                        std::size_t size_tlv = size();
                        bool is_set_child = false;

                        if (!stack_.empty()) {
                            size_tlv = stack_.top().second.second;
                            if (stack_.top().first) {
                                is_set_child = true;
                            }
                            else {
                            }
                        }

                        tag tmptag;

                        std::size_t sztag = tag_x690_cast(tmptag, buffers(), buffers().begin());
                        if (sztag && (tg == tmptag)) {
                            std::size_t szsize = size_x690_cast(rsltsz, buffers(),  buffers().begin() , sztag);
                            if (szsize) {
                                pop_front(szsize + sztag);
                                if (!stack_.empty()) {
                                    if (stack_.top().second.first)
                                        stack_.top().second.second -= (szsize + sztag + rsltsz.size());
                                }
                                stack_.push(tlv_item(settype, tlv_size(!rsltsz.undefsize(), rsltsz.size())));
                                return  true;
                            }
                        }
                        return false;
                    }

                    bool parse_tl(const tag& tg , bool settype) {
                        size_class rsltsz;
                        return parse_tl(tg, rsltsz , settype);
                    }
                    
                    

                    void pop_stack() {
                        if (!stack_.empty()) {
                            if (!stack_.top().second.first) {
                                if (is_endof())
                                   pop_front(2);
                                else
                                  std::cout  << "NEED FIND EOF, EOF NOT FOUND: "  << std::endl;  
                            }
                            else {
                                pop_front(stack_.top().second.second);
                            }
                            stack_.pop();
                        }
                    }
                    
                    bool next(std::size_t& sz) const{
                        tag tmptag;
                        std::size_t sztag = tag_x690_cast(tmptag, buffers(), buffers().begin(), sz);
                        if (sztag) {
                            size_class tmpsize;
                            std::size_t szsize = size_x690_cast(tmpsize, buffers(),  buffers().begin() , sztag + sz);
                            if (szsize) {
                                if (tmpsize.undefsize()){
                                    while ((!is_endof(sz)) && (sz<size())) {
                                        if (!next(sz))
                                            return false;
                                    }
                                    if (!is_endof(sz))
                                        return false;
                                    sz += 2;
                                    return true;
                                }
                                else
                                {
                                    sz += (szsize + sztag + tmpsize.size());
                                    return true;
                                }               
                                }}
                        return false;   
                    }



                private:


                    tlv_stack               stack_;
                    encoding_rule        rule_;

                } ;

                template<typename T>
                iarchive& operator>>(iarchive& stream, const explicit_value<T>& vl) {
                    if (stream.parse_tl(vl, tag_traits<T>::number() == TYPE_SET )) {
                        stream & vl.value();
                        stream.pop_stack();
                    }
                    return stream;
                }

                template<typename T>
                iarchive& operator>>(iarchive& stream, const optional_explicit_value<T>& vl) {
                    typedef boost::shared_ptr<T> shared_type;
                    if (stream.test_tl(vl) == vl.operator  tag()) {
                        *const_cast<shared_type*> (&(vl.value())) = boost::shared_ptr<T > (new T());
                        stream >> explicit_value<T > (*vl.value(), vl.id(), vl.type());
                    }
                    return stream;
                }

                template<typename T>
                iarchive& operator>>(iarchive& stream, const implicit_value<T>& vl) {
                    if (stream.parse_tl(vl, tag_traits<T>::number() == TYPE_SET )) {
                        const_cast<T*> (&(vl.value()))->serialize(stream);
                        stream.pop_stack();
                    }
                    return stream;
                }

                template<typename T>
                iarchive& operator>>(iarchive& stream, const optional_implicit_value<T>& vl) {
                    typedef boost::shared_ptr<T> shared_type;
                    if (stream.test_tl(vl) == vl.operator  tag()) {
                        *const_cast<shared_type*> (&(vl.value())) = boost::shared_ptr<T > (new T());
                        stream >> implicit_value<T > (*vl.value(), vl.id(), vl.type());
                    }
                    return stream;
                }

                template<typename T>
                iarchive& operator>>(iarchive& stream, const explicit_value< std::vector<T> >& vl) {
                    return stream >> implicit_value<std::vector<T> >(vl.value(), vl.id(), vl.type());
                }

                template<typename T>
                iarchive& operator>>(iarchive& stream, const explicit_value< vector_set_of<T> >& vl) {
                    return stream >> implicit_value< vector_set_of<T> >(vl.value(), vl.id(), vl.type());
                }

                template<typename T>
                iarchive& operator>>(iarchive& stream, const implicit_value< std::vector<T> >& vl) {
                    size_class tmpsize;
                    if (stream.parse_tl(vl, tmpsize, false )) {
                        std::size_t beg = stream.size();
                        if  (tmpsize.undefsize()) {
                            while (!stream.is_endof() && stream.size()) {
                                T tmp;
                                stream & tmp;
                                const_cast<std::vector<T>* > (&(vl.value()))->push_back(tmp);
                            }
                        }
                        else {
                            std::size_t sz = tmpsize.size();
                            while ((beg - stream.size()) < sz ) {
                                T tmp;
                                stream & tmp;
                                const_cast<std::vector<T>* > (&(vl.value()))->push_back(tmp);
                            }
                        }
                    }
                    return stream;
                }

                template<typename T>
                iarchive& operator>>(iarchive& stream, const implicit_value< vector_set_of<T> >& vl) {

                    size_class tmpsize;
                    if (stream.parse_tl(vl, tmpsize, false )) {
                        std::size_t beg = stream.size();
                        if  (tmpsize.undefsize()) {
                            while (!stream.is_endof() && stream.size()) {
                                T tmp;
                                stream & tmp;
                                const_cast<vector_set_of<T>* > (&(vl.value()))->push_back(tmp);
                            }
                        }
                        else {
                            std::size_t sz = tmpsize.size();
                            while ((beg - stream.size()) < sz ) {
                                T tmp;
                                stream & tmp;
                                const_cast<vector_set_of<T>* > (&(vl.value()))->push_back(tmp);
                            }
                        }
                    }
                    return stream;
                }

                template<typename T>
                iarchive& operator>>(iarchive& stream, const choice_value<T>& vl) {
                    return stream;
                }


                //////////////////////////////////////////////////////////////////////////////////

                template<typename T>
                iarchive&  primitive_desirialize(iarchive& stream, const implicit_value<T>& vl) {
                    size_class tmpsize;
                    if (stream.parse_tl(vl, tmpsize,  tag_traits<T>::number() == TYPE_SET )) {
                        row_type data;
                        std::size_t sz = tmpsize.size();
                        if (boost::asio::iso::row_cast(stream.buffers(), stream.buffers().begin() , data , 0 , sz )) {
                            if (from_x690_cast(*const_cast<T*> (&vl.value()), data)) {
                                stream.pop_stack();
                            }
                        }
                    }
                    return stream;
                }

                template<typename T>
                bool stringtype_reader(iarchive& stream, T& vl, id_type id , int8_t mask) {

                    size_class tmpsize;
                    tag tmptag =  stream.test_tl() ;
                    if (stream.parse_tl(tag(id,  mask), tmpsize,  false )) {
                        if (tmpsize.undefsize()) {
                            if (tmptag.constructed()) {
                                while (!stream.is_endof() && !stream.buffers().empty()) {
                                    if (!stringtype_reader(stream, vl, tag_traits<T>::number()  , 0))
                                        return false;
                                }
                                stream.pop_stack();
                                return true;
                            }
                            else {
                                std::size_t sz = 0;
                               if (boost::asio::iso::find_eof(stream.buffers(), stream.buffers().begin() , sz)) {
                                    row_type data;
                                    if (boost::asio::iso::row_cast(stream.buffers(), stream.buffers().begin(), data , 0 , sz )) {
                                        vl.insert(vl.end(), data.begin(), data.end());
                                        return true;
                                    }
                                }
                                return false;
                            }
                        }
                        else {
                            std::size_t sz = tmpsize.size();
                            if (tmptag.constructed()) {
                                while (!stream.buffers().empty()) {
                                    if (!stringtype_reader(stream, vl, tag_traits<T>::number()  , 0)) {
                                        return true;
                                    }
                                    stream.pop_stack();
                                }
                                return false;
                            }
                            else {
                                row_type data;
                                if (boost::asio::iso::row_cast(stream.buffers(), stream.buffers().begin(), data , 0 , tmpsize.size())) {
                                    vl.insert(vl.end(), data.begin(), data.end());
                                    stream.pop_stack();
                                    return true;
                                }
                            }
                        }
                    }
                    return false;
                }

                template<>
                iarchive& operator>>(iarchive& stream,  const implicit_value<int8_t>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<uint8_t>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<int16_t>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<uint16_t>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<int32_t>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<uint32_t>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<int64_t>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<uint64_t>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<enumerated_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<float>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<double>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<long double>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<bool>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<null_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<oid_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<reloid_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<bitstring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<octetstring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<utf8string_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<numericstring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<printablestring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<t61string_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<videotexstring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<ia5string_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<graphicstring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<visiblestring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<generalstring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<universalstring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<bmpstring_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<utctime_type>& vl);

                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<gentime_type>& vl);







            }

        }
    }
}


#endif	/* ASNBASE_H */

