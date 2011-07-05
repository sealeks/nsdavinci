#ifndef PORTABLE_BINARY_ARCHIVE_HPP
#define PORTABLE_BINARY_ARCHIVE_HPP

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/serialization/pfto.hpp>
#include <boost/static_assert.hpp>

#include <climits>
#if CHAR_BIT != 8
#error This code assumes an eight-bit byte.
#endif

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#if defined(_MSC_VER)
#pragma warning( push )
#pragma warning( disable : 4244 )
#endif



#include <boost/archive/basic_archive.hpp>
#include <boost/detail/endian.hpp>
#include <istream>
#include <ostream>
#include <boost/serialization/string.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/archive/archive_exception.hpp>
#include <boost/archive/basic_binary_iprimitive.hpp>
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/archive/shared_ptr_helper.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/archive/basic_binary_oprimitive.hpp>
#include <boost/archive/detail/common_oarchive.hpp>

#include <kernel/constdef.h>
#include <kernel/utils.h>

namespace dvnci {

    enum prb_binary_archive_flags {
        endian_big        = 0x4000,
        endian_little     = 0x8000} ;

    //#if ( endian_big <= boost::archive::flags_last )
    //#error archive flags conflict
    //#endif

    inline void
    reverse_bytes(char size, char *address) {
        char * first = address;
        char * last = first + size - 1;
        for (; first < last; ++first, --last) {
            char x = *last;
            *last = *first;
            *first = x;}}








    /////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
    // exception to be thrown if integer read from archive doesn't fit
    // variable being loaded

    class prb_binary_iarchive_exception :
    public virtual boost::archive::archive_exception {
    public:

        typedef enum {
            incompatible_integer_size} exception_code;

        prb_binary_iarchive_exception(exception_code c = incompatible_integer_size ) :
        boost::archive::archive_exception(boost::archive::archive_exception::other_exception) {}

        virtual const char *what( ) const throw ( ) {
            const char *msg = "programmer error";
            switch (code) {
                case incompatible_integer_size:
                    msg = "integer cannot be represented";
                    break;
                default:
                    msg = boost::archive::archive_exception::what();
                    assert(false);
                    break;}
            return msg;}} ;

    /////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
    // "Portable" input binary archive.  It addresses integer size and endienness so 
    // that binary archives can be passed across systems. Note:floating point types
    // not addressed here

