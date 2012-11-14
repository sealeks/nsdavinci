/* 
 * File:   asnbase.h
 * Author: sealeks
 *
 * Created on 2 РќРѕСЏР±СЂСЊ 2012 Рі., 0:39
 */

#ifndef ASNBASE_H
#define	ASNBASE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)


#include <boost/asio/detail/config.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_option.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/streambuf.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/dynamic_bitset.hpp>

#include <kernel/constdef.h>
#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/factory.h>
#include <kernel/templ.h>

#include <boost/asio/detail/push_options.hpp>

//#define SET_OBJECT_ID_CONSTANT(nm, arr)   const boost::asio::asn::oidindx_type   ______ARAYYOID##nm []  = #arr ;  const #nm oid_type  = oid_type( ______ARAYYOID##nm,5);

namespace boost {
    namespace asio {
        namespace asn {

            typedef  std::size_t                                                    id_type;
            typedef  std::size_t                                                    size_type;
            typedef  std::size_t                                                    oidindx_type;

            typedef  std::vector<int8_t>                                  row_type;
            typedef  boost::shared_ptr<row_type>               row_type_ptr;
            typedef  std::vector<row_type_ptr>                     vect_row_type_ptr;


            //// OID_TYPE

            class oid_type : public std::vector<oidindx_type> {
            public:

                oid_type() : std::vector<oidindx_type>() {
                }

                oid_type(const oidindx_type *  vl, std::size_t size);

                oid_type(const boost::array<oidindx_type, 2 > & vl);

                oid_type(const boost::array<oidindx_type, 3 > & vl);

                oid_type(const boost::array<oidindx_type, 4 > & vl);

                oid_type(const boost::array<oidindx_type, 5 > & vl);

                oid_type(const boost::array<oidindx_type, 6 > & vl);

                oid_type(const boost::array<oidindx_type, 7 > & vl);

                oid_type(const boost::array<oidindx_type, 8 > & vl);

                oid_type(const boost::array<oidindx_type, 9 > & vl);

                oid_type(const boost::array<oidindx_type, 10 > & vl);

            } ;



            std::ostream& operator<<(std::ostream& stream, const oid_type& vl);


            /// NULL TYPE

            class null_type {

                null_type() {
                }
            } ;

            inline  std::ostream& operator<<(std::ostream& stream, const null_type& vl) {
                return stream << "NULL TYPE" << std::endl;
            }


            ///  BITSTRING TYPE

            class bitstring_type : public std::vector<int8_t> {
            public:

                typedef std::vector<bool>                   bool_vector_type;
                typedef boost::dynamic_bitset<>        dynamic_bitset_type;

                bitstring_type() : std::vector<int8_t>(), unuse_(0) {
                };

                explicit bitstring_type(uint8_t vl, std::size_t unuse = 0);

                explicit bitstring_type(uint16_t vl, std::size_t unuse = 0);

                explicit bitstring_type(uint32_t vl, std::size_t unuse = 0);

                explicit bitstring_type(uint64_t vl, std::size_t unuse = 0);

                explicit bitstring_type(int8_t vl, std::size_t unuse = 0);

                explicit bitstring_type(int16_t vl, std::size_t unuse = 0);

                explicit bitstring_type(int32_t vl, std::size_t unuse = 0);

                explicit bitstring_type(int64_t vl, std::size_t unuse = 0);

                explicit bitstring_type(const row_type& vl, std::size_t unuse = 0);

                explicit bitstring_type(const std::vector<bool>& vl);

                bitstring_type(const dynamic_bitset_type& vl) : std::vector<int8_t>() {
                    construct(vl);
                };

                void  insert_bitstring(const row_type& val, std::size_t unuse = 0);

                std::size_t unusebits() const {
                    return size() ? (unuse_ % 8) : 0;
                }

                std::size_t sizebits() const {
                    return size() * 8 - unusebits() ;
                }

                bool bit(std::size_t num) const;

                void  bit(std::size_t num, bool val);

                operator bool_vector_type() const;
                
                operator dynamic_bitset_type() const;                

                operator uint8_t() const;

                operator uint16_t() const;

                operator uint32_t() const;

