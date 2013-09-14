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
#ifndef ELIB_ARGP_ARG_TOKEN_HPP
#define ELIB_ARGP_ARG_TOKEN_HPP

#include <string>


namespace elib {
namespace argp {    

class arg_token {
public:
    arg_token(unsigned pos, 
              const std::string & raw_arg,
              const std::string name = "", 
              const std::string value = "",
              bool xhas_assign = false);
    
    unsigned position() const;
    
    const std::string & raw_arg() const;
    const std::string & name() const;
    const std::string & value() const;
    
    bool invocation() const;
    bool positional() const;
    bool has_name() const;
    bool has_value() const;
    bool has_assign() const;
    
    bool matched() const;
    void matched(bool);
private:
    unsigned m_pos;
    std::string m_raw, m_name, m_value;
    bool m_assign;
    bool m_matched{false};
};


} /* namespace argp */
} /* namespace elib */
#endif /* ELIB_ARGP_ARG_TOKEN_HPP */