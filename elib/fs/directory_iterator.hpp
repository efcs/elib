#ifndef ELIB_FS_DIRECTORY_ITERATOR_HPP
#define ELIB_FS_DIRECTORY_ITERATOR_HPP

#include <elib/fs/path.hpp>
#include <elib/fs/directory_entry.hpp>
#include <elib/fs/filesystem_error.hpp>
#include <elib/fs/detail/filesystem_error_helper.hpp>
#include <elib/fs/detail/directory_stream.hpp>


#include <iterator>
#include <system_error>
#include <memory>


namespace elib {
namespace fs {
    
    
//TODO
class directory_iterator :
    public std::iterator<std::input_iterator_tag, directory_entry> {
public:
    // member functions
    directory_iterator() noexcept
        : m_end{true}
    { }
    
    explicit 
    directory_iterator(const path& p)
        : m_end{false}
    {
        std::error_code ec;
        _handle_open(p, ec);
        if (ec)
            throw filesystem_error(ec.message(), p, ec);
    }
    
    directory_iterator(const path& p, std::error_code& ec) noexcept
        : m_end{false}
    {
        _handle_open(p, ec);
    }
    
    directory_iterator(const directory_iterator&) = default;
    
    directory_iterator(directory_iterator&&) = default;
    
    ~directory_iterator() = default;

    directory_iterator& 
    operator=(const directory_iterator&) = default;
    
    directory_iterator& 
    operator=(directory_iterator&&) = default;

    const directory_entry& 
    operator*() const
    { return m_curr_ent; }
    
    const directory_entry*
    operator->() const
    { return &m_curr_ent; }
    
    directory_iterator&    
    operator++()
    {   
        std::error_code ec;
        increment(ec);
        if (ec)
            throw filesystem_error(ec.message(), ec);
        return *this;
    }
    
    //TODO find a way to remove this
    directory_iterator
    operator++(int)
    {
        directory_iterator other = *this;
        ++(*this);
        return other;
    }
    
    directory_iterator&    
    increment(std::error_code& ec) noexcept
    {
        ec.clear();
        while (true) {
            if (m_end)
                return *this;
            
            auto&& p = _increment(ec);
            
            if (ec)
                return *this;
            
            if (p.filename() != "." && p.filename() != "..") {
                m_curr_ent.assign(p);
                return *this;
            }
        }
    }
    
    friend bool 
    operator==(const directory_iterator& lhs, const directory_iterator& rhs)
    {
        if (lhs.m_end && rhs.m_end)
            return true;
        return (&lhs == &rhs);
    }
    
    friend bool 
    operator!=(const directory_iterator& lhs, const directory_iterator& rhs)
    {
        return !(lhs == rhs);
    }

    // other members as required by
    //  C++ Std, 24.1.1 Input iterators [input.iterators]
    //TODO
private:
    // handler for opening the stream
    void _handle_open(const path& p, std::error_code& ec) noexcept;
    
    // handle logic for incrementing stream
    const path&
    _increment(std::error_code& ec) noexcept
    {
        ec.clear();
        if (m_end)
           return m_stream.get(); 
        
        auto&& p = m_stream.advance(ec);
        
        if (m_stream.eof()) {
            m_end = true;
        }
        
        return p;
    }
    
    // indicates end iterator
    bool m_end{false};
    
    // the current directory entry
    directory_entry m_curr_ent{};
    
    // underlying implementation is wrapper for readdir
    // it contains a copy of the root path
    detail::directory_stream m_stream{};
};
    

} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_DIRECTORY_ITERATOR_HPP */