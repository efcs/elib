#ifndef ELIB_CMD_OPTIONS_FWD_HPP
#define ELIB_CMD_OPTIONS_FWD_HPP

namespace elib { namespace cmd_options
{
    enum class option_type
    {
        none, 
        switch_option,
        positional_option
        value_option, 
        multi_option
    };
    
    enum class key_type
    {
        none, 
        positional, 
        long_name, 
        short_name, 
    };
    
    constexpr unsigned bad_position_key = 0;
    constexpr unsigned wildcard_position_key = static_cast<unsigned>(-1);
    
    ///////////////////////////////////////////////////////////////////////////
    enum class option_semantics : unsigned;
    
    ////////////////////////////////////////////////////////////////////////////
    class command_line;
    
    ////////////////////////////////////////////////////////////////////////////
    struct parsed_option;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ValueType, class StorageType = ValueType>
    struct value_handler;
    
    template <class ValueType, class StorageType = std::vector<ValueType>>
    struct multi_value_handler;
    
    struct switch_handler;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class Handler>
    struct handler_traits;
    
    ////////////////////////////////////////////////////////////////////////////
    class basic_option;
    
    template <class Handler = switch_handler>
    class switch_option;
    
    template <
        class ValueType
      , class Handler = value_handler<ValueType>
      >
    class positional_option;
    
    template <
        class ValueType
      , class Handler = value_handler<ValueType>
      >
    class value_option;
    
    template <
        class ValueType
      , class Handler = multi_value_handler<ValueType>
      >
    class multi_option;
    
    ////////////////////////////////////////////////////////////////////////////
    class cmd_options_error;
    class option_error;
    class parse_error;
}}                                                          // namespace elib
#endif /* ELIB_CMD_OPTIONS_FWD_HPP */