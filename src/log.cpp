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
#include "elib/log.h"

#include "impl/log_impl.h"

#include <sstream>
#include <cstdarg>

#define BUFF_MAX 1024

#define _FMT_ARGS() char __fmt_buff[BUFF_MAX]; \
	va_list __args; \
	va_start(__args, msg); \
	vsnprintf(__fmt_buff, BUFF_MAX, msg, __args); \
	va_end(__args)
	
	
#define LOG_FUNC_HANDLER(level) _FMT_ARGS(); \
	m_impl->log(level, __fmt_buff) 

	
namespace elib {
    

basic_enum_traits<level_e>::map_type basic_enum_traits<level_e>::name_map =
    { {level_e::debug, "debug"},
      {level_e::info, "info"},
      {level_e::step, "step"},
      {level_e::warn, "warn"},
      {level_e::err, "err"},
      {level_e::fatal, "fatal"},
      {level_e::raw_out, "raw_out"},
      {level_e::raw_err, "raw_err"}
    };
    
    
	
log::log()
    : m_impl(new detail::log_impl)
{
}

const std::string &
log::prompt(level_e level) const
{
	return m_impl->prompt(level);
}

void 
log::prompt(level_e level, const std::string &prompt)
{
	m_impl->prompt(level, prompt);
}

void 
log::level(level_e level)
{
	m_impl->level(level);
}

level_e 
log::level()
{
	return m_impl->level();
}

void 
log::print(level_e level, const char *msg, ... ) 
{
	LOG_FUNC_HANDLER(level);
}

void 
log::print(level_e level, const std::string &msg)
{
	m_impl->log(level, msg.c_str());
}
	
void 
log::debug(const char *msg, ... )
{
	LOG_FUNC_HANDLER(level_e::debug);
}

void 
log::debug(const std::string & s)
{
    m_impl->log(level_e::debug, s.c_str());
}

void 
log::info(const char *msg, ... )
{
	LOG_FUNC_HANDLER(level_e::info);
}

void 
log::info(const std::string & s)
{
    m_impl->log(level_e::info, s.c_str());
}

void 
log::step(const char *msg, ... )
{
	LOG_FUNC_HANDLER(level_e::step);
}

void 
log::step(const std::string & s)
{
    m_impl->log(level_e::step, s.c_str());
}

void 
log::warn(const char *msg, ... )
{
	LOG_FUNC_HANDLER(level_e::warn);
}

void 
log::warn(const std::string & s)
{
    m_impl->log(level_e::warn, s.c_str());
}

void 
log::err(const char *msg, ... )
{
	LOG_FUNC_HANDLER(level_e::err);
}

void 
log::err(const std::string & s)
{
    m_impl->log(level_e::err, s.c_str());
}

void 
log::fatal(const char *msg, ...)
{
	LOG_FUNC_HANDLER(level_e::fatal);
}

void 
log::fatal(const std::string & s)
{
    m_impl->log(level_e::fatal, s.c_str());
}

void 
log::raw_out(const char *msg, ...)
{
	LOG_FUNC_HANDLER(level_e::raw_out);
}

void 
log::raw_out(const std::string &msg)
{
	m_impl->log(level_e::raw_out, msg.c_str());
}

void 
log::raw_err(const char *msg, ...)
{
	LOG_FUNC_HANDLER(level_e::raw_err);
}

void
log::raw_err(const std::string & msg)
{
	m_impl->log(level_e::raw_err, msg.c_str());
}

void
log::on(bool p) 
{
    m_impl->on(p);
}

bool
log::on() const
{
    return m_impl->on();
}

} /* namespace elib */
