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
#include "elib/elog.h"
#include "impl/log_impl.h"

#include <cstdarg>

#define BUFF_MAX 1024

#define _FMT_ARGS() char __fmt_buff[BUFF_MAX]; \
    va_list __args; \
    va_start(__args, msg); \
    vsnprintf(__fmt_buff, BUFF_MAX, msg, __args); \
    va_end(__args)
    
    
#define LOG_FUNC_HANDLER(level) _FMT_ARGS(); \
    elog::m_impl->log(level, __fmt_buff) 

    
namespace elib {
    
   
std::unique_ptr<detail::log_impl> 
elog::m_impl(new detail::log_impl);


const std::string &
elog::prompt(level_e level)
{
    return elog::m_impl->prompt(level);
}

void 
elog::prompt(level_e level, const std::string &prompt)
{
    elog::m_impl->prompt(level, prompt);
}

void 
elog::level(level_e level)
{
    elog::m_impl->level(level);
}

level_e 
elog::level()
{
    return elog::m_impl->level();
}

void 
elog::print(level_e level, const char *msg, ... ) 
{
    LOG_FUNC_HANDLER(level);
}

void 
elog::print(level_e level, const std::string &msg)
{
    elog::m_impl->log(level, msg.c_str());
}
    
void 
elog::debug(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::debug);
}

void 
elog::debug(const std::string & s)
{
    elog::m_impl->log(level_e::debug, s.c_str());
}

void 
elog::info(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::info);
}

void 
elog::info(const std::string & s)
{
    elog::m_impl->log(level_e::info, s.c_str());
}

void 
elog::step(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::step);
}

void 
elog::step(const std::string & s)
{
    elog::m_impl->log(level_e::step, s.c_str());
}

void 
elog::warn(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::warn);
}

void 
elog::warn(const std::string & s)
{
    elog::m_impl->log(level_e::warn, s.c_str());
}

void 
elog::err(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::err);
}

void 
elog::err(const std::string & s)
{
    elog::m_impl->log(level_e::err, s.c_str());
}

void 
elog::fatal(const char *msg, ...)
{
    LOG_FUNC_HANDLER(level_e::fatal);
}

void 
elog::fatal(const std::string & s)
{
    elog::m_impl->log(level_e::fatal, s.c_str());
}

void 
elog::raw_out(const char *msg, ...)
{
    LOG_FUNC_HANDLER(level_e::raw_out);
}

void 
elog::raw_out(const std::string &msg)
{
    elog::m_impl->log(level_e::raw_out, msg.c_str());
}

void 
elog::raw_err(const char *msg, ...)
{
    LOG_FUNC_HANDLER(level_e::raw_err);
}

void
elog::raw_err(const std::string & msg)
{
    elog::m_impl->log(level_e::raw_err, msg.c_str());
}

void
elog::on(bool p) 
{
    elog::m_impl->on(p);
}

bool
elog::on()
{
    return elog::m_impl->on();
}
    
} /* namespace elib */