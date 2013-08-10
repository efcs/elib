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
#include "elib/file_log.h"

namespace elib {
    
file_log::file_log()
{
}

file_log::file_log(const std::string & filename)
    : m_filename(filename)
{
    open(filename);
}

file_log::~file_log()
{
}

const std::string &
file_log::filename() const
{
    return m_filename;
}

bool
file_log::open(const std::string & filename)
{
    return open(filename, std::ios_base::app);
}

bool
file_log::open(const std::string & filename, std::ios_base::openmode mode)
{
    m_filename = filename;
    m_out.open(filename.c_str(), mode);
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

} /* namespace elib */