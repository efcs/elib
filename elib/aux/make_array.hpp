#ifndef ELIB_AUX_MAKE_ARRAY_HPP
#define ELIB_AUX_MAKE_ARRAY_HPP

# include <elib/aux/enable_if.hpp>
# include <elib/aux/forward.hpp>
# include <elib/aux/integer_sequence.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/logical.hpp> /* for and_ */
# include <elib/aux/traits/sfinae_common_type.hpp>
# include <elib/aux/traits/is_same.hpp>
# include <elib/aux/traits/remove_cv.hpp>
# include <elib/aux/traits/remove_reference.hpp>
# include <elib/aux/traits/uncvref.hpp>
# include <array>
# include <functional> /* for std::reference_wrapper */
# include <cstddef>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T>
        struct is_ref_wrapper : false_ {};
        
        template <class T>
        struct is_ref_wrapper<std::reference_wrapper<T>> : true_ {};
        
        // NOTE: leading true's are to make sure and_c gets at least 2 values.
        template <class ...Args>
        using none_are_ref_wrappers = and_c<true, true, 
            not is_ref_wrapper<uncvref<Args>>::value...
          >;
        
        template <class T, std::size_t N, std::size_t ...Indexes>
        constexpr std::array<remove_cv_t<T>, N> 
        to_array_impl(T (&ar)[N], index_sequence<Indexes...>)
        {
            return {{ ar[Indexes]... }};
        }
    }                                                       // namespace detail
    
    template <
        class ...Args
      , ELIB_ENABLE_IF(detail::none_are_ref_wrappers<Args...>::value)
      >
    constexpr std::array<sfinae_common_type_t<Args...>, sizeof...(Args)> 
    make_array(Args&&... args)
    {
        using T = sfinae_common_type_t<Args...>;
        return {{ static_cast<T>(elib::forward<Args>(args))... }};
    }
    
    template <class D, class ...Args>
    constexpr std::array<D, sizeof...(Args)> 
    make_array(Args&&... args)
    {
        return {{ static_cast<D>(elib::forward<Args>(args))... }};
    }
    
    template <class T, std::size_t N>
    constexpr std::array<remove_cv_t<T>, N> 
    to_array(T (&ar)[N] )
    {
        return detail::to_array_impl(ar, make_index_sequence<N>{});
    }
}}                                                          // namespace elib
namespace elib
{
    using aux::make_array;
    using aux::to_array;
}                                                           // namespace elib
#endif /* ELIB_AUX_MAKE_ARRAY_HPP */