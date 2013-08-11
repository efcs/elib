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
#ifndef ELIB_ARGP_ARG_OPTION_H
#define ELIB_ARGP_ARG_OPTION_H

#include "arg_token.h"

#include <string>
#include <functional>

namespace elib {
namespace argp {
    
typedef std::function<void(const arg_token&)> option_callback;
 
class basic_option {
public:
    basic_option(const std::string & cmd_desc,
                 const std::string & desc,
                  option_callback callback);
    
    virtual ~basic_option();
    
    const std::string & command_description() const;
    const std::string & description() const;
    
    std::string fmt_description() const;
    
    void notify(const arg_token &tk) const;
private:
     std::string m_cmd_desc, m_desc;
     option_callback m_callback;
};


class positional_option : public basic_option {
public:
    positional_option(const std::string & cmd_desc,
                      const std::string & desc,
                       option_callback callback);
};


class arg_option : public basic_option {
public:
    arg_option(const std::string & name,
               const std::string & cmd_desc,
               const std::string & desc,
                option_callback callback);
    
    bool has_short_name() const;
    bool has_long_name() const;
    
    const std::string & short_name() const;
    const std::string & long_name() const;
    
    bool match(const std::string & name) const;
    bool match(const std::string & name, std::string & dest) const;
    
    bool match(const arg_option & opt) const;
    bool match(const arg_option & opt, std::string & dest) const;
private:
    void parse_name_and_set(const std::string & s);
    void handle_name_part(std::string s);
private:
    std::string m_short_name, m_long_name;
};

bool prefix_is_long_name(const std::string & s);
bool prefix_is_short_name(const std::string & s);

bool is_valid_arg_name(const std::string &s);
bool is_valid_short_name(const std::string & s);
bool is_valid_long_name(const std::string & s);
  

} /* namespace argp */
} /* namespace elib */
#endif /* ELIB_ARGP_ARG_OPTION_H */