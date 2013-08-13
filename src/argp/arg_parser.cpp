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
#include "elib/argp/arg_parser.h"

#include <cctype>
#include <sstream>
#include <algorithm>

namespace elib {
namespace argp {
    
 
////////////////////////////////////////////////////////////////////////////////
//                            arg_parser                                      //
////////////////////////////////////////////////////////////////////////////////


arg_parser::arg_parser(const std::string & program_name)
    : m_program_name(program_name)
{
}

std::string
arg_parser::description() const
{
    std::stringstream ss;
    
    ss << m_program_name << ":\n";
    ss << "Invocation: " << "\n";
    this->format_command(ss);
    ss << "\n";
    ss << "Description:" << "\n";
    this->format_description(ss);
    return ss.str();
}

void
arg_parser::format_command(std::stringstream & ss) const
{
    unsigned col_count = 0;
    const unsigned col_max = 80;
    std::string indent = "  ";
    
    std::string offset;
    for (unsigned i=0; i <= m_program_name.size(); ++i)
        offset += " ";
    
    
    ss << indent << m_program_name << " ";
    col_count += indent.size() + m_program_name.size() + 1;
    
    for (auto & o : m_options) {
        if (o->command_description().size() + col_count >= col_max) {
            ss << "\n" << indent << offset;
            col_count = indent.size() + offset.size();
        }
        ss << o->command_description() << " ";
        col_count += o->command_description().size() + 1;
    }
    
    if (m_pos_option) {
        if (m_pos_option->command_description().size() + col_count >= col_max) {
            ss << "\n" << indent << offset;
            col_count = indent.size() + offset.size();
        }
        ss << m_pos_option->command_description();
    }
    
    ss << "\n";
}

void
arg_parser::format_description(std::stringstream & ss) const
{
    if (m_pos_option) {
        format_description(ss, 
            m_pos_option->command_description(),
            m_pos_option->description());
    }
    
    for (auto & o : m_options)
        format_description(ss, o->command_description(), o->description());
}

void
arg_parser::format_description(std::stringstream & ss,
                               const std::string & cmd_desc,
                               const std::string & desc) const
{
    std::string indent = "    ";
    std::vector<std::string> token_list;
    
    int word_start, word_len;
    word_start = word_len = 0;
    
    for (unsigned i=0; i < desc.size(); ++i) {
        if (desc[i] == ' ') {
            if (word_len != 0) {
                token_list.push_back(desc.substr(word_start, word_len));
                word_start = 0;
                word_len = 0;
            }
        } else {
            if (word_len == 0)
                word_start = i;
            word_len++;
        }
    }
    
    if (word_len != 0)
        token_list.push_back(desc.substr(word_start, word_len));
    
    ss << "\n" << indent << cmd_desc << "\n";
    
    ss << indent << indent << indent;
    int col_count = indent.size() * 3;
    
    for (auto & s : token_list) {
        if (s == "\n" || col_count + s.size() >= 80) {
            col_count = 3 * indent.size();
            ss << "\n" << indent << indent << indent;
        }
        
        if (s != "\n" && s != "\t") {
            ss << s << " ";
            col_count += s.size() + 1;
        }
        else if (s == "\t") {
            ss << indent;
            col_count += indent.size();
        }
    }
    
    ss << "\n";
}





bool
arg_parser::contains_option(const std::string &s) const
{
    for (auto &opt : m_options) {
        if (opt->match(s))
            return true;
    }
    
    return false;
}

bool
arg_parser::contains_option(const arg_option &o) const
{
    for (auto & opt : m_options) {
        if (opt->match(o))
            return true;
    }
    
    return false;
}
    
void 
arg_parser::run(unsigned argc, const char* argv[])
{
    std::vector<std::string> tmp_args;
    
    for (unsigned i=0; i < argc; ++i)
        tmp_args.push_back(std::string(argv[i]));
    
    run(tmp_args);
}

void 
arg_parser::run(const std::vector<std::string> & args)
{
    unsigned pos = 0;
    for (auto &s : args) {
        if (pos == 0) {
            arg_token tk(pos++, s, "", "");
            tk.matched(true);
            m_tokens.push_back(tk);
        } else {
            auto tk = create_and_match(s, pos++);
            m_tokens.push_back(tk);
        }
    }
}
    
const std::vector<arg_token> & 
arg_parser::token_list() const
{
    return m_tokens;
}

std::string
arg_parser::invocation() const
{
    if (m_tokens.size() == 0)
        return "";
    return m_tokens[0].raw_arg(); 
}
    
std::vector<arg_token> 
arg_parser::collect_unrecognized() const
{
    std::vector<arg_token> unrec;
    
    for (auto &tk : m_tokens) {
        if (! tk.matched())
            unrec.push_back(tk);
    }
    
    return unrec;
}

std::vector<arg_token> 
arg_parser::collect_positional() const
{
    std::vector<arg_token> pos_args;
    
    for (auto &tk : m_tokens) {
        if (tk.positional())
            pos_args.push_back(tk);
    }
    
    return pos_args;
}



arg_token
arg_parser::create_and_match(const std::string &tk, unsigned pos)
{
    assert(tk.size() > 0);
    
    if (tk[0] != '-')
        return create_and_match_positional(tk, pos);
    else
        return create_and_match_arg(tk, pos);
}

arg_token
arg_parser::create_and_match_positional(const std::string &tk, unsigned pos)
{
    arg_token arg_tk(pos, tk, "", tk);
    if (m_pos_option) {
        m_pos_option->notify(arg_tk);
        arg_tk.matched(true);
    }
    
    return arg_tk;
}

arg_token
arg_parser::create_and_match_arg(const std::string &tk, unsigned pos)
{
    std::string name, value;
    std::shared_ptr<arg_option> opt = nullptr;
   
    infer_token_split(tk, name, value);
    
    assert(name.size() >= 2);
    
    for (auto &option : m_options) {
        if (option->match(name)) {
            opt = option;
            break;
        }
    }
    
    arg_token arg_tk(pos, tk, name, value);
    
    if (opt != nullptr) {
        opt->notify(arg_tk);
        arg_tk.matched(true);
    }
    
    return arg_tk;
}

void
arg_parser::infer_token_split(const std::string &tk,
                              std::string & name,
                              std::string & value) const
{
    if (prefix_is_long_name(tk)) {
        infer_long_name_split(tk, name, value);
        return;
    }
   
    if (prefix_is_short_name(tk)) {
        infer_short_name_split(tk, name, value);
        return;
    }
    
    throw invalid_arg_error(tk);
}

void
arg_parser::infer_short_name_split(const std::string &tk, 
                                   std::string &name, 
                                   std::string &value) const
{
    if (tk.size() < 2 || ! isalpha(tk[1]))
        throw invalid_arg_error(tk);
    
    name = tk.substr(0, 2);
    value = tk.substr(2);
}


void
arg_parser::infer_long_name_split(const std::string &tk,
                                  std::string &name,
                                  std::string &value) const
{
    assert(prefix_is_long_name(tk));
    
    unsigned name_len = 3;
    
    while(name_len < tk.size()) {
        char c = tk[name_len];
        if (isalpha(c)) {
            ++name_len;
        }
        else if (c == '-') {
            if (name_len + 1 == tk.size() || ! isalpha(tk[name_len+1]))
                throw invalid_arg_error(tk);
            ++name_len;
        }
        else if (isalpha(c)) {
            ++name_len;
        }
        else if (c == '=') {
            break;
        }
        else {
            throw invalid_arg_error(tk);
        }
    }
    
    name = tk.substr(0, name_len);
    if (name_len != tk.size()) {
        if (tk[name_len] == '=')
            value = tk.substr(name_len+1);
    }
}


} /* namespace argp  */
} /* namespace elib */
