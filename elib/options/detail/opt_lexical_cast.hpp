#ifndef ELIB_OPTIONS_DETAIL_OPT_LEXICAL_CAST_HPP
#define ELIB_OPTIONS_DETAIL_OPT_LEXICAL_CAST_HPP

# include <elib/aux.hpp>
# include <elib/lexical_cast.hpp>
# include <string>

namespace elib { namespace options
{
    namespace detail
    {
        template <
            class From
          , ELIB_ENABLE_IF(is_valid_lexical_cast<std::string, From>::value)
        >
        std::string 
        opt_lexical_cast(From const & from, std::string const &)
        {
            return elib::lexical_cast<std::string>(from);
        }
        
        template <
            class From
          , ELIB_ENABLE_IF(! is_valid_lexical_cast<std::string, From>::value)
        >
        std::string 
        opt_lexical_cast(From const &, std::string const & default_val)
        {
            return default_val;
        }
    }                                                       // namespace detail

}}                                                          // namespace elib
#endif /* ELIB_OPTIONS_DETAIL_OPT_LEXICAL_CAST_HPP */