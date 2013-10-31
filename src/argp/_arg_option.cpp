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
#include "elib/argp/arg.hpp"
#include "elib/argp/arg_errors.hpp"

#include <algorithm>
#include <sstream>
#include <iostream>
#include <cctype>

namespace elib 
{
  namespace argp 
  {
    namespace detail
    {
    
      
      arg_option::arg_option(arg_type_e xarg_type,
                    const std::string & name,
                    const std::string & cmd_desc,
                    const std::string & desc)
          : m_cmd_desc{cmd_desc}, m_desc{desc}, m_arg_type{xarg_type}
      {
          if (name != "")
              parse_name_and_set(name);
      }
      
      
      arg_option::~arg_option()
      { }


      const std::string &
      arg_option::command_description() const
      {
          return m_cmd_desc;
      }

      const std::string &
      arg_option::description() const
      {
          return m_desc;
      }

      std::string
      arg_option::fmt_description() const
      {
          std::stringstream ss;
          ss << m_cmd_desc << "    " << m_desc << std::endl;
          return ss.str();
      }


      bool 
      arg_option::has_short_name() const
      {
          return (m_short_name != "");
      }

      bool 
      arg_option::has_long_name() const
      {
          return (m_long_name != "");
      }
          
      const std::string & 
      arg_option::short_name() const
      {
          return m_short_name;
      }

      const std::string & 
      arg_option::long_name() const
      {
          return m_long_name;
      }
          
      bool 
      arg_option::match(const std::string & name) const
      {
          std::string tmp;
          return match(name, tmp);
      }

      bool 
      arg_option::match(const std::string & name, std::string & dest) const
      {
          if (prefix_is_long_name(name) && has_long_name() &&
              name == m_long_name) {
              
              dest = m_long_name;
              return true;
          }
          
          if (prefix_is_short_name(name) && has_short_name() &&
              name == m_short_name) {
              
              dest = m_short_name;
              return true;
          }
          
          return false;
      }
          
      bool 
      arg_option::match(const arg_option & opt) const
      {
          std::string tmp;
          return match(opt, tmp);
      }

      bool 
      arg_option::match(const arg_option & opt, std::string & dest) const
      {
          if (has_long_name() && opt.has_long_name() && 
              m_long_name == opt.long_name()) {
              
              dest = m_long_name;
              return true;
          }
          
          if (has_short_name() && opt.has_short_name() &&
              m_short_name == opt.short_name()) {
              
              dest = m_short_name;
              return true;
          }
          
          return false;
      }


      void 
      arg_option::parse_name_and_set(const std::string & s)
      {
          auto count = s.find(',');
          try {
              if (count == std::string::npos) {
                  handle_name_part(s);
              }
              else {
                  handle_name_part(s.substr(0, count));
                  handle_name_part(s.substr(count+1));
              }
          } catch (name_format_error&) {
              throw name_format_error(s);
          }
      }

      void
      arg_option::handle_name_part(std::string s)
      {
          if (is_valid_long_name(s)) {
              if (has_long_name())
                  throw name_format_error(s);
              m_long_name = s;
          }
          else if (is_valid_short_name(s)) {
              if (has_short_name())
                  throw name_format_error(s);
              m_short_name = s;
          }
          else {
              throw name_format_error(s);
          }
      }

    
    } /* namespace detail */
  } /* namespace argp */
} /* namespace elib */