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
#include "elib/basic_log.h"
#include "elib/fmt.h"

#include <ostream>
#include <cstdarg>


#define _FMT_ARGS()  \
    va_list __args; \
    va_start(__args, msg); \
    std::string __str = fmt(msg, __args); \
    va_end(__args)
    
    
#define LOG_FUNC_HANDLER(level) _FMT_ARGS(); \
    _log(level, __str)

    
namespace elib {
    


basic_log::basic_log(level_e l)
    : m_level(l)
{ }
    

const std::string &
basic_log::prompt(level_e l) const
{
     /* throw if getting non-basic level */
    if (! is_basic_level(l))
        throw std::logic_error("not a valid basic level");
    
    lock_guard lock(m_lock);
    return m_prompts.at(l);
}

void 
basic_log::prompt(level_e l, const std::string &prompt)
{
    if (! is_basic_level(l))
        throw std::logic_error("not a valid basic level");
    
    lock_guard lock(m_lock);
    m_prompts[l] = prompt;
}

void 
basic_log::level(level_e l)
{
    if (! is_basic_level(l))
        throw std::logic_error("not a valid basic level");
    
    lock_guard lock(m_lock);
    m_level = l;
}

level_e 
basic_log::level()
{
    return m_level;
}

void 
basic_log::print(level_e level, const char *msg, ... ) 
{
    LOG_FUNC_HANDLER(level);
}

void 
basic_log::print(level_e level, const std::string &msg)
{
    _log(level, msg);
}
    
void 
basic_log::debug(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::debug);
}

void 
basic_log::debug(const std::string & s)
{
    _log(level_e::debug, s);
}

void 
basic_log::info(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::info);
}

void 
basic_log::info(const std::string & s)
{
    _log(level_e::info, s);
}

void 
basic_log::step(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::step);
}

void 
basic_log::step(const std::string & s)
{
    _log(level_e::step, s);
}

void 
basic_log::warn(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::warn);
}

void 
basic_log::warn(const std::string & s)
{
    _log(level_e::warn, s);
}

void 
basic_log::err(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::err);
}

void 
basic_log::err(const std::string & s)
{
    _log(level_e::err, s);
}

void 
basic_log::fatal(const char *msg, ...)
{
    LOG_FUNC_HANDLER(level_e::fatal);
}

void 
basic_log::fatal(const std::string & s)
{
    _log(level_e::fatal, s);
}

void 
basic_log::raw_out(const char *msg, ...)
{
    LOG_FUNC_HANDLER(level_e::raw_out);
}

void 
basic_log::raw_out(const std::string &msg)
{
    _log(level_e::raw_out, msg);
}

void 
basic_log::raw_err(const char *msg, ...)
{
    LOG_FUNC_HANDLER(level_e::raw_err);
}

void
basic_log::raw_err(const std::string & msg)
{
    _log(level_e::raw_err, msg);
}

void
basic_log::on(bool p) 
{
    m_on = p;
}

bool
basic_log::on() const
{
    return m_on;
}

void 
basic_log::_log(level_e l, const std::string & msg) 
{
    if (! _should_print(l))
        return;

    lock_guard lock(m_lock);
    
    std::ostream & out = _get_stream(l);
    if (! out.good())
        return;
    
    out << m_prompts[l] << msg << std::endl;
}

bool 
basic_log::_should_print(level_e l) const 
{
    return (m_on && 
            (is_raw_level(l) || 
            (is_basic_level(l) && m_level <= l)));
}

bool 
basic_log::is_raw_level(level_e l)
{
    return (l == level_e::raw_out || l == level_e::raw_err);
}

bool 
basic_log::is_basic_level(level_e l)
{
    return (l >= level_e::debug && l <= level_e::fatal);
}


std::mutex & 
basic_log::_lock() const
{
    return m_lock;
}

    
} /* namespace elib */