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
#include "elib/log/file_log.hpp"

namespace elib {
namespace log {
    

file_log::file_log(const std::string & xfilename)
    : m_filename(xfilename)
{
    open(xfilename);
}


const std::string &
file_log::filename() const
{
    return m_filename;
}

bool
file_log::open(const std::string& xfilename)
{
    return open(xfilename, std::ios_base::app);
}

bool
file_log::open(const std::string& xfilename, std::ios_base::openmode mode)
{
    m_filename = xfilename;
    m_out.open(m_filename, mode);
    return m_out.good();
}

bool
file_log::good() const
{
    return m_out.good();
}

void
file_log::close()
{
    m_out.close();
}

std::ostream& file_log::_get_stream(level_e)
{
  return m_out;
}

} /* namespace log */
} /* namespace elib */