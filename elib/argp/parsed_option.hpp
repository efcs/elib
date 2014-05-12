#ifndef ELIB_ARGP_PARSED_OPTION_HPP
#define ELIB_ARGP_PARSED_OPTION_HPP

# include <elib/argp/fwd.hpp>
# include <string>
# include <vector>

namespace elib { namespace argp
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
#endif /* ELIB_ARGP_PARSED_OPTION_HPP */