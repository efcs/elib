#ifndef ELIB_CMD_OPTIONS_PARSED_OPTION_HPP
#define ELIB_CMD_OPTIONS_PARSED_OPTION_HPP

# include <elib/cmd_options/fwd.hpp>
# include <string>
# include <vector>

namespace elib { namespace cmd_options
{
    struct parsed_option
    {
        unsigned position;
        
        std::string raw;
        
        key_type key_info;
        unsigned position_key;
        std::string string_key;
        
        std::vector<std::string> tokens;
        
        bool matched;
        bool validated;
    };
}}                                                          // namespace elib
#endif /* ELIB_CMD_OPTIONS_PARSED_OPTION_HPP */