//  Copyright 2013 Alexeev Sergey sealeks@mail.ru

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef ASNBASE_H
#define	ASNBASE_H

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4800)
#endif

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)



#include <boost/asio/streambuf.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
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

#include <iso/base_coder.h>
#include <iso/asn/utf8.h>
#include <set>



#define BOOST_ASN_SET_REGESTRATE(regtype) \
namespace boost {\
        namespace asn1 {\
            template<>\
            struct tag_traits< regtype > {\
                static  id_type number() {\
                    return TYPE_SET;\
                }\
                static  octet_type class_type() {\
                    return 0;\
                }\
            } ;\
        }\
}\

#define BOOST_ASN_TYPE_REGESTRATE(regtype, id, cl) \
namespace boost {\
        namespace asn1 {\
            template<>\
            struct tag_traits< regtype > {\
                static  id_type number() {\
                    return id;\
                }\
                static  octet_type class_type() {\
                    return static_cast<octet_type>(cl);\
                }\
            } ;\
        }\
}\

#define BOOST_ASN_UNIVERSALTYPE_REGESTRATE(regtype, id) \
namespace boost {\
        namespace asn1 {\
            template<>\
            struct tag_traits< regtype > {\
                static  id_type number() {\
                    return id;\
                }\
                static  octet_type class_type() {\
                    return 0;\
                }\
            } ;\
        }\
}\

#define BOOST_ASN_CHOISE_REGESTRATE(regtype)\
namespace boost {\
        namespace asn1 {\
            template<typename Archive>\
                void bind_element(Archive& arch, const regtype & vl){\
                    boost::asn1::bind_choice(arch, vl);\
                }  \
            template<typename Archive>\
                void bind_element(Archive& arch, regtype & vl){\
                    boost::asn1::bind_choice(arch, vl);\
                }  \
        }\
}\

#define BOOST_ASN_INTERNAL_REGESTRATE(regtype, id) \
            template<>\
            struct tag_traits< regtype > {\
                static  id_type number() {\
                    return id;\
                }\
                static  octet_type class_type() {\
                    return 0;\
                }\
            } ;\

#define BOOST_ASN_TYPEDEF(regtype, type , id, cl)  typedef type  regtype;
#define BOOST_ASN_IMPLICIT_TYPEDEF(regtype, type , id, cl)  typedef boost::asn1::implicit_typedef< type, class _____TAGTYPE___##regtype ,  id , boost::asn1:: cl>  regtype;
#define BOOST_ASN_EXPLICIT_TYPEDEF(regtype, type , id, cl)  typedef boost::asn1::explicit_typedef< type,  class _____TAGTYPE___##regtype , id , boost::asn1:: cl>   regtype;      




#define BOOST_ASN_BIND_TAG(var)    boost::asn1::bind_basic(arch, var)
#define BOOST_ASN_IMPLICIT_TAG(var, tag)    boost::asn1::bind_implicit(arch, var, tag, boost::asn1::CONTEXT_CLASS)
#define BOOST_ASN_IMPLICIT_APPLICATION_TAG(var, tag)    boost::asn1::bind_implicit(arch, var, tag, boost::asn1::APPLICATION_CLASS)
#define BOOST_ASN_IMPLICIT_PRIVATE_TAG(var, tag)    boost::asn1::bind_implicit(arch, var, tag, boost::asn1::PRIVATE_CLASS)
#define BOOST_ASN_IMPLICIT_UNIVERSAL_TAG(var, tag)    boost::asn1::bind_implicit(arch, var, tag, boost::asn1::UNIVERSAL_CLASS) 
#define BOOST_ASN_EXPLICIT_TAG(var, tag)    boost::asn1::bind_explicit(arch, var, tag, boost::asn1::CONTEXT_CLASS)
#define BOOST_ASN_EXPLICIT_APPLICATION_TAG(var, tag)    boost::asn1::bind_explicit(arch, var, tag, boost::asn1::APPLICATION_CLASS)  
#define BOOST_ASN_EXPLICIT_PRIVATE_TAG(var, tag)    boost::asn1::bind_explicit(arch, var, tag, boost::asn1::PRIVATE_CLASS)
#define BOOST_ASN_EXPLICIT_UNIVERSAL_TAG(var, tag)    boost::asn1::bind_explicit(arch, var, tag, boost::asn1::UNIVERSAL_CLASS)
#define BOOST_ASN_CHOICE(var)    boost::asn1::bind_choice(arch, var)
#define BOOST_ASN_CHOICE_TAG(var, tag)    boost::asn1::bind_implicit(arch, var, tag, boost::asn1::CONTEXT_CLASS)
#define BOOST_ASN_CHOICE_APPLICATION_TAG(var, tag)    boost::asn1::bind_implicit(arch, var, tag, boost::asn1::APPLICATION_CLASS)
#define BOOST_ASN_CHOICE_PRIVATE_TAG(var, tag)    boost::asn1::bind_implicit(arch, var, tag, boost::asn1::PRIVATE_CLASS)
#define BOOST_ASN_CHOICE_UNIVERSAL_TAG(var, tag)    boost::asn1::bind_implicit(arch, var, tag, boost::asn1::APPLICATION_CLASS)

#define BOOST_ASN_EXTENTION   arch.resetextention();

#define BOOST_ASN_CHOICE_STRUCT(enm)  boost::asn1::___asn__choice__base__< enm> 
#define BOOST_ASN_CHOICE_CHECK(enm) ( arch.__input__()) || (check( enm ))

#define BOOST_ASN_VALUE_CHOICE(nm ,tp ,enm) boost::shared_ptr< tp > nm () const {return get< tp >(enm);}; void nm ( tp * vl) { set( vl, enm );} ; void nm ## __new () { set<tp>( enm );}; void nm ## __new ( tp * vl) { set<tp>( vl, enm );};

#define BOOST_ASN_VALUE_FUNC_DECLARATE( type, var)    boost::shared_ptr< type > var  ## __new () { return var = boost::asn1::simple_build_type<type>();} \
               void  var ##  __free() { var = boost::shared_ptr< type >() ;} \
                boost::shared_ptr< type > var  ## __get_or_create () { return var  ? var  : (var = boost::asn1::simple_build_type<type>() );} \
                void var  ## __assign ( boost::shared_ptr< type > vl ) { var  =  vl ;} \
                void var  ## __assign ( type * vl ) { var  =  boost::shared_ptr< type >(vl)  ;} \
                /*void var  ## __assign ( const type & vl ) { var  =  boost::shared_ptr< type >( new type (vl)) ;}*/





