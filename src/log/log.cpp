
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
