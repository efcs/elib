#ifndef ELIB_AUX_TRAITS_ALIGNED_STORAGE_HPP
#define ELIB_AUX_TRAITS_ALIGNED_STORAGE_HPP

# include <elib/aux/integral_constant.hpp>
# include <type_traits>
# include <cstddef>

namespace elib { namespace aux
{
    using std::aligned_storage;
        
    /// The Align param has an implementation specified default value.
    /// To provide aligned_storage_t the default argument must be deduced.
    namespace detail
    {
        template <class T>
        struct deduce_align_impl;
            
        template <std::size_t Len, std::size_t Align>
        struct deduce_align_impl<aligned_storage<Len, Align>>
          : elib::integral_constant<std::size_t, Align>
        {};
            
        template <std::size_t Len>
        using deduced_align = deduce_align_impl<aligned_storage<Len>>;
    }                                                   // namespace detail
        
    template <
        std::size_t Len
      , std::size_t Align = detail::deduced_align<Len>::value
      >
    using aligned_storage_t = typename aligned_storage<Len, Align>::type;
    
}}                                                           //namespace elib
#endif /* ELIB_AUX_TRAITS_ALIGNED_STORAGE_HPP */
