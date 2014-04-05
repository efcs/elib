#ifndef ELIB_AUX_TRAITS_ALIGNED_STORAGE_HPP
#define ELIB_AUX_TRAITS_ALIGNED_STORAGE_HPP

# include <type_traits>
# include <cstddef>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::aligned_storage;
        
        template <
            std::size_t Len
          , std::size_t Align = static_cast<std::size_t>(-1)
          >
        using aligned_storage_t = typename aligned_storage<Len, Align>::type;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ALIGNED_STORAGE_HPP */
