/* 
 * File:   dtype_traits.h
 * Author: Alexeev
 *
 * Created on 28 Апрель 2011 г., 12:01
 */

#ifndef DTYPE_TRAITS_H
#define	DTYPE_TRAITS_H

#include "constdef.h"


namespace dvnci {

    template <tagtype tgtype>
    class dvnci_type_traits{
    public:
        typedef   double                            basistype;
        typedef   std::numeric_limits<basistype>    stdnumlimits;
        static const bool       isnumeric = true;
        static const bool       isinteger = false;
        static const size_t     size = sizeof(basistype);};

    template <>
    class dvnci_type_traits<TYPE_NODEF>{
    public:
        typedef   double                            basistype;
        typedef   std::numeric_limits<basistype>    stdnumlimits;
        static const bool       isnumeric = true;
        static const bool       isinteger = false;
        static const size_t     size = sizeof(basistype);};

    template <>
    class dvnci_type_traits<TYPE_DOUBLE>{
    public:
        typedef   double                            basistype;
        typedef   std::numeric_limits<basistype>    stdnumlimits;
        static const bool       isnumeric = true;
        static const bool       isinteger = false;
        static const size_t     size = sizeof(basistype);};

    template <>
    class dvnci_type_traits<TYPE_FLOAT>{
    public:
        typedef   float                             basistype;
        typedef   std::numeric_limits<basistype>    stdnumlimits;
        static const bool       isnumeric = true;
        static const bool       isinteger = false;
        static const size_t     size = sizeof(basistype);};

    template <>
    class dvnci_type_traits<TYPE_NUM64>{
    public:
        typedef   num64                             basistype;
        typedef   std::numeric_limits<basistype>    stdnumlimits;
        static const bool       isnumeric = true;
        static const bool       isinteger = true;
        static const size_t     size = sizeof(basistype);};     


}



#endif	/* DTYPE_TRAITS_H */

