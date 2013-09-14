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
#ifndef ELIB_LOG_STATIC_LOG_H
#define ELIB_LOG_STATIC_LOG_H

#include <elib/log/log_level.hpp>
#include <elib/log/log.hpp>
#include <elib/utility/fmt.hpp>

#include <cstdarg>
#include <string>


namespace elib {
namespace log {

      
/* global logging class, it logs to std::cout and std::cerr,
 * while it does not inherit from basic_log it implements
 * the basic_log interface except the methods are static */
template <typename Tag>
class static_log { 
private:
    /* only a single instance of static_log is allowed */
    static_log();
    static log m_impl;
public:
    
    static const std::string & 
    prompt(level_e l);
    
    static void 
    prompt(level_e l, const std::string &prompt);
    
    static void 
    level(level_e l);
    
    static level_e 
    level();
    
    static void 
    print(level_e l, const char *msg, ... );
    
    static void 
    print(level_e l, const std::string &msg);
    
    static void 
    debug(const char *msg, ... );
    
    static void 
    debug(const std::string & s);
    
    static void 
    info(const char *msg, ... );
    
    static void 
    info(const std::string & s);
    
    static void 
    step(const char *msg, ... );
    
    static void 
    step(const std::string & s);
    
    static void 
    warn(const char *msg, ... );
    
    static void 
    warn(const std::string & s);
    
    static void 
    err(const char *msg, ... );
    
    static void 
    err(const std::string & s);
    
    static void 
    fatal(const char *msg, ...);
    
    static void 
    fatal(const std::string & s);
    
    static void 
    raw_out(const char *msg, ...);
    
    static void 
    raw_out(const std::string & s);
    
    static void 
    raw_err(const char *msg, ...);
    
    static void 
    raw_err(const std::string & s);
    
    /* Turn ALL OUTPUT from log on/off */
    static void 
    on(bool p);
    
    static bool 
    on();
};


} /* namespace log */
} /* namespace elib */


#include <elib/log/detail/_static_log.hpp>


#endif /* ELIB_LOG_STATIC_LOG_H */