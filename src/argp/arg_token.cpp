/* 
 * Copyright (C) 2013  Eric Fiselier
 * 
 * This file is part of elib.
 *
 * elib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * elib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elib.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "elib/argp/arg_token.hpp"

namespace elib {
namespace argp {
    
////////////////////////////////////////////////////////////////////////////////
//                              arg_token                                     //
///////////////////////////////////////////////////////////////////////////////
    
arg_token::arg_token(unsigned pos, 
                     const std::string& xraw_arg,
                     const std::string xname,
                     const std::string xvalue,
                     bool xhas_assign)
    : m_pos{pos}
    , m_raw{xraw_arg}
    , m_name{xname}
    , m_value{xvalue}
    , m_assign{xhas_assign}
{
} 

unsigned
arg_token::position() const
{
    return m_pos;
}

const std::string &
arg_token::raw_arg() const
{
    return m_raw;
}

const std::string &
arg_token::name() const
{
    return m_name;
}

const std::string &
arg_token::value() const
{
    return m_value;
}


bool
arg_token::positional() const
{
    return (! has_name() && has_value());
}

bool
arg_token::invocation() const
{
    return (! has_name() && ! has_value());
}

bool
arg_token::has_name() const
{
    return (m_name != "");
}

bool
arg_token::has_value() const
{
    return (m_value != "");
}

bool
arg_token::has_assign() const
{
    return m_assign;
}


bool
arg_token::matched() const
{
    return m_matched;
}

void
arg_token::matched(bool n_val)
{
    m_matched = n_val;
}

} /* namespace argp */
} /* namespace elib */