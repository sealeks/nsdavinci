/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
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

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/iso_format.hpp>
#include <boost/date_time/date_format_simple.hpp>
#include <boost/date_time/date_facet.hpp>

#include <iso/archive_stream.h>
#include <iso/asn/utf8.h>

#include <set>

#include <boost/asio/detail/push_options.hpp>

#define BOOST_ASN_SET_REGESTRATE(regtype) \
namespace boost {\
    namespace asio {\
        namespace asn {\
            template<>\
            struct tag_traits< regtype > {\
                static  id_type number() {\
                    return TYPE_SET;\
                }\
                static  int8_t class_type() {\
                    return 0;\
                }\
            } ;\
        }\
    }\
}\

#define BOOST_ASN_TYPE_REGESTRATE(regtype, id, cl) \
namespace boost {\
    namespace asio {\
        namespace asn {\
            template<>\
            struct tag_traits< regtype > {\
                static  id_type number() {\
                    return id;\
                }\
                static  int8_t class_type() {\
                    return static_cast<int8_t>(cl);\
                }\
            } ;\
        }\
    }\
}\

#define BOOST_ASN_UNIVERSALTYPE_REGESTRATE(regtype, id) \
namespace boost {\
    namespace asio {\
        namespace asn {\
            template<>\
            struct tag_traits< regtype > {\
                static  id_type number() {\
                    return id;\
                }\
                static  int8_t class_type() {\
                    return 0;\
                }\
            } ;\
        }\
    }\
}\

#define BOOST_ASN_CHOISE_REGESTRATE(regtype)\
namespace boost {\
    namespace asio {\
        namespace asn {\
            template<typename Archive>\
                void bind_element(Archive& arch, const regtype & vl){\
                    arch & boost::asio::asn::bind_choice(arch, vl);\
                }  \
            template<typename Archive>\
                void bind_element(Archive& arch, regtype & vl){\
                    arch & boost::asio::asn::bind_choice(arch, vl);\
                }  \
        }\
    }\
}\

#define BOOST_ASN_INTERNAL_REGESTRATE(regtype, id) \
            template<>\
            struct tag_traits< regtype > {\
                static  id_type number() {\
                    return id;\
                }\
                static  int8_t class_type() {\
                    return 0;\
                }\
            } ;\

#define BOOST_ASN_TYPEDEF(regtype, type , id, cl)  typedef type  regtype;
#define BOOST_ASN_IMPLICIT_TYPEDEF(regtype, type , id, cl)  typedef boost::asio::asn::implicit_typedef< type, class _____TAGTYPE___##regtype ,  id , boost::asio::asn:: cl>  regtype;
#define BOOST_ASN_EXPLICIT_TYPEDEF(regtype, type , id, cl)  typedef boost::asio::asn::explicit_typedef< type,  class _____TAGTYPE___##regtype , id , boost::asio::asn:: cl>   regtype;      




#define BOOST_ASN_BIND_TAG(var)    boost::asio::asn::bind_basic(arch, var)
#define BOOST_ASN_IMPLICIT_TAG(var, tag)    boost::asio::asn::bind_implicit(arch, var, tag, boost::asio::asn::CONTEXT_CLASS)
#define BOOST_ASN_IMPLICIT_APPLICATION_TAG(var, tag)    boost::asio::asn::bind_implicit(arch, var, tag, boost::asio::asn::APPLICATION_CLASS)
#define BOOST_ASN_IMPLICIT_PRIVATE_TAG(var, tag)    boost::asio::asn::bind_implicit(arch, var, tag, boost::asio::asn::PRIVATE_CLASS)
#define BOOST_ASN_IMPLICIT_UNIVERSAL_TAG(var, tag)    boost::asio::asn::bind_implicit(arch, var, tag, boost::asio::asn::UNIVERSAL_CLASS) 
#define BOOST_ASN_EXPLICIT_TAG(var, tag)    boost::asio::asn::bind_explicit(arch, var, tag, boost::asio::asn::CONTEXT_CLASS)
#define BOOST_ASN_EXPLICIT_APPLICATION_TAG(var, tag)    boost::asio::asn::bind_explicit(arch, var, tag, boost::asio::asn::APPLICATION_CLASS)  
#define BOOST_ASN_EXPLICIT_PRIVATE_TAG(var, tag)    boost::asio::asn::bind_explicit(arch, var, tag, boost::asio::asn::PRIVATE_CLASS)
#define BOOST_ASN_EXPLICIT_UNIVERSAL_TAG(var, tag)    boost::asio::asn::bind_explicit(arch, var, tag, boost::asio::asn::UNIVERSAL_CLASS)
#define BOOST_ASN_CHOICE(var)    boost::asio::asn::bind_choice(arch, var)


