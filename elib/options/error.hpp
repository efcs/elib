#ifndef ELIB_OPTIONS_ERROR_HPP
#define ELIB_OPTIONS_ERROR_HPP

# include <elib/options/fwd.hpp>

namespace elib { namespace options
{
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
}}                                                          // namespace elib
#endif /* ELIB_OPTIONS_ERROR_HPP */