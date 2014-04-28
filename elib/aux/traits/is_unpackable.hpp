#ifndef ELIB_AUX_TRAITS_IS_UNPACKABLE_HPP
#define ELIB_AUX_TRAITS_IS_UNPACKABLE_HPP

# include <elib/config.hpp>
# include <elib/aux/integral_constant.hpp>
# include <type_traits>
# include <utility> /* for std::tuple_size */

namespace elib { namespace aux
{
    namespace traits
    {
        namespace traits_detail
        {
            template <class T>
            struct is_unpackable_impl
            {
            private:
                template <
                    class U
                  , class = typename std::tuple_size<U>::type
                  >
                static elib::true_ test(int);
                
                template <class>
                static elib::false_ test(long);

            public:
                using type = decltype(test<T>(0));
            };
        }                                            // namespace traits_detail
        
        template <class T>
        using is_unpackable = typename traits_detail::is_unpackable_impl<T>::type;
        
# if defined(ELIB_CONFIG_HAS_VARIABLE_TEMPLATES)
        template <class T>
        constexpr bool is_unpackable_v = is_unpackable<T>::value; 
#   endif
    }                                                       // namespace traits
    
    using namespace traits;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_IS_UNPACKABLE_HPP */