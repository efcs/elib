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
#ifndef ELIB_ARGP_ARG_PARSER_H
#define ELIB_ARGP_ARG_PARSER_H

#include "arg_option.h"
#include "arg_token.h"
#include "arg_errors.h"

#include <string>
#include <vector>
#include <memory>
#include <sstream>

UNIT_TEST_FRIEND_DECL(argp, arg_parser);

namespace elib {
namespace argp {

class arg_parser {
public:
    arg_parser(const std::string & program_name);
        
    std::string description() const;
    
    void add_option(const positional_option & opt);
    
    bool try_add_option(const arg_option &opt);
    void add_option(const arg_option & opt);
    
    void add_options(const std::vector<arg_option> &opts);
    
    bool contains_option(const std::string &s) const;
    bool contains_option(const arg_option & opt) const;
    
    void run(unsigned argc, const char* argv[]); 
    void run(const std::vector<std::string> & args);
    
    const std::vector<arg_token> & token_list() const;
    
    std::string invocation() const;
    std::vector<arg_token> collect_unrecognized() const;
    std::vector<arg_token> collect_positional() const;

private:
    arg_token create_and_match(const std::string &tk, unsigned pos);
    arg_token create_and_match_positional(const std::string &tk, unsigned pos);
    arg_token create_and_match_arg(const std::string &tk, unsigned pos);
    
    void infer_token_split(const std::string & s,
                           std::string & name,
                           std::string & value) const;
                               
    void infer_short_name_split(const std::string & tk,
                                std::string & name_dest,
                                std::string & value_dest) const;
                               
    void infer_long_name_split(const std::string & tk,
                               std::string & name,
                               std::string & value) const;
                               
    void format_command(std::stringstream & ss) const;
    void format_description(std::stringstream & ss) const;
    
    void format_description(std::stringstream & ss,
                            const std::string & cmd_desc,
                            const std::string & desc) const;
                            
private:
    std::string m_program_name;
    std::shared_ptr<positional_option> m_pos_option;
    std::vector<arg_option> m_options;
    std::vector<arg_token> m_tokens;
    DISALLOW_COPY_AND_ASSIGN(arg_parser);

};




} /* namespace argp */
} /* namespace elib */
#endif /* ELIB_ARGP_ARG_PARSER_H */