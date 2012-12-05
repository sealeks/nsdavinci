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
                typedef  boost::asio::iso::iterator_list_mutable_buffers                                                                         iterator_list_mutable_buffers;

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


                const std::size_t CER_STRING_MAX_SIZE = 1000;
                //const std::size_t CER_STRING_MAX_SIZE = 5;




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
                public:


                    typedef std::pair<id_type, list_iterator_pair>                                                                       tlv_iterators_pair;
                    typedef std::multimap<id_type, list_iterator_pair>                                                               list_iterators_map;

                    oarchive(encoding_rule rul = BER_ENCODING) : boost::asio::iso::base_oarchive() , rule_(rul) {
                    }

                    encoding_rule rule() const {
                        return rule_;
                    }
                    
                    template<typename T>
                    void operator&( const T& vl) {
                        *this  <<  implicit_value<T >(vl);
                    }                    

                    template<typename T>
                    void operator&( const explicit_value<T >& vl) {
                        *this  <<  vl;
                    }
                    
                    template<typename T, class Tag, id_type ID,  class_type TYPE >
                    void operator&( const explicit_typedef <T, Tag,ID, TYPE>& vl) {               
                        *this  <<  explicit_value<T >(vl.value(), ID, TYPE);
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
                    void operator&( const implicit_typedef <T, Tag,ID, TYPE>& vl) {
                        *this  <<  implicit_value<T >(vl.value(), ID, TYPE);
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
                    
                    void alligntype(iterator_list_const_buffers bg , iterator_list_const_buffers ed){
                        std::cout  << "NEAD ALIGHN TYPE"  << std::endl;
                         

                    }
                    
                    iterator_list_const_buffers next(iterator_list_const_buffers beg) const;



                    /// ------------------------------///////////



                    /*   template<typename T>
                      void save_explicit(const T& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                     *this  <<  explicit_value<T > (vl, id, type);
                      }

                      template<typename T>
                      void save_optional_explicit(const boost::shared_ptr<T>& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                          if (!vl) return;
                     *this  <<  optional_explicit_value<T > (vl, id, type);
                      }

                      template<typename T>
                      void save_implicit(const T& vl, id_type id,  class_type type =  CONTEXT_CLASS) {
                     *this  <<  implicit_value<T > (vl, id, type);
                      }

                      template<typename T>
                      void save_implicit(const T& vl, class_type type =  UNIVERSAL_CLASS) {
                     *this  <<  implicit_value<T > (vl, type);
                      }

                      template<typename T>
                      void save_optional_implicit(const boost::shared_ptr<T>& vl, id_type id,  class_type type =  CONTEXT_CLASS) {
                          if (!vl) return;
                     *this  <<  optional_implicit_value<T > (vl, id, type);
                      }

                      template<typename T>
                      void save_optional_implicit(const boost::shared_ptr<T>& vl, class_type type =  UNIVERSAL_CLASS) {
                          if (!vl) return;
                     *this  <<  optional_implicit_value<T > (vl, type);
                      }

                     template<typename T>
                      void save_map_explicit(const T& vl, list_iterators_map& mps,  id_type ID,  class_type TYPE = CONTEXT_CLASS) {
                          iterator_list_const_buffers itf = last();
                          explicit_value<T> tmp(vl, ID, TYPE);
                     *this  <<  tmp;
                          splice_tlv(mps, ID, itf, last());
                      }

                      template<typename T>
                      void save_optional_map_explicit(const boost::shared_ptr<T>& vl, list_iterators_map& mps,  id_type ID,  class_type TYPE = CONTEXT_CLASS) {

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
                      void save_optional_map_implicit(const boost::shared_ptr<T>& vl, list_iterators_map& mps, id_type ID,  class_type TYPE = CONTEXT_CLASS) {
                          if (!vl) return;
                          iterator_list_const_buffers itf = last();
                          implicit_value<T> tmp(vl, ID, TYPE);
                     *this  << tmp;
                          splice_tlv(mps, ID, itf, last());
                      }

                      template<typename T>
                      void save_optional_map_implicit(const boost::shared_ptr<T>& vl, list_iterators_map& mps, class_type TYPE = UNIVERSAL_CLASS) {
                          if (!vl) return;
                          iterator_list_const_buffers itf = last();
                          implicit_value<T> tmp(vl, TYPE);
                          id_type ID = tmp.id();
                     *this  << tmp;
                          splice_tlv(mps, ID, itf, last());
                      }*/



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



                ////////////////////////////////////////////////////////////////////

                template<typename T>
                inline oarchive& operator<<(oarchive& stream, const T& vl) {
                    stream.add(to_x690_cast(vl));
                    return stream;
                }

             

                template<typename T>
                oarchive& operator<<(oarchive& stream, const explicit_value<T>& vl) {

                    stream.add( to_x690_cast(tag( vl.id() , vl.mask() | CONSTRUCTED_ENCODING)));
                    oarchive::iterator_list_const_buffers it = stream.last();
 
                    std::size_t sz = stream.size();
                    stream & vl.value(); 

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
                oarchive& operator<<(oarchive& stream, const explicit_value< std::vector<T> >& vl) {
                     return stream << implicit_value<std::vector<T> >(vl.value(), vl.id(), vl.type() );
                }   
                
                template<typename T>
                oarchive& operator<<(oarchive& stream, const explicit_value< vector_set_of<T> >& vl) {
                     return stream << implicit_value<vector_set_of<T> >(vl.value(), vl.id(), vl.type() );
                }           
                

                template<typename T>
                oarchive& operator<<(oarchive& stream, const implicit_value<T>& vl) {

                    stream.add( to_x690_cast(tag(vl.id(), vl.mask() | CONSTRUCTED_ENCODING)));
                    oarchive::iterator_list_const_buffers it = stream.last();

                    std::size_t sz = stream.size();
                    const_cast<T*> (&(vl.value()))->serialize(stream);          
                    sz = stream.size(sz);
                    ++it;
                    
                    if ((tag_traits<T>::number()==TYPE_SET)/* && (stream.rule() == CER_ENCODING)*/) {
                        stream.alligntype(it, stream.last());
                    }

                    if   (stream.rule() == CER_ENCODING) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2.0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    return stream;
                }
                
               template<typename T>
                oarchive& operator<<(oarchive& stream, const implicit_value<std::vector<T> >& vl){
                   
                   stream.add( to_x690_cast(tag(vl.id(), vl.mask() | CONSTRUCTED_ENCODING)));
                    oarchive::iterator_list_const_buffers it = stream.last();

                   std::size_t sz = stream.size();
                    typedef typename std::vector<T>::const_iterator   vect_type_iterator;
                    for (vect_type_iterator itr = vl.value().begin() ; itr != vl.value().end() ; ++itr)
                        stream & (*itr );
                    sz = stream.size(sz);
                    ++it;

                    if   (stream.rule() == CER_ENCODING) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2.0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    return stream;                   
               }         
               
               template<typename T>
                oarchive& operator<<(oarchive& stream, const implicit_value<vector_set_of<T> >& vl){
                   
                   stream.add( to_x690_cast(tag(vl.id(), vl.mask() | CONSTRUCTED_ENCODING)));
                    oarchive::iterator_list_const_buffers it = stream.last();

                   std::size_t sz = stream.size();
                    typedef typename vector_set_of<T>::const_iterator   vect_type_iterator;
                    for (vect_type_iterator itr = vl.value().begin() ; itr != vl.value().end() ; ++itr)
                        stream & (*itr );
                    sz = stream.size(sz);
                    ++it;

                    if   (stream.rule() == CER_ENCODING) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2.0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
                    return stream;                   
               }                       
              

                template<typename T>
                oarchive& primitive_sirialize(oarchive& stream, const implicit_value<T>& vl) {

                    stream.add( to_x690_cast(tag(vl.id(), vl.mask())));
                    oarchive::iterator_list_const_buffers it = stream.last();

                    std::size_t sz = stream.size();
                    stream << vl.value();
                    sz = stream.size(sz);
                    ++it;

                    if  ((stream.rule() == CER_ENCODING)) {
                        stream.add( to_x690_cast(size_class()), it);
                        stream.add( row_type(2.0));
                    }
                    else
                        stream.add( to_x690_cast(size_class(sz)), it);
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
                void x690_string_to_stream_cast(const bitstring_type& val, oarchive& stream, int8_t lentype);

                template<typename T>
                oarchive& stringtype_writer(oarchive& stream, const T& vl, id_type  id , int8_t mask) {



                    int8_t construct = vl.size()<( tag_traits<T>::number() == TYPE_BITSTRING ? (CER_STRING_MAX_SIZE - 1) : CER_STRING_MAX_SIZE )
                            ?  PRIMITIVE_ENCODING  :  (stream.rule() == CER_ENCODING ?  CONSTRUCTED_ENCODING : PRIMITIVE_ENCODING) ;

                    stream.add( to_x690_cast(tag(id , mask | construct )));
                    oarchive::iterator_list_const_buffers it = stream.last();

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


                bool find_marked_sequece( const list_mutable_buffers& val, row_type& raw,  std::size_t start = 0);


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
                public:



                    iarchive(encoding_rule rul = BER_ENCODING) : boost::asio::iso::base_iarchive() , rule_(rul) {
                    }

                    encoding_rule rule() const {
                        return rule_;
                    }
                    
                    template<typename T>
                    void operator&(const T& vl) {
                        *this  >>  implicit_value<T >(vl);
                    }                    

                    template<typename T>
                    void operator&(const explicit_value<T >& vl) {
                        *this  >> vl;
                    }
                    
                    template<typename T, class Tag, id_type ID,  class_type TYPE >
                    void operator&( const explicit_typedef <T, Tag,ID, TYPE>& vl) {               
                        *this  >> explicit_value<T >(vl.value(), ID, TYPE);
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
                    void operator&( const implicit_typedef <T, Tag,ID, TYPE>& vl) {               
                        *this  >> implicit_value<T >(vl.value(), ID, TYPE);
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

                    tag next_tag() const {
                        tag tmptag;
                        std::size_t sztag = tag_x690_cast(tmptag, buffers(), buffers().begin());
                        return tmptag;
                    }


                private:

                    encoding_rule        rule_;

                } ;
                
                
                
            


             

                template<typename T>
                iarchive& operator>>(iarchive& stream, const explicit_value<T>& vl) {
                    tag tmptag;
                    std::size_t sztag = tag_x690_cast(tmptag, stream.buffers(), stream.buffers().begin());
                    if (sztag && (vl == tmptag)) {
                        size_class tmpsize;
                        std::size_t szsize = size_x690_cast(tmpsize, stream.buffers(),  stream.buffers().begin() , sztag);                      
                        if (szsize) {
                            stream.pop_front(szsize + sztag);
                            std::size_t beg = stream.size();
                            stream & vl.value();
                            if (tmpsize.undefsize()) {
                                if (stream.is_endof()) {
                                }
                            }
                            else{
                                if ((beg-stream.size())==tmpsize.size()) {
                                 //   std::cout << "check explicit success beg:"  << beg  << " end:"  << stream.size()  <<   " size: " <<  tmpsize.size() << std::endl;
                                }  
                                else{
                                 //   std::cout << "check explicit not Success:"  << beg  << " end:"  << stream.size()  <<   " size: " <<  tmpsize.size() <<  std::endl;
                                }
                            }
                        }
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
                iarchive& operator>>(iarchive& stream, const optional_explicit_value<T>& vl) {
                    tag tmptag;
                    typedef boost::shared_ptr<T> shared_type;
                    std::size_t sztag = tag_x690_cast(tmptag, stream.buffers(), stream.buffers().begin());
                    if (sztag && (vl == tmptag)) {
                        *const_cast<shared_type*> (&(vl.value())) = boost::shared_ptr<T > (new T());
                        stream >> explicit_value<T > (*vl.value(), vl.id(), vl.type());
                    }
                    return stream;
                }

                template<typename T>
                iarchive& operator>>(iarchive& stream, const implicit_value<T>& vl) {
                    tag tmptag;
                    std::size_t sztag = tag_x690_cast(tmptag, stream.buffers(), stream.buffers().begin());
                    if (sztag && (vl == tmptag)) {
                        size_class tmpsize;
                        std::size_t szsize = size_x690_cast(tmpsize,  stream.buffers(), stream.buffers().begin(), sztag);
                        if (szsize) {
                            stream.pop_front(szsize + sztag);
                            std::size_t beg = stream.size();
                         //   stream.push_tlvstack(stream.last(), stream.size());
                            const_cast<T*> (&(vl.value()))->serialize(stream);
                          //  stream.pop_tlvstack();                            
                            if (tmpsize.undefsize()) {
                                if (stream.is_endof()) {
                                }
                            }
                            else{
                                 if ((beg-stream.size())==tmpsize.size()) {
                                 //   std::cout << "check implicit success beg:"  << beg  << " end:"  << stream.size()  <<   " size: " <<  tmpsize.size() << std::endl;
                                }  
                                else{
                                  //  std::cout << "check implicit not Success:"  << beg  << " end:"  << stream.size()  <<   " size: " <<  tmpsize.size() <<  std::endl;
                                }
                            }
                        }
                    }
                    return stream;
                }
                
                template<typename T>
                iarchive& operator>>(iarchive& stream, const implicit_value< std::vector<T> >& vl) {
                    tag tmptag;
                    std::size_t sztag = tag_x690_cast(tmptag, stream.buffers(), stream.buffers().begin());
                    if (sztag && (vl == tmptag)) {
                        size_class tmpsize;
                        std::size_t szsize = size_x690_cast(tmpsize,  stream.buffers(), stream.buffers().begin(), sztag);
                        if (szsize) {
                            stream.pop_front(szsize + sztag);
                            std::size_t beg = stream.size();
                            if (tmpsize.undefsize()) {
                                while(!stream.is_endof() && stream.size()) {
                                    T tmp;
                                    stream & tmp;
                                    const_cast<std::vector<T>* > (&(vl.value()))->push_back(tmp);
                                }
                            }
                            else{
                                 while((beg-stream.size())<tmpsize.size()) {
                                    T tmp;
                                    stream & tmp;
                                    const_cast<std::vector<T>* > (&(vl.value()))->push_back(tmp);                                   
                                }
                            }
                        }
                    }
                    return stream;
                }                

                template<typename T>
                iarchive& operator>>(iarchive& stream, const optional_implicit_value<T>& vl) {
                    tag tmptag;
                    typedef boost::shared_ptr<T> shared_type;
                    std::size_t sztag = tag_x690_cast(tmptag, stream.buffers(), stream.buffers().begin());
                    if (sztag && (vl == tmptag)) {
                        *const_cast<shared_type*> (&(vl.value())) = boost::shared_ptr<T > (new T());
                        stream >> implicit_value<T > (*vl.value(), vl.id(), vl.type());
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
                    tag tmptag;
                    std::size_t sztag = tag_x690_cast(tmptag, stream.buffers(), stream.buffers().begin());
                    if (sztag && (vl == tmptag)) {
                        size_class tmpsize;
                        std::size_t szsize = size_x690_cast(tmpsize,  stream.buffers(), stream.buffers().begin(), sztag);
                        if (szsize) {
                            row_type data;
                            if (boost::asio::iso::row_cast(stream.buffers(), stream.buffers().begin() ,data , szsize + sztag, tmpsize.size())) {
                                if (from_x690_cast(*const_cast<T*> (&vl.value()), data)) {
                                    stream.pop_front(szsize + sztag + tmpsize.size());
                                }
                            }
                        }
                    }
                    return stream;
                }

                template<typename T>
                bool stringtype_reader(iarchive& stream, T& vl, id_type id , int8_t mask) {
                    tag tmptag;
                    std::size_t sztag = tag_x690_cast(tmptag, stream.buffers(),stream.buffers().begin());
                    if (sztag && (id == tmptag.id())) {
                        size_class tmpsize;
                        std::size_t szsize = size_x690_cast(tmpsize,  stream.buffers(), stream.buffers().begin(), sztag);
                        if (szsize) {
                            if (tmpsize.undefsize()) {
                                stream.pop_front(szsize + sztag + tmpsize.size());
                                if (tmptag.mask() & CONSTRUCTED_ENCODING) {
                                    while (!stream.is_endof() && !stream.buffers().empty()) {
                                        if (!stringtype_reader(stream, vl, tag_traits<T>::number()  , mask))
                                            return false;
                                    }
                                    return true;
                                }
                                else {
                                    std::size_t itfnd = 0;
                                    stream.pop_front(szsize + sztag);
                                    if (boost::asio::iso::find_eof(stream.buffers(), stream.buffers().begin() , itfnd)) {
                                        row_type data;
                                        if (boost::asio::iso::row_cast(stream.buffers(),stream.buffers().begin(), data , 0 , itfnd )) {
                                            vl.insert(vl.end(), data.begin(), data.end());
                                            return true;
                                        }
                                    }
                                    return false;
                                }
                            }
                            else {
                                if (tmptag.mask() & CONSTRUCTED_ENCODING) {
                                    while (!stream.buffers().empty()) {
                                        if (!stringtype_reader(stream, vl, tag_traits<T>::number()  , mask)) {
                                            stream.pop_front(szsize + sztag + tmpsize.size());
                                            return true;
                                        }
                                    }
                                    return false;
                                }
                                else {
                                    row_type data;
                                    if (boost::asio::iso::row_cast(stream.buffers(), stream.buffers().begin(), data , szsize + sztag, tmpsize.size())) {
                                        vl.insert(vl.end(), data.begin(), data.end());
                                        stream.pop_front(szsize + sztag + tmpsize.size());
                                        return true;
                                    }
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

