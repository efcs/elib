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
#ifndef ELIB_LOG_IMPL_H
#define ELIB_LOG_IMPL_H

#include "elib/log.h"

#include <stdexcept>
#include <iostream>
#include <mutex>
#include <map>

#define PRINT_BUFF_MAX 1024


namespace elib {
    
namespace unit_test { class test_basic_log_impl; }
    
namespace detail {
    

class basic_log_impl
{
public:	
    /* get & set the prompts as described in basic_log */
	const std::string & prompt(level_e l) const;
	void prompt(level_e l, const std::string & p);
	
    /* get & set the level as described in basic_log */
	void level(level_e l);
	level_e level() const;
	
    /* log a (already formatted) message to a given log level */
	void log(level_e l, const char *msg);
    
    /* same as in basic_log */
	void on(bool b);
    bool on() const;
    
    /* check properties about a member of level_e 
     * raw_levels: raw_out, raw_err
     * basic_levels: debug-fatal */
    static bool is_raw_level(level_e e);
    static bool is_basic_level(level_e e);    
    
protected:
    
    typedef std::lock_guard<std::mutex> lock_guard;
    
    /* return the stream that should be written to for a given
     * level, the stream is assumed to be good */
	virtual std::ostream & 
	_get_stream(level_e l) = 0;
	
    /* return true if we should log the message,
     * to log a message we must be:
     *   a) on.
     *   b) a raw level or a basic level >= current level */ 
	bool 
	_should_print(level_e l) const;
    
    /* return the lock object, so derived methods can be thread-safe */
    std::mutex & 
    _lock() const;
    
private:
    /* the current logging level */
	level_e m_level = default_log_level;
    
    /* on/off switch for ALL logging */
    bool m_on = true;
    
    /* prompt maps: level -> prompt */
	std::map<level_e, std::string> m_prompts = 
        {
          {level_e::debug, "Debug: "}, 
          {level_e::info, "Info: "},
          {level_e::step, "--> "},
          {level_e::warn, "Warning: "},
          {level_e::err, "ERROR: "},
          {level_e::fatal, "FATAL: "},
          {level_e::raw_out, ""},
          {level_e::raw_err, ""} 
        };
                            
    /* use the mutex to be thread-safe */
    mutable std::mutex m_lock;
    friend unit_test::test_basic_log_impl;
};


inline const std::string &
basic_log_impl::prompt(level_e l) const 
{
    /* throw if getting non-basic level */
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


inline std::mutex & 
basic_log_impl::_lock() const
{
    return m_lock;
}

////////////////////////////////////////////////////////////////////////////////
//                          log_impl                                                                          
////////////////////////////////////////////////////////////////////////////////

/* log_impl implements _get_stream so that seperate 
 * out & err streams can be kept (unlike file_log) */
class log_impl : public basic_log_impl {
public:
    log_impl();
    
protected:
    /* return m_out for debug-step and m_err for warn-fatal */
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


} /* namespace detail */
} /* namespace elib */
#endif /* ELIB_LOG_IMPL_H */