#define BOOST_ASN_CHOICE_STRUCT(enm)  boost::asio::asn::___asn__choice__base__< enm> 
#define BOOST_ASN_CHOICE_CHECK(enm) ( arch.__input__()) || (check( enm ))

#define BOOST_ASN_VALUE_CHOICE(nm ,tp ,enm) boost::shared_ptr< tp > nm () const {return get< tp >(enm);}; void nm ( tp * vl) { set( vl, enm );}

#define BOOST_ASN_VALUE_FUNC_DECLARATE( type, var)     boost::shared_ptr< type > var  ## __new () { return var = boost::shared_ptr< type >( new type ());} \
	void  var ##  __free() { var = boost::shared_ptr< type >() ;} \
                boost::shared_ptr< type > var  ## __get_or_create () { return var  ? var  : (var = boost::shared_ptr< type >( new type ()) );} \
                void var  ## __assign ( boost::shared_ptr< type > vl ) { var  =  vl ;} \
                void var  ## __assign ( type * vl ) { var  =  boost::shared_ptr< type >(vl)  ;} \
                void var  ## __assign ( const type & vl ) { var  =  boost::shared_ptr< type >( new type (vl)) ;}





namespace boost {
    namespace asio {
        namespace asn {



            typedef  boost::asio::iso::raw_type                             raw_type;


            typedef  std::size_t                                                     id_type;
            typedef  std::size_t                                                     size_type;




            const int8_t PRIMITIVE_ENCODING = '\x0';
            const int8_t CONSTRUCTED_ENCODING = '\x20';


            ///////////////////

            const id_type   TYPE_EOC = 0x0;
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
            const id_type   TYPE_GRAPHICSTRING = 0x19;
            const id_type   TYPE_VISIBLESTRING = 0x1A;
            const id_type   TYPE_GENERALSTRING = 0x1B;
            const id_type   TYPE_UNIVERSALSTRING = 0x1C;
            const id_type   TYPE_CHARACTERSTRING = 0x1D;
            const id_type   TYPE_BMPSTRING = 0x1E;

            const id_type EXTENDED_TAGID = 31;




            //// EOF_TYPE

            struct eoc_type  {
            } ;



            //// ENUMERATED_TYPE

            typedef int32_t enumerated_base_type;

            class enumerated_type  {
            public:

                enumerated_type(enumerated_base_type vl = 0) : value_(vl) {
                }

                void  value(enumerated_base_type vl) {
                    value_ = vl;
                }

                enumerated_base_type value() const {
                    return value_;
                }

                operator enumerated_base_type() const {
                    return value_;
                }

            private:
                enumerated_base_type value_;
            } ;







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

                explicit bitstring_type(const raw_type& vl, std::size_t unuse = 0);

                explicit bitstring_type(const std::vector<bool>& vl);

                explicit bitstring_type(bool vl, std::size_t n);

                bitstring_type(const dynamic_bitset_type& vl) : std::vector<int8_t>() {
                    construct(vl);
                };

                void  insert_bitstring(const raw_type& val, std::size_t unuse = 0);

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

                //operator raw_type() const; 

                friend bitstring_type operator|(const bitstring_type& ls, const bitstring_type& rs);

                friend bitstring_type operator&(const bitstring_type& ls, const bitstring_type& rs);

                friend bitstring_type operator^(const bitstring_type& ls, const bitstring_type& rs);



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

                explicit  octetstring_type(const raw_type& vl) : std::vector<int8_t>(vl.begin(), vl.end()) {
                }

                octetstring_type(const std::string& vl) : std::vector<int8_t>(vl.begin(), vl.end()) {
                }
                //operator raw_type() const{
                //     return  *this;}   
            } ;