                operator uint64_t() const;

                operator int8_t() const;

                operator int16_t() const;

                operator int32_t() const;

                operator int64_t() const;
                
                

            private:

                template<typename T>
                void construct(T val, std::size_t unuse) {
                    if (unuse<sizeof (T)*8) {
                        std::size_t cnt = 0;
                        int8_t tmp = 0;
                        while (cnt < (sizeof (T)*8 - unuse)) {
                            if ((T(1) << cnt) & val)
                                tmp |= int8_t(1) << (7 - (cnt % 8));


                            if (!((++cnt) % 8)) {
                                push_back(tmp);
                                tmp = 0;
                            }

                        }
                        if  ((unuse % 8))
                            push_back(tmp);
                    }
                    unuse %= 8;
                }

                void construct(const std::vector<bool>& vl);

                template<typename T>
                T return_int() const {
                    T tmp(0);
                    std::size_t sz = std::min(sizebits(), sizeof (T)*8);
                    for (std::size_t i = 0; i < sz; ++i)
                        tmp |= T(1) << i;
                    return tmp;
                }

                void construct(const dynamic_bitset_type& vl);

                std::size_t unuse_;


            } ;
                       

            std::ostream& operator<<(std::ostream& stream, const bitstring_type& vl);
            
 
            ///  OCTETSTRING TYPE           



            class octetstring_type : public std::vector<int8_t> {  
            public:
                octetstring_type() : std::vector<int8_t>(){}
                explicit  octetstring_type(const row_type& vl) : std::vector<int8_t>(vl.begin(), vl.end()) {}         
                octetstring_type(const std::string& vl) : std::vector<int8_t>(vl.begin(), vl.end()) {}                  
            };       
            
            
           std::ostream& operator<<(std::ostream& stream, const octetstring_type& vl);
           
           
           ////////
           
 
            
            
           std::ostream& operator<<(std::ostream& stream, const octetstring_type& vl);          

       

            typedef enum {
                BER_ENCODING,
                CER_ENCODING,
                DER_ENCODING
            }   encoding_rule;

            typedef enum {
                UNIVERSAL_CLASS = 0x0,
                APPLICATION_CLASS = 0x40,
                CONTEXT_CLASS = 0x80,
                PRIVATE_CLASS = 0xC0,
            }   class_type;

            inline static  int8_t from_cast(class_type vl) {
                return static_cast<int8_t> (vl);
            }

            class_type to_class_type( int8_t vl);

            typedef enum {
                PRIMITIVE_ENCODING = 0x0,
                CONSTRUCTED_ENCODING = 0x20,
            }   encoding_type;

            inline static  int8_t from_cast(encoding_type vl) {
                return static_cast<int8_t> (vl);
            }

            inline static encoding_type to_encoding_type( int8_t vl) {
                return (vl & 0x20) ? CONSTRUCTED_ENCODING : PRIMITIVE_ENCODING ;
            }

            typedef enum {
                PRIMITIVE_DEFINED_SIZE,
                //PRIMITIVE_UNDEFINED_SIZE,
                //CONSTRUCTED_DEFINED_SIZE,
                CONSTRUCTED_UNDEFINED_SIZE,                       
            }   length_type;
            
          //  inline static length_type lenthtype_cast(int8_t tp, bool undefsz){
          //      return undefsz ?  CONSTRUCTED_UNDEFINED_SIZE  : 
         //           ( (tp & CONSTRUCTED_ENCODING) ? CONSTRUCTED_DEFINED_SIZE : PRIMITIVE_DEFINED_SIZE);
         //   }
            
            




            //////  Endian conv;

            void endian_conv(row_type& val);

            row_type endian_conv_conv(const row_type& val);

            void endian_push_pack(const row_type& val,  row_type& dst);



            ///////////////////

