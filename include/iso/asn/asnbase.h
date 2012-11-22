/* 
 * File:   asnbase.h
 * Author: sealeks
 *
 * Created on 2 Р В РЎСљР В РЎвЂўР РЋР РЏР В Р’В±Р РЋР вЂљР РЋР Р‰ 2012 Р В РЎвЂ“., 0:39
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

#include <iso/archive_stream.h>



#include <boost/asio/detail/push_options.hpp>


namespace boost {
    namespace asio {
        namespace asn {



            typedef  boost::asio::iso::row_type                          row_type;
            typedef  boost::asio::iso::const_buffers                const_buffers;


            typedef  std::size_t                                                     id_type;
            typedef  std::size_t                                                     size_type;
            typedef  std::size_t                                                     oidindx_type;



            const int8_t PRIMITIVE_ENCODING = '\x0';
            const int8_t CONSTRUCTED_ENCODING = '\x20';


            ///////////////////

            const id_type   TYPE_BOOLEAN = 0x1;
            const id_type   TYPE_INTEGER = 0x2;
            const id_type   TYPE_BITSTRING = 0x3;
            const id_type   TYPE_OCTETSTRING = 0x4;
            const id_type   TYPE_NULL = 0x5;
            const id_type   TYPE_OBJECT_IDENTIFIER = 0x6;
            const id_type   TYPE_OBJECT_DESCRIPTOR = 0x7;
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


            const id_type EXTENDED_TAGID = 31;




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



            //// ReLATIVE OID_TYPE

            class reloid_type : public std::vector<oidindx_type> {
            public:

                reloid_type() : std::vector<oidindx_type>() {
                }

                reloid_type(const oidindx_type *  vl, std::size_t size);

                reloid_type(const boost::array<oidindx_type, 2 > & vl);

                reloid_type(const boost::array<oidindx_type, 3 > & vl);

                reloid_type(const boost::array<oidindx_type, 4 > & vl);

                reloid_type(const boost::array<oidindx_type, 5 > & vl);

                reloid_type(const boost::array<oidindx_type, 6 > & vl);

                reloid_type(const boost::array<oidindx_type, 7 > & vl);

                reloid_type(const boost::array<oidindx_type, 8 > & vl);

                reloid_type(const boost::array<oidindx_type, 9 > & vl);

                reloid_type(const boost::array<oidindx_type, 10 > & vl);

            } ;



            std::ostream& operator<<(std::ostream& stream, const reloid_type& vl);


            /// NULL TYPE

            class null_type {
            public:
                null_type() {}
            };

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

                //operator row_type() const;               



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

                octetstring_type() : std::vector<int8_t>() {
                }

                explicit  octetstring_type(const row_type& vl) : std::vector<int8_t>(vl.begin(), vl.end()) {
                }

                octetstring_type(const std::string& vl) : std::vector<int8_t>(vl.begin(), vl.end()) {
                }
                //operator row_type() const{
                //     return  *this;}   
            } ;


            std::ostream& operator<<(std::ostream& stream, const octetstring_type& vl);




            ////////

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


            // tag traits

            template<typename T>
            struct tag_traits {

                static  id_type number() {
                    return TYPE_SEQ;
                }

                static  bool primitive() {
                    return false;
                }

            } ;

            template<>
            struct tag_traits<int8_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<uint8_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<int16_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<uint16_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }

                static  bool primitive() {
                    return true;
                }

            } ;

            template<>
            struct tag_traits<int32_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }

                static  bool primitive() {
                    return true;
                }

            } ;

            template<>
            struct tag_traits<uint32_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<int64_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<uint64_t> {

                static  id_type number() {
                    return TYPE_INTEGER;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<long double> {

                static  id_type number() {
                    return TYPE_REAL;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<double> {

                static  id_type number() {
                    return TYPE_REAL;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<float> {

                static  id_type number() {
                    return TYPE_REAL;
                }

                static  bool primitive() {
                    return true;
                }

            } ;

            template<>
            struct tag_traits<bool> {

                static  id_type number() {
                    return TYPE_BOOLEAN;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<oid_type> {

                static  id_type number() {
                    return TYPE_OBJECT_IDENTIFIER;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<reloid_type> {

                static  id_type number() {
                    return TYPE_RELATIVE_OID;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<null_type> {

                static  id_type number() {
                    return TYPE_NULL;
                }

                static  bool primitive() {
                    return true;
                }
            } ;

            template<>
            struct tag_traits<bitstring_type> {

                static  id_type number() {
                    return TYPE_BITSTRING;
                }

                static  bool primitive() {
                    return true;
                }

            } ;

            template<>
            struct tag_traits<octetstring_type> {

                static  id_type number() {
                    return TYPE_OCTETSTRING;
                }

                static  bool primitive() {
                    return true;
                }

            } ;





            //  tag class

            class tag {
            public:

                tag(id_type  vl = 0, int8_t type = 0) : id_(vl), mask_(type) {
                }

                int8_t mask() const {
                    return mask_;
                }

                class_type type() const {
                    return to_class_type(mask_);
                }

                id_type id() const {
                    return id_;
                }

                id_type simpleid() const {
                    return (id_ < EXTENDED_TAGID) ? static_cast<int8_t> (mask_ | id_ ) : 0;
                }

            private:
                id_type id_;
                int8_t   mask_;
            } ;

            inline std::ostream& operator<<(std::ostream& stream, const tag& vl) {
                return stream << "TAG: " << vl.id() << " mask:"  << vl.mask() << '\n';
            }


            ////////////////////////////////////////////////////////////////////////////////////////////////////

            template<typename T>
            class explicit_value {
            public:

                typedef  T   root_type;

                explicit explicit_value(T& vl, id_type id,  class_type type = CONTEXT_CLASS) :  id_(id) , val_(vl), mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
                }

                explicit explicit_value(const T& vl, id_type id,  class_type type = CONTEXT_CLASS) :  id_(id) , val_(const_cast<T&> (vl)), mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
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
                
              bool operator==(const tag& rs) const {
                return (id() == rs.id() && mask() == rs.mask());
              }                     


            private:
                id_type id_;
                T& val_;
                int8_t   mask_;
            } ;




            /////////////////////////////////////////////////////////////////////////////

            template<typename T>
            class implicit_value {
            public:

                typedef  T   root_type;

                explicit implicit_value(T& vl, id_type id,  class_type type = CONTEXT_CLASS) :
                id_(id) ,  val_(vl), mask_(from_cast(type) | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING: CONSTRUCTED_ENCODING))  {
                }

                explicit implicit_value(const T& vl, id_type id,  class_type type = CONTEXT_CLASS) :
                id_(id) ,  val_(const_cast<T&> (vl)), mask_(from_cast(type) | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING: CONSTRUCTED_ENCODING))  {
                }

                explicit  implicit_value(T& vl,  class_type type = CONTEXT_CLASS) :
                id_(tag_traits<T>::number()) ,  val_(vl), mask_(from_cast(type) | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING: CONSTRUCTED_ENCODING))  {
                }

                explicit  implicit_value(const T& vl,  class_type type = CONTEXT_CLASS) : 
                id_(tag_traits<T>::number()) ,  val_(const_cast<T&> (vl)) , mask_(from_cast(type) | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING: CONSTRUCTED_ENCODING))  {
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
                
              bool operator==(const tag& rs) const {
                return (id() == rs.id() && mask() == rs.mask());
              }               


            private:
                id_type id_;
                T& val_;
                int8_t   mask_;
            } ;







            /////////////////////////////////////////////////////////////////////////////

            template<typename S>
            class optional_explicit_value {
            public:

                typedef  boost::shared_ptr<S>    T;
                typedef  S   root_type;

                explicit optional_explicit_value(T& vl, id_type id,  class_type type = CONTEXT_CLASS) :  id_(id) , val_(vl), mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
                }

                explicit optional_explicit_value(const T& vl, id_type id,  class_type type = CONTEXT_CLASS) :  id_(id) , val_(const_cast<T&> (vl)), mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
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
                
              bool operator==(const tag& rs) const {
                return (id() == rs.id() && mask() == rs.mask());
              }                      


            private:
                id_type id_;
                T& val_;
                int8_t   mask_;
            } ;




            /////////////////////////////////////////////////////////////////////////////

            template<typename S>
            class optional_implicit_value {
            public:

                typedef  boost::shared_ptr<S>    T;
                typedef  S   root_type;

                explicit optional_implicit_value(T& vl, id_type id,  class_type type = CONTEXT_CLASS) :
                id_(id) ,  val_(vl), mask_(from_cast(type) | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING: CONSTRUCTED_ENCODING))  {
                }

                explicit optional_implicit_value(const T& vl, id_type id,  class_type type = CONTEXT_CLASS) : 
                id_(id) ,  val_(const_cast<T&> (vl)), mask_(from_cast(type) | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING: CONSTRUCTED_ENCODING))  {
                }

                explicit  optional_implicit_value(T& vl,  class_type type = CONTEXT_CLASS) :
                id_(tag_traits<T>::number()) ,  val_(vl), mask_(from_cast(type) | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING: CONSTRUCTED_ENCODING))  {
                }

                explicit  optional_implicit_value(const T& vl,  class_type type = CONTEXT_CLASS) :
                id_(tag_traits<T>::number()) ,  val_(const_cast<T&> (vl)) , mask_(from_cast(type) | (tag_traits<T>::primitive() ? PRIMITIVE_ENCODING: CONSTRUCTED_ENCODING))  {
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
                    return  tag_traits<S>::primitive() ?  true : false;
                }
                
              bool operator==(const tag& rs) const {
                return (id() == rs.id() && mask() == rs.mask());
              }                     


            private:
                id_type id_;
                T& val_;
                int8_t   mask_;
            } ;





            ///////////////////////////////////////////////////////////////////////////


            ///////////////////////////////////////////////////////////////////////////

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






        }
    }
}


#endif	/* ASNBASE_H */

