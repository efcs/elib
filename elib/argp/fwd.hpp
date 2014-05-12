#ifndef ELIB_ARGP_FWD_HPP
#define ELIB_ARGP_FWD_HPP

# include <vector>

namespace elib { namespace argp
{
    ////////////////////////////////////////////////////////////////////////////
    
    enum class key_type;
    
    class option_key;
    
    
    ////////////////////////////////////////////////////////////////////////////
    class command_line_parser;
    
    ////////////////////////////////////////////////////////////////////////////
    class parsed_option;
    
    ////////////////////////////////////////////////////////////////////////////
    enum class option_semantics;
    
    ////////////////////////////////////////////////////////////////////////////
    
    template <class ValueType>
    struct lexical_converter;
    
    
    
    
    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        class basic_option;
    }                                                       // namespace detail
    
    class switch_option;
    class positional_option;
    
    template <
        class ValueType
      , class Converter = lexical_converter<ValueType>
      >
    class option;
    
}}                                                          // namespace elib
#endif /* ELIB_ARGP_FWD_HPP */