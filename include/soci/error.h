//
// Copyright (C) 2004-2008 Maciej Sobczak
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef SOCI_ERROR_H_INCLUDED
#define SOCI_ERROR_H_INCLUDED

#include "soci-config.h"

#include <stdexcept>
#include <string>

namespace soci
{

class SOCI_DECL soci_error : public std::runtime_error
{
public:
    explicit soci_error(std::string const & msg);
    soci_error(int errcod, std::string const & msg);
    int code() const{ return err_;}
private:
    int err_;
};

} // namespace soci

#endif // SOCI_ERROR_H_INCLUDED
