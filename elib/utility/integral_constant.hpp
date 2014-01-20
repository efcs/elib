#ifndef ELIB_UTILITY_INTEGRAL_CONSTANT_HPP
#define ELIB_UTILITY_INTEGRAL_CONSTANT_HPP

# include <type_traits>
# include <cstddef>

# /* type deduction macro for std::integral_constant */
# define ELIB_AUTO_INTC(...) \
    ::std::integral_constant<decltype(__VA_ARGS__), __VA_ARGS__>
# 

namespace elib 
{
    namespace utility
    {
        template <bool V>
        using bool_ = std::integral_constant<bool, V>;
        
        using true_ = bool_<true>;
        using false_ = bool_<false>;
        
        template <char V>
        using char_ = std::integral_constant<char, V>;
        
        template <int V>
        using int_ = std::integral_constant<bool, V>;
        
        template <unsigned V>
        using uint_ = std::integral_constant<unsigned, V>;
        
        template <long V>
        using long_ = std::integral_constant<long, V>;
        
        template <unsigned long V>
        using ulong_ = std::integral_constant<unsigned long, V>;
        
        template <long long V>
        using llong_ = std::integral_constant<long long, V>;
        
        template <unsigned long long V>
        using ullong_ = std::integral_constant<unsigned long long, V>;
        
        template <std::size_t V>
        using size_type_ = std::integral_constant<std::size_t, V>;
    }                                                       // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_INTEGRAL_CONSTANT_HPP */