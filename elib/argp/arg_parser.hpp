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
#ifndef ELIB_ARGP_ARG_PARSER_HPP
#define ELIB_ARGP_ARG_PARSER_HPP


#include "arg_token.hpp"
#include "arg_errors.hpp"
#include "arg.hpp"

#include <string>
#include <vector>
#include <memory>
#include <sstream>

namespace elib {
namespace argp {

class arg_parser {
public:
    typedef std::shared_ptr<detail::arg_option> sptr_type;
    
    arg_parser(const std::string & program_name);
        
    std::string description() const;
    
    template <typename T>
    bool try_add_option(const basic_arg<T> & opt);
    
    template <typename T>
    void add_option(const basic_arg<T> & opt);
    
    
    bool contains_option(const std::string &s) const;
    bool contains_option(const detail::arg_option & opt) const;
    
    void run(unsigned argc, const char* argv[]); 
    void run(const std::vector<std::string> & args);
    
    const std::vector<arg_token> & 
    token_list() const;
    
    std::string invocation() const;
    std::vector<arg_token> collect_unrecognized() const;
    std::vector<arg_token> collect_positional() const;

private:
    arg_token create_and_match(const std::string &tk, unsigned pos);
    arg_token create_and_match_positional(const std::string &tk, unsigned pos);
    arg_token create_and_match_arg(const std::string &tk, unsigned pos);
    
    /* throw invalid arg err on failure */
    void check_token_semantics(const detail::arg_option & opt,
                               const arg_token & tk) const;
    
    void infer_token_split(const std::string & s,
                           std::string & name,
                           std::string & value,
                           bool & has_assign) const;
                        
                               
    void infer_short_name_split(const std::string & tk,
                                std::string & name_dest,
                                std::string & value_dest) const;
                               
    void infer_long_name_split(const std::string & tk,
                               std::string & name,
                               std::string & value,
                               bool & has_assign) const;
                               
    void format_command(std::stringstream & ss) const;
    void format_description(std::stringstream & ss) const;
    
    void format_description(std::stringstream & ss,
                            const std::string & cmd_desc,
                            const std::string & desc) const;
        
    
private:
    std::string m_program_name;
    sptr_type m_pos_option;
    std::vector<sptr_type> m_options;
    std::vector<arg_token> m_tokens;
private:
    /* DISALLOW COPY AND ASSIGN */
    arg_parser(const arg_parser&);
    arg_parser& operator=(const arg_parser&);
};



template <typename T>
bool 
arg_parser::try_add_option(const basic_arg<T> & opt)
{
    if (opt.arg_type() == arg_type_e::positional) {
        if (m_pos_option)
            return false;
        auto sptr = std::make_shared<basic_arg<T>>(opt);
        m_pos_option = std::static_pointer_cast<detail::arg_option>(sptr);
        return true;
    }
    
    if (contains_option(opt))
        return false;
    
    auto sptr = std::make_shared<basic_arg<T>>(opt);
    auto base_ptr = std::static_pointer_cast<detail::arg_option>(sptr);
    m_options.push_back(base_ptr);
    return true;
}

template <typename T>
void 
arg_parser::add_option(const basic_arg<T> & opt)
{
    if (! try_add_option(opt))
        throw name_conflict_error();
}


} /* namespace argp */
} /* namespace elib */
#endif /* ELIB_ARGP_ARG_PARSER_HPP */