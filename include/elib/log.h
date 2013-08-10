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
#ifndef ELIB_LOG_H
#define ELIB_LOG_H

#include "basic_log.h"
#include "log_level.h"

#include <memory>

namespace elib {
    

namespace detail { class log_impl; }
    
/* Actual logging class, implements the basic_log iterface */
class log : public basic_log {
public:
    log();
    
    /* same as static log interface */
    const std::string & prompt(level_e l) const;
    void prompt(level_e l, const std::string &prompt);
    
    void level(level_e l);
    level_e level();
    
    void print(level_e l, const char *msg, ... );
    void print(level_e l, const std::string &msg);
    
    void debug(const char *msg, ... );
    void debug(const std::string & s);
    
    void info(const char *msg, ... );
    void info(const std::string & s);
    
    void step(const char *msg, ... );
    void step(const std::string & s);
    
    void warn(const char *msg, ... );
    void warn(const std::string & s);
    
    void err(const char *msg, ... );
    void err(const std::string & s);
    
    void fatal(const char *msg, ...);
    void fatal(const std::string & s);
    
    void raw_out(const char *msg, ...);
    void raw_out(const std::string & s);
    
    void raw_err(const char *msg, ...);
    void raw_err(const std::string & s);
    
    /* Turn ALL OUTPUT from log on/off */
    void on(bool p);
    bool on() const;
private:
    /* pimpl is useful for some reason */
    std::shared_ptr<detail::log_impl> m_impl;
};
 


} /* namespace elib */
#endif /* ELIB_LOG_H */
