#ifndef ELIB_FS_DIRECTORY_ITERATOR_H
#define ELIB_FS_DIRECTORY_ITERATOR_H


#include <elib/fs/directory_entry.h>
#include <elib/fs/path.h>


#include <iterator>
#include <system_error>


namespace elib {
namespace fs {
    
    
//TODO
class directory_iterator :
    public std::iterator<std::input_iterator_tag, directory_entry> {
public:
    // member functions
    directory_iterator() noexcept;
    
    explicit 
    directory_iterator(const path& p);
    
    directory_iterator(const path& p, std::error_code& ec) noexcept;
    
    directory_iterator(const directory_iterator&) = default;
    
    directory_iterator(directory_iterator&&) = default;
    
    ~directory_iterator() = default;

    directory_iterator & 
    operator=(const directory_iterator&) = default;
    
    directory_iterator & 
    operator=(directory_iterator&&) = default;

    const directory_entry & 
    operator*() const;
    
    const directory_entry*
    operator->() const;
    
    directory_iterator &    
    operator++();
    
    directory_iterator &    
    increment(std::error_code& ec) noexcept;

    // other members as required by
    //  C++ Std, 24.1.1 Input iterators [input.iterators]
    //TODO
};
    

} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_DIRECTORY_ITERATOR_H */