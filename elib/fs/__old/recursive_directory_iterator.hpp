#ifndef ELIB_FS_RECURSIVE_DIRECTORY_ITERATOR_HPP
#define ELIB_FS_RECURSIVE_DIRECTORY_ITERATOR_HPP


#include <elib/fs/directory_entry.hpp>
#include <elib/fs/path.hpp>
#include <elib/fs/directory_iterator.hpp>
#include <elib/fs/directory_options.hpp>


#include <iterator>
#include <system_error>


namespace elib {
namespace fs {
    

//TODO
class recursive_directory_iterator :
    public std::iterator<std::input_iterator_tag, directory_entry> {
public:

// constructors and destructor
    recursive_directory_iterator() noexcept;
    
    recursive_directory_iterator(const recursive_directory_iterator&) = default;
    
    explicit 
    recursive_directory_iterator(const path& p,
        directory_options options = directory_options::none);
    
    recursive_directory_iterator(const path& p,
        directory_options options, std::error_code& ec) noexcept;
        
    recursive_directory_iterator(const path& p, std::error_code& ec) noexcept;
    
    recursive_directory_iterator(recursive_directory_iterator&&) = default;
        
    ~recursive_directory_iterator() = default;

// observers
    directory_options  
    options() const;
    
    int                
    depth() const;
    
    bool               
    recursion_pending() const;

// modifiers
    recursive_directory_iterator& 
    operator=(const recursive_directory_iterator&) = default;
    
    recursive_directory_iterator& 
    operator=(recursive_directory_iterator&&) = default;

    recursive_directory_iterator& 
    operator++();
    
    recursive_directory_iterator& 
    increment(std::error_code& ec);

    void 
    pop();
    
    void 
    disable_recursion_pending();

    // ... other members as required for Input iterators [input.iterators]
    //TODO
};
    

} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_RECURSIVE_DIRECTORY_ITERATOR_HPP */