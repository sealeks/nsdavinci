/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// prb_binary_iarchive.cpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <istream>
#include <ostream>
#include <string>

#include <boost/detail/endian.hpp>
#include <boost/serialization/throw_exception.hpp>
#include <boost/archive/archive_exception.hpp>

#include <kernel/prb_binary_archive.h>

namespace dvnci {

    void
    prb_binary_iarchive::load_impl(boost::intmax_t & l, char maxsize) {
        char size;
        l = 0;
        this->primitive_base_t::load(size);

        if (0 == size) {
            return;}

        bool negative = (size < 0);
        if (negative)
            size = -size;

        if (size > maxsize)
            boost::serialization::throw_exception(
                prb_binary_iarchive_exception()
                );

        char * cptr = reinterpret_cast<char *> (& l);
#ifdef BOOST_BIG_ENDIAN
        cptr += (sizeof (boost::intmax_t) - size);
#endif
        this->primitive_base_t::load_binary(cptr, size);

#ifdef BOOST_BIG_ENDIAN
        if (m_flags & endian_little)
#else
        if (m_flags & endian_big)
#endif
            reverse_bytes(size, cptr);

        if (negative)
            l = -l;}

    void
    prb_binary_iarchive::load_override(
            boost::archive::class_name_type & t, int
            ) {
        std::string cn;
        cn.reserve(BOOST_SERIALIZATION_MAX_KEY_SIZE);
        load_override(cn, 0);
        if (cn.size() > (BOOST_SERIALIZATION_MAX_KEY_SIZE - 1))
            boost::serialization::throw_exception(
                boost::archive::archive_exception(
                boost::archive::archive_exception::invalid_class_name)
                );
        std::memcpy(t, cn.data(), cn.size());
        // borland tweak
        t.t[cn.size()] = '\0';}

    void
    prb_binary_iarchive::init(unsigned int flags) {
        unsigned char x;
        load(x);
        m_flags = x << CHAR_BIT;}

    void
    prb_binary_oarchive::save_impl(
            const boost::intmax_t l,
            const char maxsize
            ) {
        char size = 0;

        if (l == 0) {
            this->primitive_base_t::save(size);
            return;}

        boost::intmax_t ll;
        bool negative = (l < 0);
        if (negative)
            ll = -l;
        else
            ll = l;

        do {
            ll >>= CHAR_BIT;
            ++size;}
        while (ll != 0);

        this->primitive_base_t::save(
                static_cast<char> (negative ? -size : size)
                );

        if (negative)
            ll = -l;
        else
            ll = l;
        char * cptr = reinterpret_cast<char *> (& ll);
#ifdef BOOST_BIG_ENDIAN
        cptr += (sizeof (boost::intmax_t) - size);
        if (m_flags & endian_little)
            reverse_bytes(size, cptr);
#else
        if (m_flags & endian_big)
            reverse_bytes(size, cptr);
#endif
        this->primitive_base_t::save_binary(cptr, size);}

    void
    prb_binary_oarchive::init(unsigned int flags) {
        if (m_flags == (endian_big | endian_little)) {
            boost::serialization::throw_exception(
                    prb_binary_oarchive_exception()
                    );}
        save(static_cast<unsigned char> (m_flags >> CHAR_BIT));}}


#include <boost/archive/impl/archive_serializer_map.ipp>
#include <boost/archive/impl/basic_binary_iprimitive.ipp>
#include <boost/archive/impl/basic_binary_oprimitive.ipp>

namespace boost {
    namespace archive {

        using namespace dvnci;

        namespace detail {

            using namespace dvnci;

            template class archive_serializer_map<prb_binary_iarchive>;
            template class archive_serializer_map<prb_binary_oarchive>;}

        template class basic_binary_iprimitive<
        prb_binary_iarchive,
        std::istream::char_type,
        std::istream::traits_type
        > ;




        template class basic_binary_oprimitive<
        prb_binary_oarchive,
        std::ostream::char_type,
        std::ostream::traits_type
        > ;}}





