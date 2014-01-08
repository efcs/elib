
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