    class prb_binary_iarchive :
    public boost::archive::basic_binary_iprimitive<
    prb_binary_iarchive,
    std::istream::char_type,
    std::istream::traits_type>,
    public boost::archive::detail::common_iarchive<prb_binary_iarchive>
    ,
    public boost::archive::detail::shared_ptr_helper {
        typedef boost::archive::basic_binary_iprimitive<
        prb_binary_iarchive,
        std::istream::char_type,
        std::istream::traits_type> primitive_base_t;
        typedef boost::archive::detail::common_iarchive<
        prb_binary_iarchive> archive_base_t;
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    public:
#else
        friend archive_base_t;
        friend primitive_base_t; // since with override load below
        friend class boost::archive::detail::interface_iarchive<
        prb_binary_iarchive
        >;
        friend class boost::archive::load_access;
    protected:
#endif
        unsigned int m_flags;
        void load_impl(boost::intmax_t & l, char maxsize);

        // default fall through for any types not specified here

        template<class T>
        void load(T & t) {
            boost::intmax_t l;
            load_impl(l, sizeof (T));
            t = T(l);}

        void load(boost::serialization::item_version_type & t) {
            boost::intmax_t l;
            load_impl(l, sizeof (boost::serialization::item_version_type));
            // use cast to avoid compile time warning
            t = boost::serialization::item_version_type(l);}

        void load(boost::archive::version_type & t) {
            boost::intmax_t l;
            load_impl(l, sizeof (boost::archive::version_type));
            // use cast to avoid compile time warning
            t = boost::archive::version_type(l);}

        void load(boost::archive::class_id_type & t) {
            boost::intmax_t l;
            load_impl(l, sizeof (boost::archive::class_id_type));
            // use cast to avoid compile time warning
            t = boost::archive::class_id_type(static_cast<int> (l));}

        void load(std::string & t) {
            this->primitive_base_t::load(t);}
#ifndef BOOST_NO_STD_WSTRING

        void load(std::wstring & t) {
            this->primitive_base_t::load(t);}
#endif

        void load(float & t) {
            this->primitive_base_t::load(t);}

        void load(double & t) {
            this->primitive_base_t::load(t);}

        void load(char & t) {
            this->primitive_base_t::load(t);}

        void load(unsigned char & t) {
            this->primitive_base_t::load(t);}

        void load(datetime & t) {
            num64 tmp=0;
            this->primitive_base_t::load(tmp);
            t=(*(datetime*)((char*)(&tmp)));}
        
        void load(num64 & t) {
            this->primitive_base_t::load(t);}
        
        void load(unum64 & t) {
            this->primitive_base_t::load(t);}           
        

        typedef boost::archive::detail::common_iarchive<prb_binary_iarchive>
        detail_common_iarchive;

        template<class T>
        void load_override(T & t, BOOST_PFTO int) {
            this->detail_common_iarchive::load_override(t, 0);}
        void load_override(boost::archive::class_name_type & t, int);
        // binary files don't include the optional information 

        void load_override(
                boost::archive::class_id_optional_type & /* t */,
                int
                ) {}

        void init(unsigned int flags);
    public:

        prb_binary_iarchive(std::istream & is, unsigned flags = boost::archive::no_header) :
        primitive_base_t(
        * is.rdbuf(),
        0 != (flags & boost::archive::no_codecvt)
        ),
        archive_base_t(flags),
        m_flags(0) {
            init(flags);}

        prb_binary_iarchive(
                std::basic_streambuf<
                std::istream::char_type,
                std::istream::traits_type
                > & bsb,
                unsigned int flags
                ) :
        primitive_base_t(
        bsb,
        0 != (flags & boost::archive::no_codecvt)
        ),
        archive_base_t(flags),
        m_flags(0) {
            init(flags);}} ;




        //template<>
        //void prb_binary_iarchive::load<datetime>(datetime & t);





    /////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
    // exception to be thrown if integer read from archive doesn't fit
    // variable being loaded

    class prb_binary_oarchive_exception :
    public virtual boost::archive::archive_exception {
    public:

        typedef enum {
            invalid_flags} exception_code;

        prb_binary_oarchive_exception(exception_code c = invalid_flags ) {}

        virtual const char *what( ) const throw ( ) {
            const char *msg = "programmer error";
            switch (code) {
                case invalid_flags:
                    msg = "cannot be both big and little endian";
                default:
                    boost::archive::archive_exception::what();}
            return msg;}} ;

    /////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
    // "Portable" output binary archive.  This is a variation of the native binary 
    // archive. it addresses integer size and endienness so that binary archives can
    // be passed across systems. Note:floating point types not addressed here

