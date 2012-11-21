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
                // oid to X.690


                std::size_t to_x690_cast(const oid_type& val, row_type& src);

                ///////////////////////////////////////////////////////////////////////////////////
                // relative oid to X.690


                std::size_t to_x690_cast(const reloid_type& val, row_type& src);



                
                
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


                    typedef std::pair<id_type, list_iterator_pair>                                                                         tlv_iterators_pair;
                    typedef std::multimap<id_type, list_iterator_pair>                                                               list_iterators_map;

                    oarchive(encoding_rule rul = BER_ENCODING) : boost::asio::iso::base_oarchive() , rule_(rul) {
                    }

                    encoding_rule rule() const {
                        return rule_;
                    }

                    template<typename T>
                    void operator&( const explicit_value<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T>
                    void operator&( const optional_explicit_value<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T>
                    void operator&( const implicit_value<T >& vl) {
                        *this  <<  vl;
                    }

                    template<typename T>
                    void operator&( const optional_implicit_value<T >& vl) {
                        *this  <<  vl;
                    }



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

                template<typename  T>
                oarchive& operator<<(oarchive& stream, const set_of_type<T>& vl) {


                    typedef typename set_of_type<T>::const_iterator   set_type_iterator;
                    for (set_type_iterator itr = vl.begin() ; itr != vl.end() ; ++itr)
                        stream << implicit_value<T > (*itr );


                    return stream;
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const explicit_value<T>& vl) {

                    stream.add( to_x690_cast(tag( vl.id() , vl.mask() | CONSTRUCTED_ENCODING)));
                    oarchive::iterator_list_const_buffers it = stream.last();

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
                oarchive& operator<<(oarchive& stream, const implicit_value<T>& vl) {

                    stream.add( to_x690_cast(tag(vl.id(), vl.mask() | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING : CONSTRUCTED_ENCODING) )));
                    oarchive::iterator_list_const_buffers it = stream.last();

                    std::size_t sz = stream.size();
                    //stream << vl.value();
                    const_cast<T*> (&(vl.value()))->serialize(stream);
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

                template<typename T>
                oarchive& primitive_sirialize(oarchive& stream, const implicit_value<T>& vl) {

                    stream.add( to_x690_cast(tag(vl.id(), vl.mask() | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING : CONSTRUCTED_ENCODING) )));
                    oarchive::iterator_list_const_buffers it = stream.last();

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

                template<typename T>
                oarchive& operator<<(oarchive& stream, const optional_explicit_value<T>& vl) {
                    if (vl.value())
                        stream << explicit_value<T > (vl.value(), vl.id(), vl.mask());
                    return stream;
                }

                template<typename T>
                oarchive& operator<<(oarchive& stream, const optional_implicit_value<T>& vl) {
                    if (vl.value())
                        stream << implicit_value<T > (vl.value(), vl.id(), vl.mask());
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




                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
                /*INPUT STREAM                                                                                                                                                                                               */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                bool find_marked_sequece( const list_mutable_buffers& val, row_type& raw,  std::size_t start = 0);


                /////  CAST FROM AND TO TYPE

                ///////////////////////////////////////////////////////////////////////////////////////////////
                // integer from X.690          

                template<typename T>
                bool from_x690_cast(T& vl, const row_type& dt) {
                    row_type  val=dt;
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

                std::size_t tag_x690_cast(tag& val, const list_mutable_buffers& src, std::size_t beg = 0);

                ///////////////////////////////////////////////////////////////////////////////////
                // size_class from X.690

                std::size_t size_x690_cast(size_class& val, const list_mutable_buffers& src,  std::size_t beg = 0);
                
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



                //////////////////////////////////////////////////////////
                //   archiver

                class iarchive : public boost::asio::iso::base_iarchive  {
                public:




                    //typedef std::pair<id_type, list_iterator_pair>                                                                         tlv_iterators_pair;
                    //typedef std::multimap<id_type, list_iterator_pair>                                                               list_iterators_map;

                    iarchive(encoding_rule rul = BER_ENCODING) : boost::asio::iso::base_iarchive() , rule_(rul) {
                    }

                    encoding_rule rule() const {
                        return rule_;
                    }

                    template<typename T>
                    void operator&(const explicit_value<T >& vl) {
                        *this  >> vl;
                    }

                    template<typename T>
                    void operator&(const optional_explicit_value<T >& vl) {
                        *this  >>  vl;
                    }

                    template<typename T>
                    void operator&(const implicit_value<T >& vl) {
                        *this  >>  vl;
                    }

                    template<typename T>
                    void operator&(const optional_implicit_value<T >& vl) {
                        *this  >>  vl;
                    }


                private:

                    encoding_rule        rule_;

                } ;
                
                
                
               // template<typename T>
              //  inline void operator>>(const row_type& data, T& vl) {
               //     vl = from_x690_cast<T>(data);
             //   }                
                
                template<typename T>
                iarchive& operator>>(iarchive& stream, const explicit_value<T>& vl) {
                  tag tmptag;  
                  std::size_t sztag = tag_x690_cast(tmptag, stream.buffers());
                  if (sztag && (vl==tmptag)){
                      size_class tmpsize;
                      std::size_t szsize = size_x690_cast(tmpsize,  stream.buffers(), sztag);
                      if (szsize){
                          stream.ready(szsize+sztag);
                          implicit_value<T > (vl.value()) >> stream;
                      }
                  }
                  return stream;
                }     
                
                template<typename T>
                iarchive& operator>>(iarchive& stream, const optional_explicit_value<T>& vl) {
                  tag tmptag;  
                  std::size_t sztag = tag_x690_cast(tmptag, stream.buffers());
                  if (sztag && (vl==tmptag)){
                      size_class tmpsize;
                      std::size_t szsize = size_x690_cast(tmpsize,  stream.buffers(), sztag);
                      if (szsize){
                          stream.ready(szsize+sztag);
                          optional_implicit_value<T > (vl.value()) >> stream;
                      }
                  }
                  return stream;
                }  
                
                 template<typename T>
                iarchive& operator>>(iarchive& stream, const implicit_value<T>& vl) {
                  tag tmptag;  
                  std::size_t sztag = tag_x690_cast(tmptag, stream.buffers());
                  if (sztag && (vl==tmptag)){
                      size_class tmpsize;
                      std::size_t szsize = size_x690_cast(tmpsize,  stream.buffers(), sztag);
                      if (szsize){
                          stream.ready(szsize+sztag);
                          const_cast<T*>(&(vl.value()))->serialize(stream);
                      }
                  }
                  return stream;
                }     
                
                template<typename T>
                iarchive& operator>>(iarchive& stream, const optional_implicit_value<T>& vl) {
               /*   tag tmptag;  
                  std::size_t sztag = tag_x690_cast(tmptag, stream.buffers());
                  if (sztag && tmptag.id()==vl.id() && tmptag.mask()==vl.mask()){
                      size_class tmpsize;
                      std::size_t szsize = size_x690_cast(tmpsize,  stream.buffers(), sztag);
                      if (szsize){
                          stream.ready(szsize+sztag);
                          optional_implicit_value<T > (vl.value()) >> stream;
                      }
                  }*/
                  return stream;
                }      
                
                  template<typename T>
                iarchive&  primitive_desirialize(iarchive& stream, const implicit_value<T>& vl) {
                  tag tmptag;  
                  std::size_t sztag = tag_x690_cast(tmptag, stream.buffers());
                  if (sztag && (vl==tmptag)){
                      size_class tmpsize;
                      std::size_t szsize = size_x690_cast(tmpsize,  stream.buffers(), sztag);
                      if (szsize){                         
                          row_type data;
                          if (boost::asio::iso::row_cast(stream.buffers(), data , szsize+sztag, tmpsize.size())){
                              if (from_x690_cast(*const_cast<T*>(&vl.value()), data)) {
                              stream.ready(szsize+sztag + tmpsize.size());}
                          }
                      }
                  }
                  return stream;
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
                iarchive& operator>>(iarchive& stream, const implicit_value<float>& vl);
                
                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<double>& vl);    
                
                template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<long double>& vl);                   
                 
                 template<>
                iarchive& operator>>(iarchive& stream, const implicit_value<bool>& vl);                    


                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
                /*TESTS                                                                                                                                                                                                              */
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////                

                inline list_mutable_buffers  test_decode(const oarchive& arch) {
                    list_mutable_buffers tmp;
                    const_buffers buff = arch.buffers();
                    for (const_buffers::const_iterator it = buff.begin(); it != buff.end(); ++it)
                        tmp.push_back(mutable_buffer(const_cast<row_type::value_type*> (boost::asio::buffer_cast<const row_type::value_type*>(*it)), boost::asio::buffer_size(*it)));
                    return tmp;
                }

                struct test_decoder {
                    explicit test_decoder(const list_mutable_buffers & src);
                    tag tag_;
                    size_class size_;
                    list_mutable_buffers buff_;
                    std::size_t blk;
                } ;

                inline std::ostream& operator<<(std::ostream& stream, const test_decoder& vl) {
                    stream << "BEGIN------------------------------------------------------------------------" << std::endl;
                    stream << vl.tag_  << vl.size_;
                    stream << "DATA";
                    boost::asio::iso::operator <<(stream, vl.buff_);
                    stream << "END------------------------------------------------------------------------" << std::endl;
                    return stream << '\n';
                }




            }

        }
    }
}


#endif	/* ASNBASE_H */