            std::ostream& operator<<(std::ostream& stream, const octetstring_type& vl);


            ///  UTF8STRING TYPE           

            class utf8string_type : public std::string {
            public:

                utf8string_type() : std::string() {
                }

                explicit  utf8string_type(const raw_type& vl) : std::string(vl.begin(), vl.end()) {
                }

                explicit utf8string_type(const std::string& vl) : std::string(vl) {
                }

                utf8string_type(const std::wstring& vl) : std::string(wstr_to_utf8(vl)) {
                }

                operator std::wstring() const {
                    return  (valid()) ? utf8_to_wstr(*this) : std::wstring();
                }

                operator raw_type() const {
                    return (valid()) ? raw_type(begin(), end()) : raw_type();
                }

                std::wstring to_wstring() const {
                    return  (valid()) ? utf8_to_wstr(*this) : std::wstring();
                }

                bool valid() const {
                    return check_utf8(*this);
                }

            } ;


            std::ostream& operator<<(std::ostream& stream, const utf8string_type& vl);



            //  SIMLE STRING TYPE

            template<id_type TAGID>
            class simplestring_type : public std::string {
            public:

                simplestring_type() : std::string() {
                }

                explicit  simplestring_type(const raw_type& vl) : std::string(vl.begin(), vl.end()) {
                }

                simplestring_type(const std::string& vl) : std::string(vl) {
                }

                simplestring_type(const std::string::value_type* vl) : std::string(vl) {
                }

                operator raw_type() const {
                    return raw_type(begin(), end());
                }

                operator std::string() const {
                    return *this;
                }

                static id_type tagid() {
                    return TAGID;
                }

            } ;


            typedef simplestring_type<TYPE_NUMERICSTRING>   numericstring_type;
            typedef simplestring_type<TYPE_PRINTABLESTRING> printablestring_type;
            typedef simplestring_type<TYPE_T61STRING>            t61string_type;
            typedef simplestring_type<TYPE_VIDEOTEXSTRING>  videotexstring_type;
            typedef simplestring_type<TYPE_IA5STRING>            ia5string_type;
            typedef simplestring_type<TYPE_GRAPHICSTRING>   graphicstring_type;
            typedef simplestring_type<TYPE_VISIBLESTRING>    visiblestring_type;
            typedef simplestring_type<TYPE_GENERALSTRING>    generalstring_type;

            inline std::ostream& operator<<(std::ostream& stream, const numericstring_type& vl) {
                return stream << vl.operator  std::string();
            }

            inline std::ostream& operator<<(std::ostream& stream, const printablestring_type& vl) {
                return stream << vl.operator  std::string();
            }

            inline std::ostream& operator<<(std::ostream& stream, const t61string_type& vl) {
                return stream << vl.operator  std::string();
            }

            inline std::ostream& operator<<(std::ostream& stream, const videotexstring_type& vl) {
                return stream << vl.operator  std::string();
            }

            inline std::ostream& operator<<(std::ostream& stream, const ia5string_type& vl) {
                return stream << vl.operator  std::string();
            }

            inline std::ostream& operator<<(std::ostream& stream, const graphicstring_type& vl) {
                return stream << vl.operator  std::string();
            }

            inline std::ostream& operator<<(std::ostream& stream, const visiblestring_type& vl) {
                return stream << vl.operator  std::string();
            }

            inline std::ostream& operator<<(std::ostream& stream, const generalstring_type& vl) {
                return stream << vl.operator  std::string();
            }


            //UNICOD UNI STRING  
            //  32bit

            ///universalstring_type

            class universalstring_type : public std::string {
            public:

                universalstring_type() : std::string() {
                }

                universalstring_type(const std::wstring& vl) : std::string(wstr_to_universalstr(vl)) {
                }

                explicit universalstring_type(const std::string& vl) : std::string(wstr_to_universalstr( utf8_to_wstr(vl))) {
                }

                operator std::wstring() const {
                    return  universalstr_to_wstr(*this);
                }

                operator raw_type() const {
                    return raw_type(begin(), end());
                }

                std::wstring to_wstring() const {
                    return  universalstr_to_wstr(*this);
                }

                std::string to_utf8() const {
                    return  wstr_to_utf8(universalstr_to_wstr(*this));
                }

