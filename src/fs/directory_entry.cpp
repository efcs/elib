#include <elib/fs/directory_entry.h>
#include <elib/fs/operations.h>

namespace elib {
namespace fs {
    

directory_entry::directory_entry(const fs::path& p, file_status st,
                                 file_status symlink_st)
    : m_path{p}, m_status{st}, m_symlink_status{symlink_st}
{ }


void 
directory_entry::assign(const fs::path& p, file_status st,
                        file_status symlink_st)
{
    m_path = p;
    m_status = st;
    m_symlink_status = symlink_st;
}
    
void 
directory_entry::replace_filename(const fs::path& p, file_status st,
                                  file_status symlink_st)
{
    //TODO
    m_path.replace_filename(p);
    m_status = st;
    m_symlink_status = symlink_st;
}

    
file_status
directory_entry::status() const
{
    if (!status_known(m_status)) {
        if (status_known(m_symlink_status) && !is_symlink(m_symlink_status)) { 
            m_status = m_symlink_status; 
        }
        else { 
            m_status = fs::status(m_path); 
        }
    }
    
    return m_status;
}
    
file_status
directory_entry::status(std::error_code& ec) const noexcept
{
    if (!status_known(m_status)) {
        if (status_known(m_symlink_status) && !is_symlink(m_symlink_status)) { 
            m_status = m_symlink_status; 
        }
        else { 
            m_status = fs::status(m_path, ec); 
        }
    }
    
    return m_status;
}
    
file_status
directory_entry::symlink_status() const
{
    if (! status_known(m_symlink_status)) {
        m_symlink_status = fs::symlink_status(m_path);
    }
    return m_symlink_status;
}
    
file_status
directory_entry::symlink_status(std::error_code& ec) const noexcept
{
    if (! status_known(m_symlink_status)) {
        m_symlink_status = fs::symlink_status(m_path, ec);
    }
    return m_symlink_status;
}
    
    
} /* namespace fs */
} /* namespace elib */