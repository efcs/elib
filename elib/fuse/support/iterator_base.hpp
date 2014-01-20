#ifndef ELIB_FUSE_SUPPORT_ITERATOR_BASE_HPP
#define ELIB_FUSE_SUPPORT_ITERATOR_BASE_HPP

namespace elib { namespace fuse
{
    struct iterator_root 
    {};
    
    template <class It>
    struct iterator_base 
      : iterator_root
    {
        It const& cast() const noexcept
        {
            return static_cast<It const&>(*this);
        }
        
        It& cast() noexcept
        {
            return static_cast<It &>(*this);
        }
    };
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SUPPORT_ITERATOR_BASE_HPP */
