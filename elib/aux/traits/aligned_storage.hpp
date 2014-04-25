#ifndef ELIB_AUX_TRAITS_ALIGNED_STORAGE_HPP
#define ELIB_AUX_TRAITS_ALIGNED_STORAGE_HPP

# include <elib/aux/integral_constant.hpp>
# include <type_traits>
# include <cstddef>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::aligned_storage;
        
        namespace traits_detail
        {
            template <class T>
            struct deduce_align_impl;
            
            template <std::size_t Len, std::size_t Align>
            struct deduce_align_impl<aligned_storage<Len, Align>>
              : elib::integral_constant<std::size_t, Align>
            {};
            
            template <std::size_t Len>
            using deduced_align = deduce_align_impl<aligned_storage<Len>>;
        }                                                   // namespace traits_detail
        
        template <
            std::size_t Len
          , std::size_t Align = traits_detail::deduced_align<Len>::value
          >
        using aligned_storage_t = typename aligned_storage<Len, Align>::value;
    }                                                       //namespace traits
    
    using namespace traits;
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ALIGNED_STORAGE_HPP */
