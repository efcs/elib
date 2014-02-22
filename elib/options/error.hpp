#ifndef ELIB_OPTIONS_ERROR_HPP
#define ELIB_OPTIONS_ERROR_HPP

# include <elib/options/fwd.hpp>
# include <elib/aux.hpp>
# include <stdexcept>

namespace elib { namespace options
{
    /** base class for all errors */
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class error : public std::logic_error
    {
    public:
        using std::logic_error::logic_error;
        ELIB_DEFAULT_COPY_MOVE(error);
        virtual ~error() noexcept {}
    };
    
    /** error parsing option name */
    class option_name_error : public error
    {
    public:
        using error::error;
        ELIB_DEFAULT_COPY_MOVE(option_name_error);
        virtual ~option_name_error() noexcept {}
    };
    
    /** duplicate option name in options_description */
    class duplicate_option_error : public error
    {
    public:
        using error::error;
        ELIB_DEFAULT_COPY_MOVE(duplicate_option_error);
        virtual ~duplicate_option_error() noexcept {}
    };
    
    /** A options has multiple values specified for it */
    class multiple_values_error : public error
    {
    public:
        using error::error;
        ELIB_DEFAULT_COPY_MOVE(multiple_values_error);
        virtual ~multiple_values_error() noexcept {}
    };
    
    /** An opption has been specified multiple times */
    class multiple_occurrences_error : public error
    {
    public:
        using error::error;
        ELIB_DEFAULT_COPY_MOVE(multiple_occurrences_error);
        virtual ~multiple_occurrences_error() noexcept {}
    };
    
    /** A required option has not been specified */
    class required_option_error : public error
    {
    public:
        using error::error;
        ELIB_DEFAULT_COPY_MOVE(required_option_error);
        virtual ~required_option_error() noexcept {}
    };
    
    /** an unknown option has been specified */
    class unknown_option_error : public error
    {
    public:
        using error::error;
        ELIB_DEFAULT_COPY_MOVE(unknown_option_error);
        virtual ~unknown_option_error() noexcept {}
    };
    
    class ambiguous_option_error;
    class command_line_syntax_error;
    class validation_error;
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
}}                                                          // namespace elib
#endif /* ELIB_OPTIONS_ERROR_HPP */