    class prb_binary_oarchive :
    public boost::archive::basic_binary_oprimitive<
    prb_binary_oarchive,
    std::ostream::char_type,
    std::ostream::traits_type
    >,
    public boost::archive::detail::common_oarchive<
    prb_binary_oarchive
    > {
        typedef boost::archive::basic_binary_oprimitive<
        prb_binary_oarchive,
        std::ostream::char_type,
        std::ostream::traits_type
        > primitive_base_t;
        typedef boost::archive::detail::common_oarchive<
        prb_binary_oarchive
        > archive_base_t;
#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    public:
#else
        friend archive_base_t;
        friend primitive_base_t; // since with override save below
        friend class boost::archive::detail::interface_oarchive<
        prb_binary_oarchive
        >;
        friend class boost::archive::save_access;
    protected:
#endif
        unsigned int m_flags;
        void save_impl(const boost::intmax_t l, const char maxsize);
        // add base class to the places considered when matching
        // save function to a specific set of arguments.  Note, this didn't
        // work on my MSVC 7.0 system so we use the sure-fire method below
        // using archive_base_t::save;

        // default fall through for any types not specified here

        template<class T>
        void save(const T & t) {
            save_impl(t, sizeof (T));}

        void save(const std::string & t) {
            this->primitive_base_t::save(t);}
#ifndef BOOST_NO_STD_WSTRING

        void save(const std::wstring & t) {
            this->primitive_base_t::save(t);}
#endif

        void save(const float & t) {
            this->primitive_base_t::save(t);}

        void save(const double & t) {
            this->primitive_base_t::save(t);}

        void save(const char & t) {
            this->primitive_base_t::save(t);}

        void save(const unsigned char & t) {
            this->primitive_base_t::save(t);}
        
        void save(const datetime & t) {
            num64 tmp=num64_cast<datetime>(t);
            this->primitive_base_t::save(tmp);}
        
        void save(const num64 & t) {
            this->primitive_base_t::save(t);}
        
        void save(const unum64 & t) {
            this->primitive_base_t::save(t);}         

        
        typedef boost::archive::detail::common_oarchive<prb_binary_oarchive>
        detail_common_oarchive;

        template<class T>
        void save_override(T & t, BOOST_PFTO int) {
            this->detail_common_oarchive::save_override(t, 0);}
        // explicitly convert to char * to avoid compile ambiguities

        void save_override(const boost::archive::class_name_type & t, int) {
            const std::string s(t);
            * this << s;}
        // binary files don't include the optional information 

        void save_override(
                const boost::archive::class_id_optional_type & /* t */,
                int
                ) {}

        void init(unsigned int flags);
    public:

        prb_binary_oarchive(std::ostream & os, unsigned flags = boost::archive::no_header) :
        primitive_base_t(
        * os.rdbuf(),
        0 != (flags & boost::archive::no_codecvt)
        ),
        archive_base_t(flags),
        m_flags(flags & (endian_big | endian_little)) {
            init(flags);}

        prb_binary_oarchive(
                std::basic_streambuf<
                std::ostream::char_type,
                std::ostream::traits_type
                > & bsb,
                unsigned int flags
                ) :
        primitive_base_t(
        bsb,
        0 != (flags & boost::archive::no_codecvt)
        ),
        archive_base_t(flags),
        m_flags(0) {
            init(flags);}} ;

        //template<>
        //void prb_binary_oarchive::save<datetime>(const datetime & t);
}

namespace boost {
namespace serialization {


   using namespace dvnci;

   template<class Archive>
   void serialize(Archive& ar, datetime& g, const unsigned int version) {
        num64 tmp=num64_cast<datetime>(g);
        ar & tmp;}}}

// required by export in boost version > 1.34
#ifdef BOOST_SERIALIZATION_REGISTER_ARCHIVE
BOOST_SERIALIZATION_REGISTER_ARCHIVE(dvnci::prb_binary_iarchive)
#endif

// required by export in boost <= 1.34
#define BOOST_ARCHIVE_CUSTOM_IARCHIVE_TYPES dvnci::prb_binary_iarchive

#if defined(_MSC_VER)
#pragma warning( pop )
#endif


// required by export in boost version > 1.34
#ifdef BOOST_SERIALIZATION_REGISTER_ARCHIVE
BOOST_SERIALIZATION_REGISTER_ARCHIVE(dvnci::prb_binary_oarchive)
#endif

// required by export in boost <= 1.34
#define BOOST_ARCHIVE_CUSTOM_OARCHIVE_TYPES dvnci::prb_binary_oarchive





#endif // PORTABLE_BINARY_ARCHIVE_HPP