            const id_type   TYPE_BOOLEAN = 0x1;
            const id_type   TYPE_INTEGER = 0x2;
            const id_type   TYPE_BITSTRING = 0x3;
            const id_type   TYPE_OCTETSTRING = 0x4;            
            const id_type   TYPE_NULL = 0x5;
            const id_type   TYPE_OBJECT_IDENTIFIER = 0x6;
            const id_type   TYPE_OBJECT_DESCRIPTOR= 0x7;            
            const id_type   TYPE_EXTERNAL = 0x8;
            const id_type   TYPE_REAL = 0x9;
            const id_type   TYPE_ENUMERATED = 0xA;       
            const id_type   TYPE_EMBEDDED_PDV = 0xB;       
            const id_type   TYPE_UTF8STRING = 0xC;  
            const id_type   TYPE_RELATIVE_OID = 0xD;            
            
            const id_type   TYPE_SEQ = 0x10;            
            const id_type   TYPE_SET = 0x11;
            const id_type   TYPE_NUMERICSTRING = 0x12;
            const id_type   TYPE_PRINTABLESTRING = 0x13;    
            const id_type   TYPE_T61STRING = 0x14;
            const id_type   TYPE_VIDEOTEXSTRING = 0x15;     
            const id_type   TYPE_IA5STRING = 0x16;
            const id_type   TYPE_UTCTIME = 0x17;       
            const id_type   TYPE_GENERALZEDTIME = 0x18;              
            
            
            inline int8_t constructed_type(id_type id, encoding_rule rl){
                if (rl==CER_ENCODING){
                     return '\x20';
                }
                else{
                    return  (id==TYPE_SEQ || id==TYPE_SET || id==TYPE_EMBEDDED_PDV ) ? '\x20' : '\x0';
                }
            }            
            

            template<typename T>
            struct tag_number {

                static  id_type number() {
                    return TYPE_SEQ;
                }
                 
                 static  bool primitive() {
                    return false;
                }
                 
            } ;

            template<>
            struct tag_number<int8_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }
                
                 static  bool primitive() {
                    return true;
                }                
            } ;
            

