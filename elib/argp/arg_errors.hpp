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
#ifndef ELIB_ARGP_ARG_ERRORS_HPP
#define ELIB_ARGP_ARG_ERRORS_HPP

# include <elib/config.hpp>
# include <elib/pragma.hpp>

#include <stdexcept>

namespace elib {
namespace argp {
   
ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_WEAK_VTABLES()

class option_conflict_error : public std::logic_error {
public:
    option_conflict_error()
        : std::logic_error("option conflict error") 
    { }
};

class name_conflict_error : public std::logic_error {
public:
    name_conflict_error()
        : std::logic_error("name conflict error")
        { }
        
    name_conflict_error(const std::string & what_arg)
        : std::logic_error("name conflict error: " + what_arg) 
    { }
};


class name_format_error : public std::logic_error {
public:
    name_format_error(const std::string & what_arg)
        : std::logic_error("name format error: " + what_arg) 
    { }
};

class invalid_arg_error : public std::runtime_error {
public:
    invalid_arg_error()
        : std::runtime_error("invalid argument")
    { }
    
    invalid_arg_error(const std::string& what_arg)
        : std::runtime_error("invalid argument: " + what_arg)
    { }
    
    invalid_arg_error(const std::string& what_arg, const std::string & arg)
        : std::runtime_error("invalid argument: " + what_arg + ": ( " + arg + " )")
    { }
};

ELIB_PRAGMA_DIAG_POP()

} /* namespace argp */
} /* namespace elib */
#endif /* ELIB_ARGP_ARG_ERRORS_HPP */