/* Copyright (C) 2013  Eric Fiselier
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
#ifndef ELIB__LOG_H
#define ELIB__LOG_H

#include "elib/log.h"

#include <iostream>
#include <mutex>
#include <map>
#include <stdexcept>


namespace elib {
	
    
using lock_guard = std::lock_guard<std::mutex>;


class basic_log_impl
{
public:
    static bool is_raw_level(level_e e);
    static bool is_basic_level(level_e e);
    static bool is_valid_level(level_e e);
public: 
    const std::string & prompt(level_e l) const;
    void prompt(level_e l, const std::string & p);
    
    void level(level_e l);
    level_e level() const;
    
    void log(level_e l, const char *msg);
    
    void on(bool b);
    bool on() const;
protected:
    virtual std::ostream & 
    _get_stream(level_e l) = 0;
    
    bool 
    _should_print(level_e l) const;
    
    std::mutex & 
    _lock() const;
private:
    level_e m_level = basic_log::default_level;
    bool m_on = true;

    std::map<level_e, std::string> m_prompts = {
                                {level_e::debug, "Debug: "},
                                {level_e::info, "Info: "},
                                {level_e::step, "--> "},
                                {level_e::warn, "Warning: "},
                                {level_e::err, "ERROR: "},
                                {level_e::fatal, "FATAL: "},
                                {level_e::raw_out, ""},
                                {level_e::raw_err, ""} };
                                
    mutable std::mutex m_lock;

};




inline const std::string &
basic_log_impl::prompt(level_e l) const 
{
    if (! is_basic_level(l))
        throw std::logic_error("not a valid basic level");
    
    lock_guard lock(m_lock);
    return m_prompts.at(l);
}

inline void
basic_log_impl::prompt(level_e l, const std::string &prompt) 
{
    if (! is_basic_level(l))
        throw std::logic_error("not a valid basic level");
    
    lock_guard lock(m_lock);
    m_prompts[l] = prompt;
}

inline void 
basic_log_impl::basic_log_impl::level(level_e l) 
{
    if (! is_basic_level(l))
        throw std::logic_error("not a valid basic level");
    
    lock_guard lock(m_lock);
    m_level = l;
}

inline level_e 
basic_log_impl::level() const 
{
    return m_level;
}

inline void 
basic_log_impl::log(level_e l, const char *msg) 
{
    if (! is_valid_level(l))
        throw std::logic_error("not a valid level");
    
    if (! _should_print(l))
        return;

    lock_guard lock(m_lock);
    
    std::ostream & out = _get_stream(l);
    if (! out.good())
        return;
    
    out << m_prompts[l] << msg << std::endl;
}

inline void 
basic_log_impl::on(bool p) 
{
    m_on = p;
}

inline bool
basic_log_impl::on() const
{
    return m_on;
}

inline bool 
basic_log_impl::_should_print(level_e l) const 
{
    return (m_on && 
            (is_raw_level(l) || 
            (is_basic_level(l) && m_level <= l)));
}

inline bool 
basic_log_impl::is_raw_level(level_e l)
{
    return (l == level_e::raw_out || l == level_e::raw_err);
}

inline bool 
basic_log_impl::is_basic_level(level_e l)
{
    return (l >= level_e::debug && l <= level_e::fatal);
}

inline bool 
basic_log_impl::is_valid_level(level_e l) 
{ 
    return (is_raw_level(l) || is_basic_level(l));
}

inline std::mutex & 
basic_log_impl::_lock() const
{
    return m_lock;
}

////////////////////////////////////////////////////////////////////////////////
//                          log_impl                                                                          
////////////////////////////////////////////////////////////////////////////////

class log_impl : public basic_log_impl {
public:
    log_impl();
    
protected:
    std::ostream & 
    _get_stream(level_e e);
    
private:
    std::ostream &m_out, &m_err;
    DISALLOW_COPY_AND_ASSIGN(log_impl);
};

inline 
log_impl::log_impl()
    : m_out(std::cout), m_err(std::cerr)
{
}

inline std::ostream &
log_impl::_get_stream(level_e e)
{
    if (e == level_e::raw_out ||  e <= level_e::step) 
        return m_out;
     else 
        return m_err;
}



} /* namespace elib */
#endif /* ELIB__LOG_H */