            template<>
            struct tag_number<uint8_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }
                
                 static  bool primitive() {
                    return true;
                }                      
            } ;

            template<>
            struct tag_number<int16_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }
                
                static  bool primitive() {
                    return true;
                }                      
            } ;

            template<>
            struct tag_number<uint16_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }  
                
                 static  bool primitive() {
                    return true;
                }                      
                
            } ;

            template<>
            struct tag_number<int32_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }
                 
                 static  bool primitive() {
                    return true;
                }                      
                 
            } ;

            template<>
            struct tag_number<uint32_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                } 
                
                 static  bool primitive() {
                    return true;
                }                  
            } ;

            template<>
            struct tag_number<int64_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }
   
                        
                static  bool primitive() {
                    return true;
                }                  
            } ;

            template<>
            struct tag_number<uint64_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }
                 
                 static  bool primitive() {
                    return true;
                }                   
            } ;

            template<>
            struct tag_number<long double> {

                static  id_type number() {
                    return TYPE_REAL;
                } 
                
                static  bool primitive() {
                    return true;
                }                  
            } ;

            template<>
            struct tag_number<double> {

                static  id_type number() {
                    return TYPE_REAL;
                }
         
                
                 static  bool primitive() {
                    return true;
                }                  
            } ;

            template<>
            struct tag_number<float> {

                static  id_type number() {
                    return TYPE_REAL;
                }
                
               static  bool primitive() {
                    return true;
                }                  
                
            } ;

            template<>
            struct tag_number<bool> {

                static  id_type number() {
                    return TYPE_BOOLEAN;
                }
                
                 static  bool primitive() {
                    return true;
                }                  
            } ;

            template<>
            struct tag_number<oid_type> {

                static  id_type number() {
                    return TYPE_OBJECT_IDENTIFIER;
                }
                
                 static  bool primitive() {
                    return true;
                }                  
            } ;

            template<>
            struct tag_number<null_type> {

                static  id_type number() {
                    return TYPE_NULL;
                }    
                
                 static  bool primitive() {
                    return true;
                }                  
            } ;
            
            template<>
            struct tag_number<bitstring_type> {

                static  id_type number() {
                    return TYPE_BITSTRING;
                }
                
                
                 static  bool primitive() {
                    return true;
                }                  
                
            } ;    
            
            template<>
            struct tag_number<octetstring_type> {

                static  id_type number() {
                    return TYPE_OCTETSTRING;
                }               
                
                 static  bool primitive() {
                    return true;
                }                  
                
            } ;      
            
            
            

            class tag {
            public:

                tag(id_type  vl, int8_t type = 0) : id_(vl), mask_(type) {
                }

                int8_t mask() const {
                    return mask_;
                }

                class_type type() const {
                    return to_class_type(mask_);
                }

                encoding_type encoding() const {
                    return to_encoding_type(mask_);
                }

                id_type id() const {
                    return id_;
                }

                id_type simpleid() const {
                    return (id_ < 31 && id_) ? static_cast<int8_t> (mask_ | id_ ) : 0;
                }

            private:
                id_type id_;
                int8_t   mask_;

            } ;

            class size_class {
            public:

                size_class(size_type  vl,  bool undefsize = false) : size_(vl), undefsize_(undefsize) {
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
            
   
                
                
            template<typename T>
            class explicit_value {
            public:

                typedef  T   root_type;
                
                explicit_value() :  id_() , val_(), mask_(from_cast(CONTEXT_CLASS) | from_cast(CONSTRUCTED_ENCODING)) {
                }               

                explicit explicit_value(const T& vl, id_type id,  class_type type = CONTEXT_CLASS) :  id_(id) , val_(vl), mask_(from_cast(type) | from_cast(CONSTRUCTED_ENCODING)) {
                }
                
                explicit  explicit_value(const T& vl, class_type type = CONTEXT_CLASS) :  id_() , val_(vl), mask_(from_cast(type) | from_cast(CONSTRUCTED_ENCODING)) {
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

                encoding_type encoding() const {
                    return to_encoding_type(mask_);
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
                
                implicit_value() : id_() ,  val_(), mask_(from_cast(PRIVATE_CLASS))  {
                }

                explicit implicit_value(const T& vl, id_type id,  class_type type = PRIVATE_CLASS) : id_(id) ,  val_(vl), mask_(from_cast(type))  {
                }
                
                explicit  implicit_value(const T& vl,  class_type type = PRIVATE_CLASS) : id_(tag_number<T>::number()) ,  val_(vl), mask_(from_cast(type))  {
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
                    return  tag_number<T>::primitive() ?  true : false;
                }                    

                encoding_type encoding() const {
                    return to_encoding_type(mask_);
                }

            private:
                id_type id_;                
                T val_;
                int8_t   mask_;
            } ;
            
            
            
           template<typename T >
            class set_of_type : public std::vector<T> {  
            public:
                
                 set_of_type(id_type id = TYPE_SET, class_type type = UNIVERSAL_CLASS) : std::vector<T>(),  id_(id) , mask_(from_cast(type) | from_cast(CONSTRUCTED_ENCODING)) {} 
                
                
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
                                       
                encoding_type encoding() const {
                    return to_encoding_type(mask_);
                }
                
          

            private:
                id_type id_; 
                int8_t   mask_;               
            
            };                 



            /////  CAST FROM AND TO TYPE

            ///////////////////////////////////////////////////////////////////////////////////////////////
            // integer to X.690

            template<typename T>
            std::size_t to_x690_cast(T val, row_type& src, length_type lentype = PRIMITIVE_DEFINED_SIZE) {
                row_type tmp;
                bool negat = (val < 0);



#ifdef BIG_ENDIAN_ARCHITECTURE      
                !!! not implement
#else

                if (negat)
                    if (val & (T(1) << (sizeof (T)*8 - 1))) {
                        val &= ~(T(1) << (sizeof (T)*8 - 1));
                        tmp.push_back(static_cast<row_type::value_type> (0xFF & val));
                        val >>= 8;
                        val |= (T(1) << ((sizeof (T) - 1)*8 - 1));
                    }
                while (val) {
                    tmp.push_back(static_cast<row_type::value_type> (0xFF & val));
                    val >>= 8;
                }
                if (negat && !tmp.empty())
                    while ((tmp.size() > 1) && (tmp.back() == static_cast<row_type::value_type> ('\xFF')))
                        tmp.pop_back();

                if ((tmp.empty() || (!negat && (tmp.back() & '\x80'))))
                    tmp.push_back(static_cast<row_type::value_type> ('\x0'));
                else {
                    if (negat && !(tmp.back() & '\x80'))
                        tmp.push_back(static_cast<row_type::value_type> ('\xFF'));
                }
                endian_push_pack(tmp, src);

#endif                              
                return tmp.size();
            }

            template<>
            std::size_t to_x690_cast(int8_t val, row_type& src, length_type lentype);

            template<>
            std::size_t to_x690_cast(uint8_t val, row_type& src, length_type lentype);


            // integer from X.690            

            template<typename T>
            T  from_x690_cast(row_type val, length_type lentype = PRIMITIVE_DEFINED_SIZE) {
#ifdef BIG_ENDIAN_ARCHITECTURE 
                !!! not implement
#else              
                endian_conv(val);
                if (sizeof (T) > val.size())
                    val.resize(sizeof (T), row_type::value_type((val.empty() || (val.back() & '\x80' )) ? '\xFF' : 0));
                return (*(T*) (&val[0]));
#endif                  
            }


            ///////////////////////////////////////////////////////////////////////////////////
            // tag to X.690


            std::size_t to_x690_cast(const tag& val, row_type& src, length_type lentype = PRIMITIVE_DEFINED_SIZE);

            row_type to_x690_cast(const tag& va, length_type lentype = PRIMITIVE_DEFINED_SIZE);


            ///////////////////////////////////////////////////////////////////////////////////
            // size_class to X.690


            std::size_t to_x690_cast(const size_class& val, row_type& src, length_type lentype = PRIMITIVE_DEFINED_SIZE);

            row_type to_x690_cast(const size_class& val, length_type lentype = PRIMITIVE_DEFINED_SIZE);



            ///////////////////////////////////////////////////////////////////////////////////
            // real to X.690


            template<>
            std::size_t to_x690_cast(double val, row_type& src, length_type lentype);

            template<>
            std::size_t to_x690_cast(float val, row_type& src, length_type lentype);

            template<>
            std::size_t to_x690_cast(long double val, row_type& src, length_type lentype);



            ///////////////////////////////////////////////////////////////////////////////////
            // bool to X.690

            template<>
            std::size_t to_x690_cast(bool val, row_type& src, length_type lentype);

            ///////////////////////////////////////////////////////////////////////////////////
            // null to X.690

            std::size_t to_x690_cast(const null_type& val, row_type& src, length_type lentype = PRIMITIVE_DEFINED_SIZE);


            ///////////////////////////////////////////////////////////////////////////////////
            // oid to X.690


            std::size_t to_x690_cast(const oid_type& val, row_type& src, length_type lentype = PRIMITIVE_DEFINED_SIZE);
            
            
            ///////////////////////////////////////////////////////////////////////////////////
            // bitstring to X.690


            std::size_t to_x690_cast(const bitstring_type& val, row_type& src, length_type lentype = PRIMITIVE_DEFINED_SIZE);    
            
            ///////////////////////////////////////////////////////////////////////////////////
            // bitstring to X.690


            std::size_t to_x690_cast(const octetstring_type& val, row_type& src, length_type lentype = PRIMITIVE_DEFINED_SIZE);                 

            


            ////////////////////////////////////////////////////////////////////////////////////
            // explicit to X.690

            //   template< template T >
            //   std::size_t to_x690_cast(template T& val, row_type& src){
            //       return 0;
            ///   }


            //////////////////////////////////////////////////////////////////////////////////////////

            template<typename T>
            row_type to_x690_cast(T val, length_type lentype = PRIMITIVE_DEFINED_SIZE ) {
                row_type rslt;
                to_x690_cast(val, rslt, lentype);
                return rslt;
            }




            // buffers


            typedef  std::vector<const_buffer>                        const_buffers;
            typedef  std::list<const_buffer>                              list_const_buffers;
            typedef  list_const_buffers::iterator                        iterator_list_const_buffers;
            typedef  boost::shared_ptr<const_buffers>         const_buffers_ptr;



            std::size_t size_of(const const_buffers& val);

            std::size_t size_of(const const_buffers_ptr& val);

            class archive {
            public:

                archive(encoding_rule rul = BER_ENCODING) : rule_(rul) {
                }

                encoding_rule rule() const {
                    return rule_;
                }

                const_buffers  buffers() const {
                    return const_buffers(listbuffers_.begin(), listbuffers_.end());
                }

                iterator_list_const_buffers  add(const row_type& vl)  {
                    rows_vect.push_back(row_type_ptr( new row_type(vl)));
                    return listbuffers_.insert(listbuffers_.end(), const_buffer(&(rows_vect.back()->operator[](0)), rows_vect.back()->size()));
                }

                iterator_list_const_buffers  add(const row_type& vl, iterator_list_const_buffers it)  {
                    rows_vect.push_back(row_type_ptr( new row_type(vl)));
                    return listbuffers_.insert(it, const_buffer(&(rows_vect.back()->operator[](0)), rows_vect.back()->size()));
                }
                
                //iterator_list_const_buffers  end()  {
                //    return  listbuffers_.rbegin().base();
                //}                
                

                std::size_t  size(iterator_list_const_buffers it)  {
                    std::size_t rslt = 0;
                    for (iterator_list_const_buffers i = it; i != listbuffers_.end(); ++i)
                        rslt += boost::asio::buffer_size(*i);
                    return rslt;
                }

                void clear()  {
                    listbuffers_.clear();
                    rows_vect.clear();
                }





            private:

                list_const_buffers listbuffers_;
                encoding_rule rule_;
                vect_row_type_ptr rows_vect;
            } ;
            
            

            std::ostream& operator<<(std::ostream& stream, const archive& vl);

            std::ofstream& operator<<(std::ofstream& stream, const archive& vl);
            
            
            
            template<typename T>
            inline archive& operator<<(archive& stream, const T& vl){
                stream.add(to_x690_cast(vl));          
                return stream;
            }
      
            archive& operator<<(archive& stream, const bitstring_type& vl);
                
            archive& operator<<(archive& stream, const octetstring_type& vl);    
            
            template<typename  T>             
            archive& operator<<(archive& stream, const set_of_type<T>& vl) {      
                //iterator_list_const_buffers it =stream.add( to_x690_cast(tag( TYPE_SET , vl.mask() | '\x20')));
                
                typedef typename set_of_type<T>::const_iterator   set_type_iterator;
                for (set_type_iterator itr=vl.begin() ; itr!=vl.end() ; ++itr)
                   operator<<(stream,*itr );
                
               /* std::size_t sz = stream.size( ++it);
                if (stream.rule()==CER_ENCODING){
                     stream.add( to_x690_cast(size_class(sz, true)), it);
                     stream.add( row_type(2.0));
                }
                else    
                     stream.add( to_x690_cast(size_class(sz)), it);    */            
                
                return stream;}             
            
            
            template<typename T>
            archive& operator<<(archive& stream, const explicit_value<T>& vl) {
                iterator_list_const_buffers it =stream.add( to_x690_cast(tag( vl.id() , vl.mask() | '\x20')));
                stream << implicit_value<T>(vl.value(), vl.id());
                std::size_t sz = stream.size( ++it);
                if ((stream.rule()==CER_ENCODING)){
                     stream.add( to_x690_cast(size_class(sz, true)), it);
                     stream.add( row_type(2.0));
                }
                else    
                     stream.add( to_x690_cast(size_class(sz)), it);
                return stream;
            }

            template<typename T>
            archive& operator<<(archive& stream, const implicit_value<T>& vl) {
                iterator_list_const_buffers it =stream.add( to_x690_cast(tag(tag_number<T>::number(), vl.mask() | (tag_number<T>::primitive() ? '\x0' : '\x20') )));
              //  iterator_list_const_buffers it = stream.end();
                stream << vl.value();   
                std::size_t sz = stream.size( ++it);
                if  ((!tag_number<T>::primitive()) && (stream.rule()==CER_ENCODING)){
                     stream.add( to_x690_cast(size_class(sz, true)), it);
                     stream.add( row_type(2.0));
                }
                else    
                     stream.add( to_x690_cast(size_class(sz)), it);
                return stream;
            }
            
   
            

                         
             
             
 
            

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


#endif	/* ASNBASE_H */

