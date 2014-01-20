#ifndef ELIB_FUNCTIONAL_STD_UTILITY_HPP
#define ELIB_FUNCTIONAL_STD_UTILITY_HPP

# include <elib/utility.hpp>
# include <utility>

namespace elib 
{
    namespace functional
    {
        namespace std
        {
            ////////////////////////////////////////////////////////////////////
            // make_pair
            template <class T = void, class U = void>
            struct make_pair;
            
            template <class T> struct make_pair<void, T>;
            template <class T> struct make_pair<T, void>;
            
            template <class T, class U>
            struct make_pair
            {
                using result_type = ::std::pair<T, U>;
                using first_argument_type = T;
                using second_argument_type = U;
                
                constexpr ::std::pair<T, U> operator()(const T& t, const U& u) const
                ELIB_RETURN_NOEXCEPT(
                  ::std::make_pair(t, u)
                )
            };
            
            template <>
            struct make_pair<void, void>
            {
                template <class T, class U>
                
            };
            
            
        }                                                   // namespace std
    }                                                       // namespace functional
}                                                           // namespace elib
#endif /* ELIB_FUNCTIONAL_STD_UTILITY_HPP */