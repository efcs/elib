#ifndef ELIB_MEMORY_ALLOCATOR_DESTRUCTOR_HPP
#define ELIB_MEMORY_ALLOCATOR_DESTRUCTOR_HPP

# include <memory>

namespace elib { namespace memory
{
    ////////////////////////////////////////////////////////////////////////
    template <class Alloc>
    struct allocator_destructor
    {
        using traits = std::allocator_traits<Alloc>;
        using pointer = typename traits::pointer;
        using size_type = typename traits::size_type;
            
    public:
        inline allocator_destructor(Alloc & a, size_type s)
            : m_alloc(a), m_size(s)
        {}
            
        inline void operator()(pointer p) noexcept
        {
            traits::deallocate(m_alloc, p, m_size);
        }
            
    private:
        Alloc & m_alloc;
        size_type m_size;
    };
}}                                                          // namespace elib
namespace elib
{
    using memory::allocator_destructor;
}                                                           // namespace elib
#endif /* ELIB_MEMORY_ALLOCATOR_DESTRUCTOR_HPP */