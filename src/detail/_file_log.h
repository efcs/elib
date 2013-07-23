#ifndef ELIB__FILELOG_H
#define ELIB__FILELOG_H

#include "elib/file_log.h"
#include "_log.h"

#include <fstream>

namespace elib {
    
    
class file_log_impl : public basic_log_impl {
public:
    file_log_impl();
    ~file_log_impl();
    
    bool open(const std::string & filename);
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


inline 
file_log_impl::file_log_impl()
{
}

inline
file_log_impl::~file_log_impl()
{
}

inline bool
file_log_impl::open(const std::string & filename)
{
    lock_guard lock(_lock());
    
    m_filename = filename;
    m_out.clear();
    m_out.open(filename);
    if (m_out.good())
        m_out.seekp(0, std::ios_base::end);

    return m_out.good();
}

inline const std::string &
file_log_impl::filename() const
{
    return m_filename;
}

inline bool
file_log_impl::good() const
{
    return m_out.good();
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
    ((void)l); //UNUSED
    return m_out;
}

} /* namespace elib */
#endif /* ELIB__FILELOG_H */