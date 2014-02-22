#ifndef ELIB_OPTIONS_FWD_HPP
#define ELIB_OPTIONS_FWD_HPP

# include <vector>
# include <string>
# include <memory>


namespace elib { namespace options
{
    ////////////////////////////////////////////////////////////////////////////
    //                              Errors
    ////////////////////////////////////////////////////////////////////////////
    class error;
    class duplicate_option_error;
    class option_name_error;
    class multiple_values_error;
    class multiple_occurrences_error;
    class required_option_error;
    class unknown_option_error;
    class ambiguous_option_error;
    class command_line_syntax_error;
    class validation_error;
    
    ////////////////////////////////////////////////////////////////////////////
    //                              Options
    ////////////////////////////////////////////////////////////////////////////
    enum class match_result
    {
        none, full, aprox
    };
    
    struct option;
    
    class option_description;
    class option_description_init;
    
    class options_description;
    class positional_options_description;
    
    ////////////////////////////////////////////////////////////////////////////
    //                              Converters
    ////////////////////////////////////////////////////////////////////////////
    
    /** uses elib::lexical_cast */
    template <class T> struct lexical_converter;
    
    /** uses elib::enumeration::enum_cast */
    template <class T> struct enum_converter;
    
    /** Chooses the best converter for type T */
    template <class T> struct default_converter;
    
    ////////////////////////////////////////////////////////////////////////////
    //                              Values
    ////////////////////////////////////////////////////////////////////////////
    class value_semantic;
    class untyped_value;
    
    class typed_value_base;
    
    template <class T, class Converter = default_converter<T>>
    class typed_value;
    
    ////////////////////////////////////////////////////////////////////////////
    //                              Parsers
    ////////////////////////////////////////////////////////////////////////////
    class command_line_parser;
    class parsed_options;
    
    ////////////////////////////////////////////////////////////////////////////
    //                           Storage
    ////////////////////////////////////////////////////////////////////////////
    class variable_map;
    
}}                                                      // namespace elib::options
#endif /* ELIB_OPTIONS_FWD_HPP */