                operator std::string() const {
                    return *this;
                }


            } ;

            inline std::ostream& operator<<(std::ostream& stream, const universalstring_type& vl) {
                return stream << vl.operator  std::string();
            }

            //UNICOD BMP STRING  
            //  16bit

            ///bmpstring_type

            class bmpstring_type : public std::string {
            public:

                bmpstring_type() : std::string() {
                }

                bmpstring_type(const std::wstring& vl) : std::string(wstr_to_bmpstr(vl)) {
                }

                explicit bmpstring_type(const std::string& vl) : std::string(wstr_to_bmpstr( utf8_to_wstr(vl))) {
                }

                operator std::wstring() const {
                    return  bmpstr_to_wstr(*this);
                }

                operator raw_type() const {
                    return raw_type(begin(), end());
                }

                std::wstring to_wstring() const {
                    return  bmpstr_to_wstr(*this);
                }

                std::string to_utf8() const {
                    return  wstr_to_utf8(bmpstr_to_wstr(*this));
                }

                operator std::string() const {
                    return *this;
                }



            } ;

            inline std::ostream& operator<<(std::ostream& stream, const bmpstring_type& vl) {
                return stream << vl.operator  std::string();
            }

            //  time types


            ///  UTCTIME_TIME TYPE 

            typedef boost::posix_time::ptime utctime_type;

            raw_type from_utctime(const utctime_type& val);

            utctime_type to_utctime(const raw_type& val);

            inline utctime_type now_generator() {
                return boost::posix_time::microsec_clock::universal_time();
            }

            // inline utctime_type nowtest_generator() {
            //      return boost::posix_time::ptime(boost::gregorian::date(2012,11,29));
            //}            


            ///  GENERALSED_TIME TYPE  

            class gentime_type {
            public:

                gentime_type() : val_() {
                }

                gentime_type(const boost::posix_time::ptime& vl) : val_(vl) {
                }

                boost::posix_time::ptime value() const {
                    return val_;
                }

                void value(const boost::posix_time::ptime vl)  {
                    val_ = vl;
                }

                operator boost::posix_time::ptime() const {
                    return val_;
                }

            private:
                boost::posix_time::ptime val_;
            } ;

            class any_type  {
            public:

                any_type() {
                }

                template<typename Archive>
                void bind(Archive& arch) {
                    arch.bind(data);
                }

                void set(const raw_type& dt) {
                    data = dt;
                }

                std::size_t get(raw_type& dt) const {
                    dt.insert(dt.end(), data.begin(), data.end());
                    return data.size();
                }

            private:
                raw_type data;

            } ;


            raw_type from_gentime(const gentime_type& val);

            gentime_type to_gentime(const raw_type& val);

            std::ostream& operator<<(std::ostream& stream, const gentime_type& vl);




            //////

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

            ;

            template<typename T>
            struct tag_traits {

                static  id_type number() {
                    return TYPE_SEQ;
                }

                static  int8_t class_type() {
                    return 0;
                }
            } ;

            template<typename T >
            struct tag_traits< std::deque<T> > {

                static  id_type number() {
                    return TYPE_SET;
                }

                static  int8_t class_type() {
                    return 0;
                }
            } ;

