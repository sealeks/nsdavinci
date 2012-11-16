/* 
 * File:   asnbase.h
 * Author: sealeks
 *
 * Created on 2 РќРѕСЏР±СЂСЊ 2012 Рі., 0:39
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
                const int8_t  NEGATNULL_REAL_ID = '\x42';


                const std::size_t MAX_SIMPLELENGTH_SIZE = 0x80;


                const std::size_t FLOAT_MANTISSA_SIZE = 23;
                const std::size_t FLOAT_EXPONENTA_DELT = 127;

                const std::size_t DOUBLE_MANTISSA_SIZE = 52;
                const std::size_t DOUBLE_EXPONENTA_DELT = 1023;

                const std::size_t LONGDOUBLE_MANTISSA_SIZE = 112;
                const std::size_t LONGDOUBLE_EXPONENTA_DELT = 16383;
                

                const std::size_t CER_STRING_MAX_SIZE = 1000;                










                //////  Endian conv;

                void endian_conv(row_type& val);

                row_type endian_conv_conv(const row_type& val);

                void endian_push_pack(const row_type& val,  row_type& dst);


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


                ///////////////////




                
                

                template<typename T>
                class explicit_value {
                public:

                    typedef  T   root_type;

                    //explicit_value() :  id_() , val_(), mask_(from_cast(CONTEXT_CLASS) | CONSTRUCTED_ENCODING) {
                    //}

                    explicit explicit_value(const T& vl, id_type id,  class_type type = CONTEXT_CLASS) :  id_(id) , val_(vl), mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
                    }

                    const T& value() const {
                        return val_;
                    }

                    T& value() {
                        return val_;
                    }

                    id_type id()  const {
                        return id_;
                    }

                    class_type type() const {
                        return to_class_type(mask_);
                    }

                    int8_t mask() const {
                        return mask_;
                    }

                    static  bool primitive() {
                        return false;
                    }


                private:
                    id_type id_;
                    T val_;
                    int8_t   mask_;
                } ;

                template<typename T>
                class implicit_value {
                public:

                    typedef  T   root_type;

                    //implicit_value() : id_(0) ,  val_(), mask_(from_cast(CONTEXT_CLASS))  {
                    //}

                    explicit implicit_value(const T& vl, id_type id,  class_type type = CONTEXT_CLASS) : id_(id) ,  val_(vl), mask_(from_cast(type))  {
                    }

                    explicit  implicit_value(const T& vl,  class_type type = CONTEXT_CLASS) : id_(tag_traits<T>::number()) ,  val_(vl), mask_(from_cast(type))  {
                    }

                    const T& value() const {
                        return val_;
                    }

                    T& value() {
                        return val_;
                    }

                    id_type id()  const {
                        return id_;
                    }

                    class_type type() const {
                        return to_class_type(mask_);
                    }

                    int8_t mask() const {
                        return mask_;
                    }

                    static  bool primitive() {
                        return  tag_traits<T>::primitive() ?  true : false;
                    }


                private:
                    id_type id_;
                    T val_;
                    int8_t   mask_;
                } ;

                template<typename T >
                class set_of_type : public std::vector<T> {
                public:

                    set_of_type(id_type id = TYPE_SET, class_type type = UNIVERSAL_CLASS) : std::vector<T>(),  id_(id) , mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
                    }

                    id_type id()  const {
                        return id_;
                    }

                    class_type type() const {
                        return to_class_type(mask_);
                    }

                    int8_t mask() const {
                        return mask_;
                    }

                    static  bool primitive() {
                        return false;
                    }



                private:
                    id_type id_;
                    int8_t   mask_;

                } ;



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


                // integer from X.690            

                template<typename T>
                T  from_x690_cast(row_type val) {
#ifdef BIG_ENDIAN_ARCHITECTURE 
                    !!! not implement
#else              
                    endian_conv(val);
                    if (sizeof (T) > val.size())
                        val.resize(sizeof (T), row_type::value_type((val.empty() || (val.back() & NEGATIVE_MARKER )) ? POSITIVE_START : 0));
                    return (*(T*) (&val[0]));
#endif                  
                }


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
                // oid to X.690


                std::size_t to_x690_cast(const oid_type& val, row_type& src);
                
                ///////////////////////////////////////////////////////////////////////////////////
                // relative oid to X.690


                std::size_t to_x690_cast(const reloid_type& val, row_type& src);                


                //////////////////////////////////////////////////////////////////////////////////////////

                template<typename T>
                row_type to_x690_cast(T val) {
                    row_type rslt;
                    to_x690_cast(val, rslt);
                    return rslt;
                }
                
                
                
                
                
                
                
                
                
             class archive : public boost::asio::iso::base_archive  {
            public:


                typedef std::pair<id_type, list_iterator_pair>                                                                         tlv_iterators_pair;
                typedef std::multimap<id_type, list_iterator_pair>                                                               list_iterators_map;

                archive(encoding_rule rul = BER_ENCODING) : boost::asio::iso::base_archive() , rule_(rul) {
                }

                encoding_rule rule() const {
                   return rule_;
                }


                template<typename T>
                void save_map_explicit(const T& vl, list_iterators_map& mps,  id_type ID,  class_type TYPE = CONTEXT_CLASS) {
                    iterator_list_const_buffers itf = last();
                    explicit_value<T> tmp(vl, ID, TYPE);
                    *this  <<  tmp;
                    splice_tlv(mps, ID, itf, last());
                }

                template<typename T>
                void save_map_implicit(const T& vl, list_iterators_map& mps, id_type ID,  class_type TYPE = CONTEXT_CLASS) {
                    iterator_list_const_buffers itf = last();
                    implicit_value<T> tmp(vl, ID, TYPE);
                    *this  << tmp;
                    splice_tlv(mps, ID, itf, last());
                }

                template<typename T>
                void save_map_implicit(const T& vl, list_iterators_map& mps, class_type TYPE = UNIVERSAL_CLASS) {
                    iterator_list_const_buffers itf = last();
                    implicit_value<T> tmp(vl, TYPE);
                    id_type ID = tmp.id();
                    *this  << tmp;
                    splice_tlv(mps, ID, itf, last());
                }
                
                template<typename T>
                void save_explicit(const T& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                    *this  <<  explicit_value<T > (vl, id, type);
                }

                template<typename T>
                void save_implicit(const T& vl, id_type id,  class_type type =  CONTEXT_CLASS) {
                    *this  <<  implicit_value<T > (vl, id, type);
                }

                template<typename T>
                void save_implicit(const T& vl, class_type type =  UNIVERSAL_CLASS) {
                    *this  <<  implicit_value<T > (vl, type);
                }                



            protected:

                void splice_tlv(list_iterators_map& mps, id_type id, iterator_list_const_buffers itf,  iterator_list_const_buffers its) {

                    if (mps.upper_bound(id) != mps.end())
                        listbuffers_.splice(mps.upper_bound(id)->second.first , listbuffers_ , ++itf , ++iterator_list_const_buffers(its));
                    else
                        ++itf;

                    if (itf != its)
                        mps.insert(tlv_iterators_pair(id, list_iterator_pair(itf, its)));
                }



            private:


                encoding_rule        rule_;

            } ;
               
                
                
                
                
                
                
                
                
                
                
                
                
                
                

  



                std::ostream& operator<<(std::ostream& stream, const archive& vl);

                std::ofstream& operator<<(std::ofstream& stream, const archive& vl);

                template<typename T>
                inline archive& operator<<(archive& stream, const T& vl) {
                    stream.add(to_x690_cast(vl));
                    return stream;
                }

                template<typename  T>
                archive& operator<<(archive& stream, const set_of_type<T>& vl) {


                    typedef typename set_of_type<T>::const_iterator   set_type_iterator;
                    for (set_type_iterator itr = vl.begin() ; itr != vl.end() ; ++itr)
                        operator<<(stream, *itr );


                    return stream;
                }

                template<typename T>
                archive& operator<<(archive& stream, const explicit_value<T>& vl) {

                    stream.add( to_x690_cast(tag( vl.id() , vl.mask() | CONSTRUCTED_ENCODING)));
                    archive::iterator_list_const_buffers it = stream.last();

                    std::size_t sz = stream.size();
                    stream << implicit_value<T > (vl.value());
                    sz = stream.size(sz);
                    ++it;

                    if ((stream.rule() == CER_ENCODING)) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2.0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    return stream;
                }

                template<typename T>
                archive& operator<<(archive& stream, const implicit_value<T>& vl) {

                    stream.add( to_x690_cast(tag(vl.id(), vl.mask() | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING : CONSTRUCTED_ENCODING) )));
                    archive::iterator_list_const_buffers it = stream.last();

                    std::size_t sz = stream.size();
                    stream << vl.value();
                    sz = stream.size(sz);
                    ++it;

                    if  ((!tag_traits<T>::primitive()) && (stream.rule() == CER_ENCODING)) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2.0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    return stream;
                }

                ////////////////// STRING REALIZATION

                template<typename T>
                void x690_string_to_stream_cast(const T& val, archive& stream, int8_t lentype) {
                    if (!lentype) {

                        stream.add(val);
                        return;
                    }
                    else {

                        typedef typename T::const_iterator     const_iterator_type;
                        typedef typename T::difference_type   difference_type;

                        const_iterator_type it = val.begin();
                        while (it != val.end()) {
                            stream.add(row_type(1, static_cast<row_type::value_type> ( tag_traits<T>::number())));
                            difference_type  diff = std::distance(it, val.end());
                            if (diff > CER_STRING_MAX_SIZE) {
                                diff = CER_STRING_MAX_SIZE;
                                stream.add(to_x690_cast(size_class(static_cast<std::size_t> (diff))));
                            }
                            else {
                                stream.add(to_x690_cast(size_class(static_cast<std::size_t> (diff))));
                            }
                            stream.add(row_type(val.begin(), val.begin() + diff));
                            it = it + diff;
                        }
                    }
                }


                template<>
                void x690_string_to_stream_cast(const bitstring_type& val, archive& stream, int8_t lentype);

                template<typename T>
                archive& stringtype_writer(archive& stream, const T& vl, id_type  id , int8_t mask) {



                    int8_t construct = vl.size()<( tag_traits<T>::number() == TYPE_BITSTRING ? (CER_STRING_MAX_SIZE - 1) : CER_STRING_MAX_SIZE )
                            ?  PRIMITIVE_ENCODING  :  (stream.rule() == CER_ENCODING ?  CONSTRUCTED_ENCODING : PRIMITIVE_ENCODING) ;

                    stream.add( to_x690_cast(tag(tag_traits<T>::number() , mask | construct )));
                    archive::iterator_list_const_buffers it = stream.last();

                    std::size_t sz = stream.size();
                    x690_string_to_stream_cast(vl, stream, construct);
                    sz = stream.size(sz);
                    ++it;

                    if  (construct) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2.0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    return stream;
                }

                template<>
                archive& operator<<(archive& stream, const implicit_value<bitstring_type>& vl);

                template<>
                archive& operator<<(archive& stream, const implicit_value<octetstring_type>& vl);










                /////

                static std::ostream& operator<<(std::ostream& stream, const const_buffers& self) {
                    for (const_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                        stream << dvnci::binary_block_to_hexsequence_debug(std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) ));
                    stream << std::endl;
                    return stream;
                }

                static std::ofstream& operator<<(std::ofstream& stream, const const_buffers& self) {
                    for (const_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                        stream << std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) );
                    stream << std::endl;
                    return stream;
                }



            }

        }
    }
}


#endif	/* ASNBASE_H */