namespace boost {
    namespace asn1 {


        using boost::asio::const_buffer;
        using boost::asio::const_buffers_1;
        using boost::asio::mutable_buffer;
        using boost::asio::mutable_buffers_1;

        using  boost::itu::mutable_sequences;
        using  boost::itu::const_sequences;
        using  boost::itu::encoding_rule;
        using  boost::itu::octet_type;        
        using  boost::itu::octet_sequnce;        

        template<typename T>
        inline boost::shared_ptr< T> simple_build_type() {
            return boost::shared_ptr< T > (new T());
        }

        typedef std::size_t id_type;
        typedef std::size_t size_type;

        const octet_type PRIMITIVE_ENCODING = '\x0';
        const octet_type CONSTRUCTED_ENCODING = '\x20';


        ///////////////////

        const id_type TYPE_EOC = 0x0;
        const id_type TYPE_BOOLEAN = 0x1;
        const id_type TYPE_INTEGER = 0x2;
        const id_type TYPE_BITSTRING = 0x3;
        const id_type TYPE_OCTETSTRING = 0x4;
        const id_type TYPE_NULL = 0x5;
        const id_type TYPE_OBJECT_IDENTIFIER = 0x6;
        const id_type TYPE_OBJECT_DESCRIPTOR = 0x7;
        const id_type TYPE_EXTERNAL = 0x8;
        const id_type TYPE_REAL = 0x9;
        const id_type TYPE_ENUMERATED = 0xA;
        const id_type TYPE_EMBEDDED_PDV = 0xB;
        const id_type TYPE_UTF8STRING = 0xC;
        const id_type TYPE_RELATIVE_OID = 0xD;

        const id_type TYPE_SEQ = 0x10;
        const id_type TYPE_SET = 0x11;
        const id_type TYPE_NUMERICSTRING = 0x12;
        const id_type TYPE_PRINTABLESTRING = 0x13;
        const id_type TYPE_T61STRING = 0x14;
        const id_type TYPE_VIDEOTEXSTRING = 0x15;
        const id_type TYPE_IA5STRING = 0x16;
        const id_type TYPE_UTCTIME = 0x17;
        const id_type TYPE_GENERALZEDTIME = 0x18;
        const id_type TYPE_GRAPHICSTRING = 0x19;
        const id_type TYPE_VISIBLESTRING = 0x1A;
        const id_type TYPE_GENERALSTRING = 0x1B;
        const id_type TYPE_UNIVERSALSTRING = 0x1C;
        const id_type TYPE_CHARACTERSTRING = 0x1D;
        const id_type TYPE_BMPSTRING = 0x1E;

        const id_type EXTENDED_TAGID = 31;




        //// EOF_TYPE

        struct eoc_type {
        };



        //// ENUMERATED_TYPE

        typedef int32_t enumerated_base_type;

        class enumerated_type {
        public:

            enumerated_type(enumerated_base_type vl = 0) : value_(vl) {
            }

            void value(enumerated_base_type vl) {
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
        };







        //// ReLATIVE OID_TYPE

        class reloid_type : public std::vector<oidindx_type> {
        public:

            reloid_type() : std::vector<oidindx_type>() {
            }

            reloid_type(const oidindx_type * vl, std::size_t size);

            reloid_type(const boost::array<oidindx_type, 2 > & vl);

            reloid_type(const boost::array<oidindx_type, 3 > & vl);

            reloid_type(const boost::array<oidindx_type, 4 > & vl);

            reloid_type(const boost::array<oidindx_type, 5 > & vl);

            reloid_type(const boost::array<oidindx_type, 6 > & vl);

            reloid_type(const boost::array<oidindx_type, 7 > & vl);

            reloid_type(const boost::array<oidindx_type, 8 > & vl);

            reloid_type(const boost::array<oidindx_type, 9 > & vl);

            reloid_type(const boost::array<oidindx_type, 10 > & vl);

        };



        std::ostream& operator<<(std::ostream& stream, const reloid_type& vl);


        /// NULL TYPE

        class null_type {
        public:

            null_type() {
            }
        };

        inline std::ostream& operator<<(std::ostream& stream, const null_type& vl) {
            return stream << "NULL TYPE" << std::endl;
        }


        ///  BITSTRING TYPE

        class bitstring_type : public std::vector<octet_type> {
        public:

            typedef std::vector<bool> bool_vector_type;
            typedef boost::dynamic_bitset<> dynamic_bitset_type;

            bitstring_type() : std::vector<octet_type>(), unuse_(0) {
            };

            explicit bitstring_type(uint8_t vl, std::size_t unuse = 0);

            explicit bitstring_type(uint16_t vl, std::size_t unuse = 0);

            explicit bitstring_type(uint32_t vl, std::size_t unuse = 0);

            explicit bitstring_type(uint64_t vl, std::size_t unuse = 0);

            explicit bitstring_type(int8_t vl, std::size_t unuse = 0);

            explicit bitstring_type(int16_t vl, std::size_t unuse = 0);

            explicit bitstring_type(int32_t vl, std::size_t unuse = 0);

            explicit bitstring_type(int64_t vl, std::size_t unuse = 0);

            explicit bitstring_type(const octet_sequnce& vl, std::size_t unuse = 0);

            explicit bitstring_type(const std::vector<bool>& vl);

            explicit bitstring_type(bool vl, std::size_t n);

            bitstring_type(const dynamic_bitset_type& vl) : std::vector<octet_type>() {
                construct(vl);
            };

            void insert_bitstring(const octet_sequnce& val, std::size_t unuse = 0);

            std::size_t unusebits() const {
                return size() ? (unuse_ % 8) : 0;
            }

            std::size_t sizebits() const {
                return size() * 8 - unusebits();
            }

            bool bit(std::size_t num) const;

            void bit(std::size_t num, bool val);

            operator bool_vector_type() const;

            operator dynamic_bitset_type() const;

            dynamic_bitset_type dynamic_bitset() const;

            operator uint8_t() const;

            operator uint16_t() const;

            operator uint32_t() const;

            operator uint64_t() const;

            operator int8_t() const;

            operator int16_t() const;

            operator int32_t() const;

            operator int64_t() const;

            friend bitstring_type operator|(const bitstring_type& ls, const bitstring_type& rs);

            friend bitstring_type operator&(const bitstring_type& ls, const bitstring_type& rs);

            friend bitstring_type operator^(const bitstring_type& ls, const bitstring_type& rs);



        private:

