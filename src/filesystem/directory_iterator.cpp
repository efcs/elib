#include <elib/filesystem/directory_iterator.hpp>
#include <elib/filesystem/filesystem_error.hpp>

namespace elib { namespace fs { inline namespace v1
{
    
    namespace detail
    {
      
        typedef path::string_type string_type;
    ///////////////////////////////////////////////////////////////////////////
    //                          POSIX helpers                                                            
    //////////////////////////////////////////////////////////////////////////
      
        inline DIR *posix_opendir(const string_type& p, std::error_code *ec)
        {
            DIR *ret;
            if ((ret = ::opendir(p.c_str())) == nullptr) {
                std::error_code m_ec = capture_errno();
                if (ec) {
                    *ec = m_ec;
                    return nullptr;
                } else {
                    throw filesystem_error("fs::posix_opendir", path(p), m_ec);
                }
            }
            if (ec) ec->clear();
            return ret;
        }
      
        inline string_type posix_readdir_r(DIR *dir_stream, std::error_code *ec)
        {
            struct dirent dir_entry;
            struct dirent *dir_entry_ptr{nullptr};
            
            int ret;
            if ((ret = ::readdir_r(dir_stream,  &dir_entry,  &dir_entry_ptr)) != 0) {
                std::error_code m_ec = capture_errno();
                if (ec) {
                    *ec = m_ec;
                    return {};
                } else {
                    throw filesystem_error("fs::posix_readdir_r", m_ec);
                }
            }
            if (ec) ec->clear();
            if (dir_entry_ptr == nullptr) return string_type{};
            return string_type{dir_entry.d_name};
        }
      
        inline void posix_closedir(DIR *dir_stream,  std::error_code *ec)
        {
            if (::closedir(dir_stream) == -1) {
                std::error_code m_ec = capture_errno();
                if (ec) {
                    *ec = m_ec;
                    return;
                } else {
                    throw filesystem_error("fs::posix_closedir", m_ec);
                }            
            }
            if (ec) ec->clear();
        }
      
    ////////////////////////////////////////////////////////////////////////////
    //                          CLASS DIR_STREAM                                              
    ////////////////////////////////////////////////////////////////////////////
    
        dir_stream::dir_stream(const path& p, std::error_code *ec)
        {
            m_dir_stream = detail::posix_opendir(p.native(),  ec);
        }
      
        dir_stream::~dir_stream() noexcept
        { 
            if (m_dir_stream) {
                // we don't want to throw,  so eat the error if one exists
                std::error_code ec;
                this->close(&ec); 
            }
        }
      
        path dir_stream::advance(std::error_code *ec)
        {
            path p{};
            if (m_dir_stream == nullptr) return path{};
            std::error_code m_ec;
            auto str = detail::posix_readdir_r(m_dir_stream,  &m_ec);
            if (m_ec || str.empty()) close();
            if (ec && m_ec) *ec = m_ec;
            return path{str};
        }
        
        void dir_stream::close(std::error_code *ec)
        {
            if (m_dir_stream == nullptr) return;
            // incase posix_closedir throws, set m_dir_stream
            // to nullptr before the call
            DIR *tmp = m_dir_stream;
            m_dir_stream = nullptr;
            detail::posix_closedir(tmp, ec);
        }
    }                                                       // namespace detail    
    
////////////////////////////////////////////////////////////////////////////////
//                        CLASS DIRECTORY_ITERATOR                                  
////////////////////////////////////////////////////////////////////////////////
    
    directory_iterator::directory_iterator(const path& p, std::error_code *ec)
      : directory_iterator()
    {
        m_stream = ec ? std::make_shared<detail::dir_stream>(p, ec)
                        : std::make_shared<detail::dir_stream>(p);
        if (ec && *ec) {
            m_make_end();
            return;
        }
        m_root_path = p;
        // we "increment" the iterator to set it to the first value
        m_increment(ec);
    }
    
    directory_iterator& directory_iterator::m_increment(std::error_code *ec)
    {
        if (!m_stream) return *this;
        
        path part;
        while (m_stream->good()) {
            part = m_stream->advance(ec);
            if (part != "." && part != "..")
                break;
        }

        if (!m_stream->good())
            m_make_end();
        else
            m_element.assign(m_root_path / part);
        return *this;
    }
    
    void directory_iterator::m_make_end()
    {
        m_stream.reset();
        m_root_path.clear();
        m_element.assign(path{""});
    }
    
    
////////////////////////////////////////////////////////////////////////////////
//                 CLASS RECURSIVE_DIRECTORY_ITERATOR                                                         
////////////////////////////////////////////////////////////////////////////////
    
    
    
    recursive_directory_iterator::recursive_directory_iterator(const path& p, 
        directory_options opt, std::error_code *ec)
      : recursive_directory_iterator()
    {
        m_options = opt;
        auto curr_iter = directory_iterator{p, ec};
        if ((ec && *ec) || curr_iter == directory_iterator{}) return;
            
        m_stack_ptr = std::make_shared<
                        std::stack<directory_iterator> 
                        >();

        m_stack_ptr->push(curr_iter);
    }
    
    
    
    recursive_directory_iterator& 
    recursive_directory_iterator::m_increment(std::error_code *ec)
    {
        if (!m_stack_ptr) return *this;
        
        if (m_try_recursion(ec) || (ec && *ec))
            return *this;
            
        const directory_iterator end_it;
        while (m_stack_ptr->size() > 0)
        {
            m_stack_ptr->top().m_increment(ec);
            if ((ec && *ec) || m_stack_ptr->top() != end_it)
                break;
            
            m_stack_ptr->pop();
        }
        
        if ((ec && *ec) || m_stack_ptr->size() == 0)
            m_make_end();
            
        m_rec = true;
        return *this;
    }
    
    bool recursive_directory_iterator::m_try_recursion(std::error_code *ec)
        {
        if (!m_stack_ptr || m_stack_ptr->size() == 0 
            || m_stack_ptr->top() == directory_iterator{})
        { return false; }
        
        auto& curr_it = m_stack_ptr->top();
        
        using under_t = typename std::underlying_type<directory_options>::type;
        bool rec_sym = static_cast<under_t>(options()) 
            & static_cast<under_t>(directory_options::follow_directory_symlink);
            
        if (recursion_pending() && is_directory(curr_it->status()) &&
            (!is_symlink(curr_it->symlink_status()) || rec_sym))
        {
            auto tmp = directory_iterator{curr_it->path(), ec};
            if ((ec && *ec) || tmp == directory_iterator{})
                return false;
            //else
            m_stack_ptr->push(tmp);
            return true;
        }
        
        return false;
    }
    
    void recursive_directory_iterator::m_make_end()
    {
        m_stack_ptr.reset();
    }
}}}                                                          // namespace elib