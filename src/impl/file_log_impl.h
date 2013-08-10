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
#ifndef ELIB_FILE_LOG_IMPL_H
#define ELIB_FILE_LOG_IMPL_H

#include "elib/file_log.h"
#include "log_impl.h"

#include <cstdarg>
#include <fstream>


namespace elib {
namespace detail {
    
    
class file_log_impl : public basic_log_impl {
public:
    file_log_impl() = default;
    ~file_log_impl() = default;
    
    bool open(const std::string & filename, std::ios_base::openmode mode);
    const std::string & filename() const;
    bool good() const;
    void close();
    
protected:
    std::ostream & 
    _get_stream(level_e e);

private:
    std::string m_filename;
    std::ofstream m_out;
};


inline bool
file_log_impl::open(const std::string & filename,
                    std::ios_base::openmode mode)
{
    lock_guard lock(_lock());
    
    m_filename = filename;
    m_out.clear();
    m_out.open(filename, mode);

    return good();
}

inline const std::string &
file_log_impl::filename() const
{
    return m_filename;
}

inline bool
file_log_impl::good() const
{
    return m_out.is_open() && m_out.good();
}

inline void
file_log_impl::close()
{
    lock_guard lock(_lock());
    m_filename = "";
    m_out.close();
}

inline std::ostream & 
file_log_impl::_get_stream(level_e l)
{
    UNUSED(l);
    return m_out;
}
    
} /* namespace detail */
} /* namespace elib */
#endif /* ELIB_FILE_LOG_IMPL_H */