            BOOST_ASN_INTERNAL_REGESTRATE(eoc_type, TYPE_EOC)
            BOOST_ASN_INTERNAL_REGESTRATE(int8_t, TYPE_INTEGER)
            BOOST_ASN_INTERNAL_REGESTRATE(uint8_t, TYPE_INTEGER)
            BOOST_ASN_INTERNAL_REGESTRATE(int16_t, TYPE_INTEGER)
            BOOST_ASN_INTERNAL_REGESTRATE(uint16_t, TYPE_INTEGER)
            BOOST_ASN_INTERNAL_REGESTRATE(int32_t, TYPE_INTEGER)
            BOOST_ASN_INTERNAL_REGESTRATE(uint32_t, TYPE_INTEGER)
            BOOST_ASN_INTERNAL_REGESTRATE(int64_t, TYPE_INTEGER)
            BOOST_ASN_INTERNAL_REGESTRATE(uint64_t, TYPE_INTEGER)
            BOOST_ASN_INTERNAL_REGESTRATE(long double, TYPE_REAL)
            BOOST_ASN_INTERNAL_REGESTRATE(double, TYPE_REAL)
            BOOST_ASN_INTERNAL_REGESTRATE(float, TYPE_REAL)
            BOOST_ASN_INTERNAL_REGESTRATE(bool, TYPE_BOOLEAN)
            BOOST_ASN_INTERNAL_REGESTRATE(oid_type, TYPE_OBJECT_IDENTIFIER)
            BOOST_ASN_INTERNAL_REGESTRATE(reloid_type, TYPE_RELATIVE_OID)
            BOOST_ASN_INTERNAL_REGESTRATE(null_type,  TYPE_NULL)
            BOOST_ASN_INTERNAL_REGESTRATE(bitstring_type, TYPE_BITSTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( octetstring_type,  TYPE_OCTETSTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( enumerated_type,  TYPE_ENUMERATED)
            BOOST_ASN_INTERNAL_REGESTRATE( utf8string_type,  TYPE_UTF8STRING)
            BOOST_ASN_INTERNAL_REGESTRATE( numericstring_type,  TYPE_NUMERICSTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( printablestring_type,  TYPE_PRINTABLESTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( t61string_type,  TYPE_T61STRING)
            BOOST_ASN_INTERNAL_REGESTRATE( videotexstring_type,  TYPE_VIDEOTEXSTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( ia5string_type,  TYPE_IA5STRING)
            BOOST_ASN_INTERNAL_REGESTRATE( graphicstring_type,  TYPE_GRAPHICSTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( visiblestring_type,  TYPE_VISIBLESTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( generalstring_type,  TYPE_GENERALSTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( universalstring_type,  TYPE_UNIVERSALSTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( bmpstring_type,  TYPE_BMPSTRING)
            BOOST_ASN_INTERNAL_REGESTRATE( utctime_type,  TYPE_UTCTIME)
            BOOST_ASN_INTERNAL_REGESTRATE( gentime_type,  TYPE_GENERALZEDTIME)




            //  tag class

            class tag {
            public:

                static const id_type null_tag = (!id_type(0));

                tag() : id_(null_tag), mask_(0) {
                }

                tag(id_type  vl , int8_t type = 0) : id_(vl), mask_(type) {
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

                operator bool() const {
                    return (id_ != null_tag);
                }

                bool constructed() const {
                    return (mask_ & CONSTRUCTED_ENCODING);
                }

                friend bool operator<(const tag& ls, const tag& rs) {
                    if (static_cast<uint8_t> (ls.type() | CONSTRUCTED_ENCODING) == static_cast<uint8_t> (rs.type() | CONSTRUCTED_ENCODING))
                        return ls.id() < rs.id();
                    else
                        return static_cast<uint8_t> (ls.type() | CONSTRUCTED_ENCODING) < static_cast<uint8_t> (rs.type() | CONSTRUCTED_ENCODING);
                }

                friend bool operator==(const tag& ls, const tag& rs) {
                    if (static_cast<uint8_t> (ls.type() | CONSTRUCTED_ENCODING) == static_cast<uint8_t> (rs.type() | CONSTRUCTED_ENCODING))
                        return ls.id() == rs.id();
                    return false;
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

                typedef T    base_type;

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

                bool operator==(const tag& rs) const {
                    return (id() == rs.id() && mask() == rs.mask());
                }

                operator tag() const {
                    return tag(id_, mask_);
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

                explicit implicit_value(T& vl, id_type id,  class_type type) :
                id_(id) ,  val_(vl), mask_(from_cast(type))  {
                }

                explicit implicit_value(const T& vl, id_type id,  class_type type) :
                id_(id) ,  val_(const_cast<T&> (vl)), mask_(from_cast(type))  {
                }

                explicit  implicit_value(T& vl,  class_type type) :
                id_(tag_traits<T>::number()) ,  val_(vl), mask_(from_cast(type))  {
                }

                explicit  implicit_value(const T& vl,  class_type type) :
                id_(tag_traits<T>::number()) ,  val_(const_cast<T&> (vl)) , mask_(from_cast(type))  {
                }

                explicit  implicit_value(T& vl) :
                id_(tag_traits<T>::number()) ,  val_(vl), mask_(tag_traits<T>::class_type())  {
                }

                explicit  implicit_value(const T& vl) :
                id_(tag_traits<T>::number()) ,  val_(const_cast<T&> (vl)) , mask_(tag_traits<T>::class_type())  {
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

                void setcontructed() const {
                    mask_ |= CONSTRUCTED_ENCODING;
                }

                bool operator==(const tag& rs) const {
                    return (id() == rs.id() && (mask() | CONSTRUCTED_ENCODING) == ( rs.mask() | CONSTRUCTED_ENCODING));
                }

                operator tag() const {
                    return tag(id_, mask_);
                }


            private:
                id_type id_;
                T& val_;
                mutable int8_t   mask_;
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

                operator tag() const {
                    return tag(id_, mask_);
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

                explicit optional_implicit_value(T& vl, id_type id,  class_type type) :
                id_(id) ,  val_(vl), mask_(from_cast(type))  {
                }

                explicit optional_implicit_value(const T& vl, id_type id,  class_type type) :
                id_(id) ,  val_(const_cast<T&> (vl)), mask_(from_cast(type))  {
                }

                explicit  optional_implicit_value(T& vl,  class_type type) :
                id_(tag_traits<T>::number()) ,  val_(vl), mask_(from_cast(type))  {
                }

                explicit  optional_implicit_value(const T& vl,  class_type type) :
                id_(tag_traits<T>::number()) ,  val_(const_cast<T&> (vl)) , mask_(from_cast(type))  {
                }

                explicit  optional_implicit_value(T& vl) :
                id_(tag_traits<T>::number()) ,  val_(vl), mask_(tag_traits<T>::class_type())  {
                }

                explicit  optional_implicit_value(const T& vl) :
                id_(tag_traits<T>::number()) ,  val_(const_cast<T&> (vl)) , mask_( tag_traits<T>::class_type())  {
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

                bool operator==(const tag& rs) const {
                    return (id() == rs.id() && (mask() | CONSTRUCTED_ENCODING) == ( rs.mask() | CONSTRUCTED_ENCODING));
                }

                operator tag() const {
                    return tag(id_, mask_);
                }


            private:
                id_type id_;
                T& val_;
                int8_t   mask_;
            } ;


            ////////////////////////////////////////////////////////////////////////////

            template<typename T, class Tag,  id_type ID,  class_type TYPE = CONTEXT_CLASS >
            class implicit_typedef   {
            public:

                implicit_typedef() : value_() {
                }

                implicit_typedef (const T& val) : value_(val) {
                }

                void operator()(const T& val) {
                    value_ = val;
                }

                operator T() const {
                    return value_;
                }

                T operator=(const T& val) {
                    return value_ = val;
                }

                const T& value() const {
                    return value_;
                }

                T& value() {
                    return value_;
                }

                id_type id()  const {
                    return ID;
                }

                class_type type() const {
                    return TYPE;
                }


            private:
                T value_;
            } ;


            ////////////////////////////////////////////////////////////////////////////

            template<typename T, class Tag, id_type ID,  class_type TYPE = CONTEXT_CLASS >
            class explicit_typedef  {
            public:

                explicit_typedef() : value_() {
                }

                explicit_typedef (const T& val) : value_(val) {
                }

                void operator()(const T& val) {
                    value_ = val;
                }

                operator T() const {
                    return value_;
                }

                T operator=(const T& val) {
                    return value_ = val;
                }

                const T& value() const {
                    return value_;
                }

                T& value() {
                    return value_;
                }

                id_type id()  const {
                    return ID;
                }

                class_type type() const {
                    return TYPE;
                }



            private:
                T value_;
            } ;






            ///////////////////////////////////////////////////////////////////////////

            template<typename T >
            class choice_value {
            public:

                typedef  T   root_type;

                choice_value(const T& vl) : val_(vl) {
                }

                choice_value(T& vl) : val_(const_cast<T&> (vl)) {
                }

                const T& value() const {
                    return val_;
                }

                T& value() {
                    return val_;
                }

            private:

                T& val_;
            } ;



            //////////////////////////////////////////////////////////////////////////////////////////////////////       

            template<typename E>
            class ___asn__choice__base__ {

                class base_choice_holder {
                public:

                    base_choice_holder(int type = 0) : type_(type) {
                    }

                    virtual ~base_choice_holder() {
                    }

                    virtual bool empty() const {
                        return true;
                    }

                    int type() const {
                        return type_;
                    }

                    void type( int val) {
                        type_ = val;
                    }
                protected:
                    int type_;
                } ;

                template<typename T>
                class choice_holder : public base_choice_holder {
                public:

                    choice_holder() : base_choice_holder(static_cast<int> (0)) , val_(boost::shared_ptr<T>()) {
                    }

                    choice_holder(T* vl, int ID = 0) : base_choice_holder(static_cast<int> (ID)) , val_(boost::shared_ptr<T>(vl)) {
                    }

                    boost::shared_ptr<T>& value() {
                        return val_;
                    }

                    const boost::shared_ptr<T>& value() const {
                        return val_;
                    }

                    virtual bool empty() const {
                        return false;
                    }

                private:
                    boost::shared_ptr<T> val_;
                } ;


                typedef boost::shared_ptr<base_choice_holder> type_ptr;

            public:

                ___asn__choice__base__() : val_() {
                }

                template<typename T>
                ___asn__choice__base__(T* vl, int id) : val_( new choice_holder<T>(vl, id)) {
                }

                virtual  ~___asn__choice__base__() {
                }

                bool empty() const {
                    return ((!val_) || (val_->empty()));
                }

                E type() const {
                    return static_cast<E> (val_ ? val_->type() : 0);
                }

                void type(E val) {
                    if (val_)
                        val_->type(static_cast<E> (val));
                }

                bool check(E val) {
                    return type() == val;
                }

                template<typename T>
                boost::shared_ptr<T>& value(bool isinput, E tp)  {
                    typedef  choice_holder<T> choice_holder_type;
                    typedef  boost::shared_ptr<choice_holder_type> choice_holder_ptr;
                    if (/*!val_ ||*/ isinput)
                        set ( new T(), tp);
                    // val_ = type_ptr( new choice_holder<T > ());
                    //if (isinput)
                    //type(tp);
                    return  boost::static_pointer_cast< choice_holder_type > (val_)->value();
                }

                template<typename T>
                const boost::shared_ptr<T> get(E ID) const {
                    typedef  choice_holder<T> choice_holder_type;
                    typedef  boost::shared_ptr<choice_holder_type> choice_holder_ptr;
                    return (type() == ID) ?
                            boost::static_pointer_cast< choice_holder_type > (val_)->value() :
                            boost::shared_ptr<T > ();
                }

                template<typename T>
                void set(T* vl, E ID) {
                    typedef  choice_holder<T> choice_holder_type;
                    typedef  boost::shared_ptr<choice_holder_type> choice_holder_ptr;
                    val_ = type_ptr( new choice_holder<T > (vl, static_cast<int> (ID)));
                }

                void free() {
                    val_ = type_ptr();
                }

            protected:

                type_ptr val_;

            } ;


            ////////////////////////////////////////////////////////////////////////////////////////////////////

            template<typename Archive, typename T>
            inline bool bind_basic(Archive & arch, T& vl) {
                std::size_t tst = arch.size();
                arch & implicit_value<T > (vl);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_basic(Archive & arch, boost::shared_ptr<T>& vl) {
                std::size_t tst = arch.size();
                arch & optional_implicit_value<T > (vl);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_basic(Archive & arch, implicit_value<T >& vl) {
                std::size_t tst = arch.size();
                arch & vl;
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_basic(Archive & arch, explicit_value<T >& vl) {
                std::size_t tst = arch.size();
                arch & vl;
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_basic(Archive & arch, optional_implicit_value<T >& vl) {
                std::size_t tst = arch.size();
                arch & vl;
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_basic(Archive & arch, optional_explicit_value<T >& vl) {
                std::size_t tst = arch.size();
                arch & vl;
                return (arch.size() != tst);
            }

            template<typename Archive, typename T,  class Tag, id_type ID,  class_type TYPE>
            inline bool bind_basic(Archive & arch, implicit_typedef<T, Tag, ID, TYPE>& vl) {
                std::size_t tst = arch.size();
                arch & implicit_value<T > (vl.value(), ID, TYPE);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T,  class Tag, id_type ID,  class_type TYPE>
            inline bool bind_basic(Archive & arch, explicit_typedef<T, Tag, ID, TYPE>& vl) {
                std::size_t tst = arch.size();
                arch & explicit_value<T > (vl.value(), ID, TYPE);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T,  class Tag, id_type ID,  class_type TYPE>
            inline bool bind_basic(Archive & arch, boost::shared_ptr< implicit_typedef<T, Tag, ID, TYPE> >& vl) {
                if (!vl) return false;
                std::size_t tst = arch.size();
                arch & implicit_value<T > (vl->value(), ID, TYPE);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T,  class Tag, id_type ID,  class_type TYPE>
            inline bool bind_basic(Archive & arch, boost::shared_ptr< explicit_typedef<T, Tag, ID, TYPE> >& vl) {
                if (!vl) return false;
                std::size_t tst = arch.size();
                arch & explicit_value<T > (vl->value(), ID, TYPE);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_explicit(Archive & arch, T& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & explicit_value<T > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_explicit(Archive & arch, const T& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & explicit_value<T > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_explicit(Archive & arch, boost::shared_ptr<T>& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & optional_explicit_value<T > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_explicit(Archive & arch, const boost::shared_ptr<T>& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & optional_explicit_value<T > (vl, id, type);

                return (arch.size() != tst);
            }

            template<typename Archive, typename T,  class Tag, id_type id,  class_type type>
            inline bool bind_explicit(Archive & arch, implicit_typedef<T, Tag, id, type>& vl) {
                std::size_t tst = arch.size();
                arch & explicit_value<T > (vl.value(), id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T,  class Tag, id_type id,  class_type type>
            inline bool bind_explicit(Archive & arch, explicit_typedef<T, Tag, id, type>& vl) {
                std::size_t tst = arch.size();
                arch & explicit_value<T > (vl.value(), id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_explicit(Archive & arch, std::vector<T>& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & explicit_value<std::vector<T> > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_explicit(Archive & arch, std::deque<T>& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & explicit_value<std::deque<T> > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, T& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & implicit_value<T > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, const T& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & implicit_value<T > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, boost::shared_ptr<T>& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & optional_implicit_value<T > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, const boost::shared_ptr<T>& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & optional_implicit_value<T > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, T& vl,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & implicit_value<T > (vl,  type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, const T& vl, class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & implicit_value<T > (vl,  type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, boost::shared_ptr<T>& vl, class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & optional_implicit_value<T > (vl,  type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, const boost::shared_ptr<T>& vl, class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & optional_implicit_value<T > (vl, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T,  class Tag, id_type id,  class_type type>
            inline bool bind_implicit(Archive & arch, implicit_typedef<T, Tag, id, type>& vl) {
                std::size_t tst = arch.size();
                arch & implicit_value<T > (vl.value(), id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T,  class Tag, id_type id,  class_type type>
            inline bool bind_implicit(Archive & arch, explicit_typedef<T, Tag, id, type>& vl) {
                std::size_t tst = arch.size();
                arch & implicit_value<T > (vl.value(), id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline void bind_implicit(Archive & arch, std::vector<T>& vl, class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & implicit_value<std::vector<T> > (vl, TYPE_SEQ , type);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, std::vector<T>& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & implicit_value<std::vector<T> > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_implicit(Archive & arch, std::deque<T>& vl, id_type id,  class_type type = CONTEXT_CLASS) {
                std::size_t tst = arch.size();
                arch & implicit_value<std::deque<T> > (vl, id, type);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_choice(Archive & arch, T& vl) {
                std::size_t tst = arch.size();
                arch & choice_value<T > (vl);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_choice(Archive & arch,  boost::shared_ptr<T>& vl) {
                std::size_t tst = arch.size();
                arch & choice_value<T > (vl);
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_element(Archive& arch, const T& vl) {
                std::size_t tst = arch.size();
                arch & vl;
                return (arch.size() != tst);
            }

            template<typename Archive, typename T>
            inline bool bind_element(Archive& arch, T& vl) {
                std::size_t tst = arch.size();
                arch & vl;
                return (arch.size() != tst);
            }

        }
    }
}


#endif	/* ASNBASE_H */

