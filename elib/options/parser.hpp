#ifndef ELIB_OPTIONS_PARSER_HPP
#define ELIB_OPTIONS_PARSER_HPP

# include <elib/options/fwd.hpp>
# include <elib/options/option.hpp>
# include <elib/options/value.hpp>
# include <string>
# include <vector>

namespace elib { namespace options
{  
    ////////////////////////////////////////////////////////////////////////////
    //
    class parsed_options
    {
        explicit parsed_options(options_description const* desc);
        
        std::vector< option > options;
        
        options_description const* description;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class command_line_parser
    {
    public:
        command_line_parser(std::vector<std::string> const & args);
        command_line_parser(int argc, const char* const argv[]);
        
        command_line_parser & options(options_description const &);
        command_line_parser & positional(positional_options_description const &);
        
        parsed_options run();

    private:
        options_description const* m_desc;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    parsed_options 
    parse_command_line(
        int argc, const char* const argv[]
      , options_description const &
    );
    
    ////////////////////////////////////////////////////////////////////////////
    //
    std::vector< std::string >
    collect_unrecognized(
        std::vector< option > & options
      , collect_unrecognized_mode mode
    );
    
}}                                                          // namespace elib
#endif /* ELIB_OPTIONS_PARSER_HPP */