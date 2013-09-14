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
#include "elib/log/log.hpp"

namespace elib {
namespace log {
    
log::log()
    : m_out(std::cout), m_err(std::cerr)
{ }

log::log(level_e l)
    : basic_log(l), m_out(std::cout), m_err(std::cerr)
{ }

std::ostream &
log::_get_stream(level_e l)
{
    if (l <= level_e::step || l == level_e::raw_out)
        return m_out;
    return m_err;
}

} /* namespace log */
} /* namespace elib */
