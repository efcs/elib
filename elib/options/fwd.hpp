#ifndef ELIB_OPTIONS_FWD_HPP
#define ELIB_OPTIONS_FWD_HPP

# include <vector>
# include <string>

namespace elib { namespace options
{
    ////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////
    class error;
    class duplicate_option_error;
    class option_name_error;
    class multiple_values_error;
    class mutiple_occurrences_error;
    class required_option_error;
    class unknown_option_error;
    class ambiguous_option_error;
    class command_line_syntax_error;
    class validation_error;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////
    enum class match_result
    {
        none, full, aprox
    };
    
    class option;
    
    class option_description;
    class option_description_init;
    
    class options_description;
    class positional_options_description;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////
    class value_semantic;
    class untyped_value;
    class typed_value_base;
    
    template <class T>
    class typed_value;
    
    template <class T>
    typed_value<T>* value();
    
    template <class T>
    typed_value<T>* value(T* v);
    
    typed_value<bool>* bool_switch();
    typed_value<bool>* bool_switch(bool * v);
    
    ////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////
    class command_line_parser;
    class parsed_options;
    
    parsed_options 
    parse_command_line(
        int argc, const char* const argv[]
      , options_description const &
    );
    
    enum class collect_unrecognized_mode
    {
        include_positional
      , exclude_positional
    };
    
    static constexpr collect_unrecognized_mode include_positional = 
        collect_unrecognized_mode::include_positional;
        
    static constexpr collect_unrecognized_mode exclude_positional =
        collect_unrecognized_mode::exclude_positional;
    
    std::vector< std::string >
    collect_unrecognized(
        std::vector< option > & options
      , collect_unrecognized_mode mode
    );
    
    ////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////
    class variable_map;
    class variable_value;
    
    void store(parsed_options const &, variable_map &);
    void notify(variable_map &);
    
}}                                                      // namespace elib::options
#endif /* ELIB_OPTIONS_FWD_HPP */