            template<typename T>
            void construct(T val, std::size_t unuse) {
                if (unuse<sizeof (T)*8) {
                    std::size_t cnt = 0;
                    octet_type tmp = 0;
                    while (cnt < (sizeof (T)*8 - unuse)) {
                        if ((T(1) << cnt) & val)
                            tmp |= octet_type(1) << (7 - (cnt % 8));


                        if (!((++cnt) % 8)) {
                            push_back(tmp);
                            tmp = 0;
                        }

                    }
                    if ((unuse % 8))
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


        };


        std::ostream& operator<<(std::ostream& stream, const bitstring_type& vl);


        ///  OCTETSTRING TYPE           

        class octetstring_type : public std::vector<octet_type> {
        public:

            octetstring_type() : std::vector<octet_type>() {
            }

            explicit octetstring_type(const octet_sequnce& vl) : std::vector<octet_type>(vl.begin(), vl.end()) {
            }

            octetstring_type(const std::string& vl) : std::vector<octet_type>(vl.begin(), vl.end()) {
            }
            //operator octet_sequnce() const{
            //     return  *this;}   
        };


        std::ostream& operator<<(std::ostream& stream, const octetstring_type& vl);


        ///  UTF8STRING TYPE           

        class utf8string_type : public std::string {
        public:

            utf8string_type() : std::string() {
            }

            explicit utf8string_type(const octet_sequnce& vl) : std::string(vl.begin(), vl.end()) {
            }

            explicit utf8string_type(const std::string& vl) : std::string(vl) {
            }

            utf8string_type(const std::wstring& vl) : std::string(wstr_to_utf8(vl)) {
            }

            operator std::wstring() const {
                return (valid()) ? utf8_to_wstr(*this) : std::wstring();
            }

            operator octet_sequnce() const {
                return (valid()) ? octet_sequnce(begin(), end()) : octet_sequnce();
            }

            std::wstring to_wstring() const {
                return (valid()) ? utf8_to_wstr(*this) : std::wstring();
            }

            bool valid() const {
                return check_utf8(*this);
            }

        };


        std::ostream& operator<<(std::ostream& stream, const utf8string_type& vl);



        //  SIMLE STRING TYPE

        template<id_type TAGID>
        class simplestring_type : public std::string {
        public:

            simplestring_type() : std::string() {
            }

            explicit simplestring_type(const octet_sequnce& vl) : std::string(vl.begin(), vl.end()) {
            }

            simplestring_type(const std::string& vl) : std::string(vl) {
            }

            simplestring_type(const std::string::value_type* vl) : std::string(vl) {
            }

            operator octet_sequnce() const {
                return octet_sequnce(begin(), end());
            }

            operator std::string() const {
                return *this;
            }

            static id_type tagid() {
                return TAGID;
            }

        };


        typedef simplestring_type<TYPE_NUMERICSTRING> numericstring_type;
        typedef simplestring_type<TYPE_PRINTABLESTRING> printablestring_type;
        typedef simplestring_type<TYPE_T61STRING> t61string_type;
        typedef simplestring_type<TYPE_VIDEOTEXSTRING> videotexstring_type;
        typedef simplestring_type<TYPE_IA5STRING> ia5string_type;
        typedef simplestring_type<TYPE_GRAPHICSTRING> graphicstring_type;
        typedef simplestring_type<TYPE_OBJECT_DESCRIPTOR> objectdescriptor_type;
        typedef simplestring_type<TYPE_VISIBLESTRING> visiblestring_type;
        typedef simplestring_type<TYPE_GENERALSTRING> generalstring_type;

        inline std::ostream& operator<<(std::ostream& stream, const numericstring_type& vl) {
            return stream << vl.operator std::string();
        }

        inline std::ostream& operator<<(std::ostream& stream, const printablestring_type& vl) {
            return stream << vl.operator std::string();
        }

        inline std::ostream& operator<<(std::ostream& stream, const t61string_type& vl) {
            return stream << vl.operator std::string();
        }

        inline std::ostream& operator<<(std::ostream& stream, const videotexstring_type& vl) {
            return stream << vl.operator std::string();
        }

        inline std::ostream& operator<<(std::ostream& stream, const ia5string_type& vl) {
            return stream << vl.operator std::string();
        }

        inline std::ostream& operator<<(std::ostream& stream, const graphicstring_type& vl) {
            return stream << vl.operator std::string();
        }

        inline std::ostream& operator<<(std::ostream& stream, const visiblestring_type& vl) {
            return stream << vl.operator std::string();
        }

        inline std::ostream& operator<<(std::ostream& stream, const generalstring_type& vl) {
            return stream << vl.operator std::string();
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

            explicit universalstring_type(const std::string& vl) : std::string(wstr_to_universalstr(utf8_to_wstr(vl))) {
            }

            operator std::wstring() const {
                return universalstr_to_wstr(*this);
            }

            operator octet_sequnce() const {
                return octet_sequnce(begin(), end());
            }

            std::wstring to_wstring() const {
                return universalstr_to_wstr(*this);
            }

            std::string to_utf8() const {
                return wstr_to_utf8(universalstr_to_wstr(*this));
            }

            operator std::string() const {
                return *this;
            }


        };

        inline std::ostream& operator<<(std::ostream& stream, const universalstring_type& vl) {
            return stream << vl.operator std::string();
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

            explicit bmpstring_type(const std::string& vl) : std::string(wstr_to_bmpstr(utf8_to_wstr(vl))) {
            }

            operator std::wstring() const {
                return bmpstr_to_wstr(*this);
            }

            operator octet_sequnce() const {
                return octet_sequnce(begin(), end());
            }

            std::wstring to_wstring() const {
                return bmpstr_to_wstr(*this);
            }

            std::string to_utf8() const {
                return wstr_to_utf8(bmpstr_to_wstr(*this));
            }

            operator std::string() const {
                return *this;
            }



        };

        inline std::ostream& operator<<(std::ostream& stream, const bmpstring_type& vl) {
            return stream << vl.operator std::string();
        }

        //  time types


        ///  UTCTIME_TIME TYPE 

        typedef boost::posix_time::ptime utctime_type;

        octet_sequnce from_utctime(const utctime_type& val);

        utctime_type to_utctime(const octet_sequnce& val);

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

            void value(const boost::posix_time::ptime vl) {
                val_ = vl;
            }

            operator boost::posix_time::ptime() const {
                return val_;
            }

        private:
            boost::posix_time::ptime val_;
        };

        class any_type {
        public:

            any_type() {
            }

            template<typename Archive>
            void bind(Archive& arch) {
                arch.bind(data);
            }

            void set(const octet_sequnce& dt) {
                data = dt;
            }

