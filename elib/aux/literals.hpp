#ifndef ELIB_AUX_LITERALS_HPP
#define ELIB_AUX_LITERALS_HPP

# include <elib/aux/integral_constant.hpp>
# include <string>
# include <cstddef>

namespace elib 
{ 
    namespace aux { namespace detail
    {
        template <unsigned Value, char ...Ch>
        struct generate_binary_literal
          : integral_constant<unsigned, Value>
        {
            static_assert(sizeof...(Ch) == 0, "Pack is empty");
        };
        
        template <unsigned Value, char First, char ...Rest>
        struct generate_binary_literal<Value, First, Rest...>
          : generate_binary_literal<(Value << 1) + (First - '0'), Rest...>
        {
            static_assert(
                First == '0' || First == '1'
              , "Only 0 and 1 are allowed in a binary literal"
              );
        };
    }}                                                 // namespace aux::detail
    
// Scan doesn't like user defined literals
# if !defined(ELIB_CONFIG_COVERITY_SCAN)
    template <char ...Ch>
    constexpr unsigned operator "" _bin() noexcept
    {
        static_assert(
            sizeof...(Ch) <= sizeof(unsigned) * 8
          , "binary literals can contain at most sizeof(unsigned) * 8 characters"
          );
        static_assert(
            sizeof...(Ch) != 0
          , "binary literals must contain at least 1 character"
          );
        return aux::detail::generate_binary_literal<0u, Ch...>::value; 
    }
    
    inline std::string operator "" _str(const char *s)
    {
        return s;
    }
    
    inline std::string operator "" _str(const char *s, std::size_t len) 
    {
        return std::string(s, len);
    }
# endif /* ELIB_CONFIG_COVERITY_SCAN */
}                                                           // namespace elib
#endif /* ELIB_AUX_LITERALS_HPP */