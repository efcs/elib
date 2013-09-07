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
#ifndef ELIB_LOG_LOG_H
#define ELIB_LOG_LOG_H

#include <elib/log/basic_log.h>
#include <elib/log/log_level.h>

#include <iostream>


namespace elib {
namespace log {
    

namespace detail { class log_impl; }
    
/* Actual logging class, implements the basic_log iterface */
class log : public basic_log {
public:
    log();
    explicit log(level_e level);
    
protected:
    std::ostream & 
    _get_stream(level_e level);
    
private:
    std::ostream &m_out, &m_err;
};
 

} /* namespace log */
} /* namespace elib */
#endif /* ELIB_LOG_LOG_H */