            std::size_t get(octet_sequnce& dt) const {
                dt.insert(dt.end(), data.begin(), data.end());
                return data.size();
            }

        private:
            octet_sequnce data;

        };


        octet_sequnce from_gentime(const gentime_type& val);

        gentime_type to_gentime(const octet_sequnce& val);

        std::ostream& operator<<(std::ostream& stream, const gentime_type& vl);




        //////

        typedef enum {
            UNIVERSAL_CLASS = 0x0,
            APPLICATION_CLASS = 0x40,
            CONTEXT_CLASS = 0x80,
            PRIVATE_CLASS = 0xC0,
        } class_type;

        inline static octet_type from_cast(class_type vl) {
            return static_cast<octet_type> (vl);
        }

        class_type to_class_type(octet_type vl);


        // tag traits

        ;

        template<typename T>
        struct tag_traits {

            static id_type number() {
                return TYPE_SEQ;
            }

            static octet_type class_type() {
                return 0;
            }
        };

        template<typename T >
        struct tag_traits< std::deque<T> > {

            static id_type number() {
                return TYPE_SET;
            }

            static octet_type class_type() {
                return 0;
            }
        };

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
        BOOST_ASN_INTERNAL_REGESTRATE(null_type, TYPE_NULL)
        BOOST_ASN_INTERNAL_REGESTRATE(bitstring_type, TYPE_BITSTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(octetstring_type, TYPE_OCTETSTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(enumerated_type, TYPE_ENUMERATED)
        BOOST_ASN_INTERNAL_REGESTRATE(utf8string_type, TYPE_UTF8STRING)
        BOOST_ASN_INTERNAL_REGESTRATE(numericstring_type, TYPE_NUMERICSTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(printablestring_type, TYPE_PRINTABLESTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(t61string_type, TYPE_T61STRING)
        BOOST_ASN_INTERNAL_REGESTRATE(videotexstring_type, TYPE_VIDEOTEXSTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(ia5string_type, TYPE_IA5STRING)
        BOOST_ASN_INTERNAL_REGESTRATE(graphicstring_type, TYPE_GRAPHICSTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(objectdescriptor_type, TYPE_OBJECT_DESCRIPTOR)
        BOOST_ASN_INTERNAL_REGESTRATE(visiblestring_type, TYPE_VISIBLESTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(generalstring_type, TYPE_GENERALSTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(universalstring_type, TYPE_UNIVERSALSTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(bmpstring_type, TYPE_BMPSTRING)
        BOOST_ASN_INTERNAL_REGESTRATE(utctime_type, TYPE_UTCTIME)
        BOOST_ASN_INTERNAL_REGESTRATE(gentime_type, TYPE_GENERALZEDTIME)




        //  tag class

        class tag {
        public:

            static const id_type null_tag = (!id_type(0));

            tag() : id_(null_tag), mask_(0) {
            }

            tag(id_type vl, octet_type type = 0) : id_(vl), mask_(type) {
            }

            octet_type mask() const {
                return mask_;
            }

            class_type type() const {
                return to_class_type(mask_);
            }

            id_type id() const {
                return id_;
            }

            id_type simpleid() const {
                return (id_ < EXTENDED_TAGID) ? static_cast<octet_type> (mask_ | id_) : 0;
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
            octet_type mask_;
        };

        inline std::ostream& operator<<(std::ostream& stream, const tag& vl) {
            return stream << "TAG: " << vl.id() << " mask:" << vl.mask() << '\n';
        }












        ////////////////////////////////////////////////////////////////////////////////////////////////////

        template<typename T>
        class explicit_value {
        public:

            typedef T base_type;

            explicit explicit_value(T& vl, id_type id, class_type type = CONTEXT_CLASS) : id_(id), val_(vl), mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
            }

            explicit explicit_value(const T& vl, id_type id, class_type type = CONTEXT_CLASS) : id_(id), val_(const_cast<T&> (vl)), mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
            }

            const T& value() const {
                return val_;
            }

            T& value() {
                return val_;
            }

            id_type id() const {
                return id_;
            }

            class_type type() const {
                return to_class_type(mask_);
            }

            octet_type mask() const {
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
            octet_type mask_;
        };




        /////////////////////////////////////////////////////////////////////////////

        template<typename T>
        class implicit_value {
        public:

            typedef T root_type;

            explicit implicit_value(T& vl, id_type id, class_type type) :
            id_(id), val_(vl), mask_(from_cast(type)) {
            }

            explicit implicit_value(const T& vl, id_type id, class_type type) :
            id_(id), val_(const_cast<T&> (vl)), mask_(from_cast(type)) {
            }

            explicit implicit_value(T& vl, class_type type) :
            id_(tag_traits<T>::number()), val_(vl), mask_(from_cast(type)) {
            }

            explicit implicit_value(const T& vl, class_type type) :
            id_(tag_traits<T>::number()), val_(const_cast<T&> (vl)), mask_(from_cast(type)) {
            }

            explicit implicit_value(T& vl) :
            id_(tag_traits<T>::number()), val_(vl), mask_(tag_traits<T>::class_type()) {
            }

            explicit implicit_value(const T& vl) :
            id_(tag_traits<T>::number()), val_(const_cast<T&> (vl)), mask_(tag_traits<T>::class_type()) {
            }

            const T& value() const {
                return val_;
            }

            T& value() {
                return val_;
            }

            id_type id() const {
                return id_;
            }

            class_type type() const {
                return to_class_type(mask_);
            }

            octet_type mask() const {
                return mask_;
            }

            void setcontructed() const {
                mask_ |= CONSTRUCTED_ENCODING;
            }

            bool operator==(const tag& rs) const {
                return (id() == rs.id() && (mask() | CONSTRUCTED_ENCODING) == (rs.mask() | CONSTRUCTED_ENCODING));
            }

            operator tag() const {
                return tag(id_, mask_);
            }


        private:
            id_type id_;
            T& val_;
            mutable octet_type mask_;
        };







        /////////////////////////////////////////////////////////////////////////////

        template<typename S>
        class optional_explicit_value {
        public:

            typedef boost::shared_ptr<S> T;
            typedef S root_type;

            explicit optional_explicit_value(T& vl, id_type id, class_type type = CONTEXT_CLASS) : id_(id), val_(vl), mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
            }

            explicit optional_explicit_value(const T& vl, id_type id, class_type type = CONTEXT_CLASS) : id_(id), val_(const_cast<T&> (vl)), mask_(from_cast(type) | CONSTRUCTED_ENCODING) {
            }

            const T& value() const {
                return val_;
            }

            T& value() {
                return val_;
            }

            id_type id() const {
                return id_;
            }

            class_type type() const {
                return to_class_type(mask_);
            }

            octet_type mask() const {
                return mask_;
            }

            static bool primitive() {
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
            octet_type mask_;
        };




        /////////////////////////////////////////////////////////////////////////////

        template<typename S>
        class optional_implicit_value {
        public:

            typedef boost::shared_ptr<S> T;
            typedef S root_type;

            explicit optional_implicit_value(T& vl, id_type id, class_type type) :
            id_(id), val_(vl), mask_(from_cast(type)) {
            }

            explicit optional_implicit_value(const T& vl, id_type id, class_type type) :
            id_(id), val_(const_cast<T&> (vl)), mask_(from_cast(type)) {
            }

            explicit optional_implicit_value(T& vl, class_type type) :
            id_(tag_traits<S>::number()), val_(vl), mask_(from_cast(type)) {
            }

            explicit optional_implicit_value(const T& vl, class_type type) :
            id_(tag_traits<S>::number()), val_(const_cast<T&> (vl)), mask_(from_cast(type)) {
            }

            explicit optional_implicit_value(T& vl) :
            id_(tag_traits<S>::number()), val_(vl), mask_(tag_traits<S>::class_type()) {
            }

            explicit optional_implicit_value(const T& vl) :
            id_(tag_traits<S>::number()), val_(const_cast<T&> (vl)), mask_(tag_traits<S>::class_type()) {
            }

            const T& value() const {
                return val_;
            }

            T& value() {
                return val_;
            }

            id_type id() const {
                return id_;
            }

            class_type type() const {
                return to_class_type(mask_);
            }

            octet_type mask() const {
                return mask_;
            }

            bool operator==(const tag& rs) const {
                return (id() == rs.id() && (mask() | CONSTRUCTED_ENCODING) == (rs.mask() | CONSTRUCTED_ENCODING));
            }

            operator tag() const {
                return tag(id_, mask_);
            }


        private:
            id_type id_;
            T& val_;
            octet_type mask_;
        };


        ////////////////////////////////////////////////////////////////////////////

        template<typename T, class Tag, id_type ID, class_type TYPE = CONTEXT_CLASS >
        class implicit_typedef {
        public:

            implicit_typedef() : value_(new T()) {
            }

            implicit_typedef(const T& val) : value_(new T(val)) {
            }

            void operator()(const T& val) {
                *value_ = val;
            }

            operator T() const {
                return *value_;
            }

            T operator=(const T& val) {
                return *value_ = val;
            }

            const T& value() const {
                return *value_;
            }

            T& value() {
                return *value_;
            }

            T& operator*() const // never throws
            {
                return *value_;
            }

            T * operator-> () const // never throws
            {
                return value_.get();
            }

            const boost::shared_ptr<T>& shared_value() const {
                return value_;
            }

            boost::shared_ptr<T>& shared_value() {
                return value_;
            }

            id_type id() const {
                return ID;
            }

            class_type type() const {
                return TYPE;
            }


        private:
            boost::shared_ptr<T> value_;
        };


        ////////////////////////////////////////////////////////////////////////////

        template<typename T, class Tag, id_type ID, class_type TYPE = CONTEXT_CLASS >
        class explicit_typedef {
        public:

            explicit_typedef() : value_(new T()) {
            }

            explicit_typedef(const T& val) : value_(new T(val)) {
            }

            void operator()(const T& val) {
                *value_ = val;
            }

            operator T() const {
                return *value_;
            }

            T operator=(const T& val) {
                return *value_ = val;
            }

            const T& value() const {
                return *value_;
            }

            T& value() {
                return *value_;
            }

            T& operator*() const // never throws
            {
                return *value_;
            }

            T * operator-> () const // never throws
            {
                return *value_.get();
            }

            const boost::shared_ptr<T>& shared_value() const {
                return value_;
            }

            boost::shared_ptr<T>& shared_value() {
                return value_;
            }

            id_type id() const {
                return ID;
            }

            class_type type() const {
                return TYPE;
            }



        private:
            boost::shared_ptr<T> value_;
        };



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

                void type(int val) {
                    type_ = val;
                }
            protected:
                int type_;
            };

            template<typename T>
            class choice_holder : public base_choice_holder {
            public:

                choice_holder() : base_choice_holder(static_cast<int> (0)), val_(boost::shared_ptr<T>()) {
                }

                choice_holder(T* vl, int ID = 0) : base_choice_holder(static_cast<int> (ID)), val_(boost::shared_ptr<T>(vl)) {
                }

                choice_holder(boost::shared_ptr<T> vl, int ID = 0) : base_choice_holder(static_cast<int> (ID)), val_(vl) {
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
            };


            typedef boost::shared_ptr<base_choice_holder> type_ptr;

        public:

            ___asn__choice__base__() : val_() {
            }

            template<typename T>
            ___asn__choice__base__(T* vl, int id) : val_(new choice_holder<T>(vl, id)) {
            }

            virtual ~___asn__choice__base__() {
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
            boost::shared_ptr<T>& value(bool isinput, E tp) {
                typedef choice_holder<T> choice_holder_type;
                typedef boost::shared_ptr<choice_holder_type> choice_holder_ptr;
                if (isinput)
                    set(new T(), tp);
                return boost::static_pointer_cast< choice_holder_type > (val_)->value();
            }

            template<typename T>
            boost::shared_ptr<T> get(E ID) const {
                typedef choice_holder<T> choice_holder_type;
                typedef boost::shared_ptr<choice_holder_type> choice_holder_ptr;
                return (type() == ID) ?
                        boost::static_pointer_cast< choice_holder_type > (val_)->value() :
                        boost::shared_ptr<T > ();
            }

            template<typename T>
            void set(T* vl, E ID) {
                typedef choice_holder<T> choice_holder_type;
                typedef boost::shared_ptr<choice_holder_type> choice_holder_ptr;
                val_ = type_ptr(new choice_holder<T > (vl, static_cast<int> (ID)));
            }

            template<typename T>
            void set(boost::shared_ptr<T> vl, E ID) {
                typedef choice_holder<T> choice_holder_type;
                typedef boost::shared_ptr<choice_holder_type> choice_holder_ptr;
                val_ = type_ptr(new choice_holder<T > (vl, static_cast<int> (ID)));
            }

            template<typename T>
            void set(E ID) {
                typedef choice_holder<T> choice_holder_type;
                typedef boost::shared_ptr<choice_holder_type> choice_holder_ptr;
                val_ = type_ptr(new choice_holder<T > (new T(), static_cast<int> (ID)));
            }

            void free() {
                val_ = type_ptr();
            }

        protected:

            type_ptr val_;

        };

        template<typename T>
        struct value_holder {

            value_holder() : internal_(new T()) {
            }

            explicit value_holder(const T & vl) : internal_(new T(vl)) {
            }

            T& operator*() const {
                return *internal_;
            }

            T& operator=(const T & vl) {
                internal_ = boost::shared_ptr<T > (new T(vl));
                return *internal_;
            }

            T * operator-> () const {
                return internal_.get();
            }


        private:

            boost::shared_ptr<T> internal_;
        };


        ////////////////////////////////////////////////////////////////////////////////////////////////////

        template<typename Archive, typename T>
        inline bool bind_basic(Archive & arch, T& vl) {
            std::size_t tst = arch.size();
            arch & implicit_value<T > (vl);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T>
        inline bool bind_basic(Archive & arch, value_holder<T>& vl) {
            return bind_basic(arch, *vl);
        }

        template<typename Archive, typename T>
        inline bool bind_basic(Archive & arch, boost::shared_ptr<T>& vl) {
            std::size_t tst = arch.size();
            arch & optional_implicit_value<T > (vl);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_basic(Archive & arch, implicit_typedef<T, Tag, ID, TYPE>& vl) {
            std::size_t tst = arch.size();
            arch & implicit_value<T > (vl.value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_basic(Archive & arch, explicit_typedef<T, Tag, ID, TYPE>& vl) {
            std::size_t tst = arch.size();
            arch & explicit_value<T > (vl.value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_basic(Archive & arch, boost::shared_ptr< implicit_typedef<T, Tag, ID, TYPE> >& vl) {
            std::size_t tst = arch.size();
            arch & optional_implicit_value<T > (vl->shared_value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_basic(Archive & arch, boost::shared_ptr< explicit_typedef<T, Tag, ID, TYPE> >& vl) {
            std::size_t tst = arch.size();
            arch & optional_explicit_value<T > (vl->shared_value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T>
        inline bool bind_explicit(Archive & arch, T& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & explicit_value<T > (vl, id, type);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T>
        inline bool bind_explicit(Archive & arch, value_holder<T>& vl, id_type id, class_type type = CONTEXT_CLASS) {
            return bind_explicit(arch, *vl, id, type);
        }

        template<typename Archive, typename T>
        inline bool bind_explicit(Archive & arch, boost::shared_ptr<T>& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & optional_explicit_value<T > (vl, id, type);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_explicit(Archive & arch, explicit_typedef<T, Tag, ID, TYPE>& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & explicit_value<T > (vl.value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_explicit(Archive & arch, boost::shared_ptr< explicit_typedef<T, Tag, ID, TYPE> >& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & optional_explicit_value<T > (vl->shared_value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_explicit(Archive & arch, implicit_typedef<T, Tag, ID, TYPE>& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & explicit_value<T > (vl.value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_explicit(Archive & arch, boost::shared_ptr< implicit_typedef<T, Tag, ID, TYPE> >& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & optional_explicit_value<T > (vl->shared_value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T>
        inline bool bind_implicit(Archive & arch, T& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & implicit_value<T > (vl, id, type);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T>
        inline bool bind_implicit(Archive & arch, value_holder<T>& vl, id_type id, class_type type = CONTEXT_CLASS) {
            return bind_implicit(arch, *vl, id, type);
        }

        template<typename Archive, typename T>
        inline bool bind_implicit(Archive & arch, boost::shared_ptr<T>& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & optional_implicit_value<T > (vl, id, type);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_implicit(Archive & arch, explicit_typedef<T, Tag, ID, TYPE>& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & explicit_value<T > (vl.value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_implicit(Archive & arch, boost::shared_ptr< explicit_typedef<T, Tag, ID, TYPE> >& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & optional_explicit_value<T > (vl->shared_value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_implicit(Archive & arch, implicit_typedef<T, Tag, ID, TYPE>& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & implicit_value<T > (vl.value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T, class Tag, id_type ID, class_type TYPE>
        inline bool bind_implicit(Archive & arch, boost::shared_ptr< implicit_typedef<T, Tag, ID, TYPE> >& vl, id_type id, class_type type = CONTEXT_CLASS) {
            std::size_t tst = arch.size();
            arch & optional_implicit_value<T > (vl->shared_value(), ID, TYPE);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T>
        inline bool bind_choice(Archive & arch, T& vl) {
            std::size_t tst = arch.size();
            vl.serialize(arch);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T>
        inline bool bind_choice(Archive & arch, const T& vl) {
            std::size_t tst = arch.size();
            const_cast<T*> (&(vl))->serialize(arch);
            return (arch.size() != tst);
        }

        template<typename Archive, typename T>
        inline bool bind_choice(Archive & arch, value_holder<T>& vl) {
            return bind_choice(arch, *vl);
        }

        template<typename Archive, typename T>
        inline bool bind_choice(Archive & arch, boost::shared_ptr< T >& vl) {
            if (!vl) {
                if (arch.__input__())
                    vl = boost::shared_ptr< T > (new T());
                else
                    return false;
            }
            if (bind_choice(arch, *vl))
                return true;
            vl.reset();
            return false;
        }

        template<typename Archive, typename T>
        inline bool bind_element(Archive& arch, T& vl) {
            std::size_t tst = arch.size();
            arch & vl;
            return (arch.size() != tst);
        }

        template<typename Archive, typename T>
        inline bool bind_element(Archive& arch, value_holder<T>& vl) {
            return bind_element(arch, (*vl));
        }



#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4065)
#endif            



        /////////////////////////////////////////////////////////////////////////////////////////////////

        struct external_type {
            //start==============================================================
            //It is  INTERNAL CHOICE

            enum encoding_type_enum {
                encoding_type_null = 0,
                encoding_type_single_ASN1_type,
                encoding_type_octet_aligned,
                encoding_type_arbitrary,
            };

            struct encoding_type : public BOOST_ASN_CHOICE_STRUCT(encoding_type_enum) {

                encoding_type() : BOOST_ASN_CHOICE_STRUCT(encoding_type_enum) () {
                }

                BOOST_ASN_VALUE_CHOICE(single_ASN1_type, any_type, encoding_type_single_ASN1_type)
                BOOST_ASN_VALUE_CHOICE(octet_aligned, octetstring_type, encoding_type_octet_aligned)
                BOOST_ASN_VALUE_CHOICE(arbitrary, bitstring_type, encoding_type_arbitrary)

                        template<typename Archive> void serialize(Archive & arch) {

                    if (arch.__input__()) {
                        int __tag_id__ = arch.test_id();
                        switch (arch.test_class()) {
                            case 0x0:
                            {
                                switch (__tag_id__) {
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            case 0x40:
                            {
                                switch (__tag_id__) {
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            case 0xC0:
                            {
                                switch (__tag_id__) {
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            case 0x80:
                            {
                                switch (__tag_id__) {
                                    case 0:
                                    {
                                        if (BOOST_ASN_EXPLICIT_TAG(value<any_type > (true, encoding_type_single_ASN1_type), 0)) return;
                                        else free();
                                        break;
                                    }
                                    case 1:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<octetstring_type > (true, encoding_type_octet_aligned), 1)) return;
                                        else free();
                                        break;
                                    }
                                    case 2:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<bitstring_type > (true, encoding_type_arbitrary), 2)) return;
                                        else free();
                                        break;
                                    }
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            default:
                            {
                                ;
                            }
                        }
                    }
                    else {
                        switch (type()) {
                            case encoding_type_single_ASN1_type:
                            {
                                BOOST_ASN_EXPLICIT_TAG(value<any_type > (false, encoding_type_single_ASN1_type), 0);
                                break;
                            }
                            case encoding_type_octet_aligned:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<octetstring_type > (false, encoding_type_octet_aligned), 1);
                                break;
                            }
                            case encoding_type_arbitrary:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<bitstring_type > (false, encoding_type_arbitrary), 2);
                                break;
                            }
                            default:
                            {
                            }
                        }
                    }
                }
            };


            boost::shared_ptr<oid_type > direct_reference; //  OPTIONAL
            BOOST_ASN_VALUE_FUNC_DECLARATE(oid_type, direct_reference)

            boost::shared_ptr<int > indirect_reference; //  OPTIONAL
            BOOST_ASN_VALUE_FUNC_DECLARATE(int, indirect_reference)

            boost::shared_ptr<objectdescriptor_type > data_value_descriptor; //  OPTIONAL
            BOOST_ASN_VALUE_FUNC_DECLARATE(objectdescriptor_type, data_value_descriptor)

            boost::asn1::value_holder<encoding_type > encoding;

            external_type() : encoding() {
            }

            template<typename Archive> void serialize(Archive & arch) {

                BOOST_ASN_BIND_TAG(direct_reference);
                BOOST_ASN_BIND_TAG(indirect_reference);
                BOOST_ASN_BIND_TAG(data_value_descriptor);
                BOOST_ASN_CHOICE(encoding);
            }
        };

        BOOST_ASN_INTERNAL_REGESTRATE(external_type, TYPE_EXTERNAL)

        /////////////////////////////////////////////////////////////////////////////////////////////////   

        struct embeded_type {

            enum identification_type_enum {
                identification_type_null = 0,
                identification_type_syntaxes_type,
                identification_type_syntax_type,
                identification_type_presentation_context_id_type,
                identification_type_context_negotiation_type,
                identification_type_transfer_syntax_type,
                identification_type_fixed_type,
            };

            struct identification_type : public BOOST_ASN_CHOICE_STRUCT(identification_type_enum) {

                struct syntaxes_type {
                    oid_type abstract;
                    oid_type transfer;

                    syntaxes_type() : abstract(), transfer() {
                    }

                    template<typename Archive> void serialize(Archive & arch) {

                        BOOST_ASN_IMPLICIT_TAG(abstract, 0);
                        BOOST_ASN_IMPLICIT_TAG(transfer, 1);
                    }
                };

                struct context_negotiation_type {
                    int presentation_context_id;
                    oid_type transfer_syntax;

                    context_negotiation_type() : presentation_context_id(), transfer_syntax() {
                    }

                    template<typename Archive> void serialize(Archive & arch) {

                        BOOST_ASN_IMPLICIT_TAG(presentation_context_id, 0);
                        BOOST_ASN_IMPLICIT_TAG(transfer_syntax, 1);
                    }
                };

                identification_type() : BOOST_ASN_CHOICE_STRUCT(identification_type_enum) () {
                }

                BOOST_ASN_VALUE_CHOICE(syntaxes, syntaxes_type, identification_type_syntaxes_type)
                BOOST_ASN_VALUE_CHOICE(syntax, oid_type, identification_type_syntax_type)
                BOOST_ASN_VALUE_CHOICE(presentation_context_id, int, identification_type_presentation_context_id_type)
                BOOST_ASN_VALUE_CHOICE(context_negotiation, context_negotiation_type, identification_type_context_negotiation_type)
                BOOST_ASN_VALUE_CHOICE(transfer_syntax, oid_type, identification_type_transfer_syntax_type)
                BOOST_ASN_VALUE_CHOICE(fixed, null_type, identification_type_fixed_type)

                        template<typename Archive> void serialize(Archive & arch) {

                    if (arch.__input__()) {
                        int __tag_id__ = arch.test_id();
                        switch (arch.test_class()) {
                            case 0x0:
                            {
                                switch (__tag_id__) {
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            case 0x40:
                            {
                                switch (__tag_id__) {
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            case 0xC0:
                            {
                                switch (__tag_id__) {
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            case 0x80:
                            {
                                switch (__tag_id__) {
                                    case 0:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<syntaxes_type > (true, identification_type_syntaxes_type), 0)) return;
                                        else free();
                                        break;
                                    }
                                    case 1:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<oid_type > (true, identification_type_syntax_type), 1)) return;
                                        else free();
                                        break;
                                    }
                                    case 2:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<int > (true, identification_type_presentation_context_id_type), 2)) return;
                                        else free();
                                        break;
                                    }
                                    case 3:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<context_negotiation_type > (true, identification_type_context_negotiation_type), 3)) return;
                                        else free();
                                        break;
                                    }
                                    case 4:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<oid_type > (true, identification_type_transfer_syntax_type), 4)) return;
                                        else free();
                                        break;
                                    }
                                    case 5:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<null_type > (true, identification_type_fixed_type), 5)) return;
                                        else free();
                                        break;
                                    }
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            default:
                            {
                                ;
                            }
                        }
                    }
                    else {
                        switch (type()) {
                            case identification_type_syntaxes_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<syntaxes_type > (false, identification_type_syntaxes_type), 0);
                                break;
                            }
                            case identification_type_syntax_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<oid_type > (false, identification_type_syntax_type), 1);
                                break;
                            }
                            case identification_type_presentation_context_id_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<int > (false, identification_type_presentation_context_id_type), 2);
                                break;
                            }
                            case identification_type_context_negotiation_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<context_negotiation_type > (false, identification_type_context_negotiation_type), 3);
                                break;
                            }
                            case identification_type_transfer_syntax_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<oid_type > (false, identification_type_transfer_syntax_type), 4);
                                break;
                            }
                            case identification_type_fixed_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<null_type > (false, identification_type_fixed_type), 5);
                                break;
                            }
                            default:
                            {
                            }
                        }
                    }
                }
            };




            identification_type identification;
            boost::shared_ptr< objectdescriptor_type> data_value_descriptor; //  OPTIONAL
            BOOST_ASN_VALUE_FUNC_DECLARATE(objectdescriptor_type, data_value_descriptor)

            octetstring_type data_value;

            embeded_type() : identification(), data_value() {
            }

            template<typename Archive> void serialize(Archive & arch) {

                BOOST_ASN_CHOICE(identification);
                BOOST_ASN_IMPLICIT_TAG(data_value, 1); //  ????
            }
        };

        BOOST_ASN_INTERNAL_REGESTRATE(embeded_type, TYPE_EMBEDDED_PDV)



        //////////////////////////////////////////////////////////////////////////////////////////////////


        struct characterstring_type {

            enum identification_type_enum {
                identification_type_null = 0,
                identification_type_syntaxes_type,
                identification_type_syntax_type,
                identification_type_presentation_context_id_type,
                identification_type_context_negotiation_type,
                identification_type_transfer_syntax_type,
                identification_type_fixed_type,
            };

            struct identification_type : public BOOST_ASN_CHOICE_STRUCT(identification_type_enum) {

                struct syntaxes_type {
                    oid_type abstract;
                    oid_type transfer;

                    syntaxes_type() : abstract(), transfer() {
                    }

                    template<typename Archive> void serialize(Archive & arch) {

                        BOOST_ASN_IMPLICIT_TAG(abstract, 0);
                        BOOST_ASN_IMPLICIT_TAG(transfer, 1);
                    }
                };

                struct context_negotiation_type {
                    int presentation_context_id;
                    oid_type transfer_syntax;

                    context_negotiation_type() : presentation_context_id(), transfer_syntax() {
                    }

                    template<typename Archive> void serialize(Archive & arch) {

                        BOOST_ASN_IMPLICIT_TAG(presentation_context_id, 0);
                        BOOST_ASN_IMPLICIT_TAG(transfer_syntax, 1);
                    }
                };

                identification_type() : BOOST_ASN_CHOICE_STRUCT(identification_type_enum) () {
                }

                BOOST_ASN_VALUE_CHOICE(syntaxes, syntaxes_type, identification_type_syntaxes_type)
                BOOST_ASN_VALUE_CHOICE(syntax, oid_type, identification_type_syntax_type)
                BOOST_ASN_VALUE_CHOICE(presentation_context_id, int, identification_type_presentation_context_id_type)
                BOOST_ASN_VALUE_CHOICE(context_negotiation, context_negotiation_type, identification_type_context_negotiation_type)
                BOOST_ASN_VALUE_CHOICE(transfer_syntax, oid_type, identification_type_transfer_syntax_type)
                BOOST_ASN_VALUE_CHOICE(fixed, null_type, identification_type_fixed_type)

                        template<typename Archive> void serialize(Archive & arch) {

                    if (arch.__input__()) {
                        int __tag_id__ = arch.test_id();
                        switch (arch.test_class()) {
                            case 0x0:
                            {
                                switch (__tag_id__) {
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            case 0x40:
                            {
                                switch (__tag_id__) {
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            case 0xC0:
                            {
                                switch (__tag_id__) {
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            case 0x80:
                            {
                                switch (__tag_id__) {
                                    case 0:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<syntaxes_type > (true, identification_type_syntaxes_type), 0)) return;
                                        else free();
                                        break;
                                    }
                                    case 1:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<oid_type > (true, identification_type_syntax_type), 1)) return;
                                        else free();
                                        break;
                                    }
                                    case 2:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<int > (true, identification_type_presentation_context_id_type), 2)) return;
                                        else free();
                                        break;
                                    }
                                    case 3:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<context_negotiation_type > (true, identification_type_context_negotiation_type), 3)) return;
                                        else free();
                                        break;
                                    }
                                    case 4:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<oid_type > (true, identification_type_transfer_syntax_type), 4)) return;
                                        else free();
                                        break;
                                    }
                                    case 5:
                                    {
                                        if (BOOST_ASN_IMPLICIT_TAG(value<null_type > (true, identification_type_fixed_type), 5)) return;
                                        else free();
                                        break;
                                    }
                                    default:
                                    {
                                    }
                                }
                                ;
                            }
                            default:
                            {
                                ;
                            }
                        }
                    }
                    else {
                        switch (type()) {
                            case identification_type_syntaxes_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<syntaxes_type > (false, identification_type_syntaxes_type), 0);
                                break;
                            }
                            case identification_type_syntax_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<oid_type > (false, identification_type_syntax_type), 1);
                                break;
                            }
                            case identification_type_presentation_context_id_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<int > (false, identification_type_presentation_context_id_type), 2);
                                break;
                            }
                            case identification_type_context_negotiation_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<context_negotiation_type > (false, identification_type_context_negotiation_type), 3);
                                break;
                            }
                            case identification_type_transfer_syntax_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<oid_type > (false, identification_type_transfer_syntax_type), 4);
                                break;
                            }
                            case identification_type_fixed_type:
                            {
                                BOOST_ASN_IMPLICIT_TAG(value<null_type > (false, identification_type_fixed_type), 5);
                                break;
                            }
                            default:
                            {
                            }
                        }
                    }
                }
            };




            identification_type identification;
            boost::shared_ptr<objectdescriptor_type > data_value_descriptor; //  OPTIONAL
            BOOST_ASN_VALUE_FUNC_DECLARATE(objectdescriptor_type, data_value_descriptor)

            octetstring_type string_value;

            characterstring_type() : identification(), string_value() {
            }

            template<typename Archive> void serialize(Archive & arch) {

                BOOST_ASN_CHOICE(identification);
                BOOST_ASN_IMPLICIT_TAG(data_value_descriptor, 1);
                BOOST_ASN_IMPLICIT_TAG(string_value, 2);
            }
        };

        BOOST_ASN_INTERNAL_REGESTRATE(characterstring_type, TYPE_CHARACTERSTRING)


    }
}



#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif	/* ASNBASE_H */

