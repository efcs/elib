#include <elib/fs/directory_iterator.hpp>

namespace elib {
namespace fs {
    
void
directory_iterator::_handle_open(const path& p, std::error_code& ec) noexcept
{
    ec.clear();
    m_stream.open(p, ec);
    if (ec)
        return;
    
    // needs initial increment to set m_curr_ent
    increment(ec);
}
    
    
} /* namespace fs */
} /* namespace elib */