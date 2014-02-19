#ifndef ELIB_EXCEPT_FWD_HPP
#define ELIB_EXCEPT_FWD_HPP

# include <string>
# include <memory>
# include <typeinfo>
# include <cstdio>

# include <elib/tuple.hpp>

namespace elib { namespace except
{
    class exception;
    class unknown_exception;
    
    template <class Tag, class T> 
    class error_info;
    
    template <class E, class Tag, class T>
    E const & operator<<(E const &, error_info<Tag, T> const &);
    
    template <class E, class ...Tags, class ...Types>
    E const & operator<<(E const &, tuple<error_info<Tags, Types>...> const &);
    
    template <class E>
    E * current_exception_cast();
    
    template <class E>
    [[noreturn]] void throw_exception(E const &);
    
    template <class ErrorInfo, class E>
    typename ErrorInfo::error_info::value_type const * get_error_info(E const &);
    
    template <class ErrorInfo, class E>
    typename ErrorInfo::error_info::value_type * get_error_info(E &);
    
    namespace tags
    {
        struct api_function {};
        struct at_line {};
        struct errno_info {};
        struct file_handle {};
        struct file_name {};
        struct file_open_mode {};
        struct type_info_name {};
        struct original_exception_type {};
        
        struct throw_func {};
        struct throw_file {};
        struct throw_line {};
    }                                                       // namespace tags
    
    using throw_func = error_info<tags::throw_func, const char*>;
    using throw_file = error_info<tags::throw_file, const char*>;
    using throw_line = error_info<tags::throw_line, int>;
    
    using errinfo_api_function = error_info<tags::api_function, const char*>;
    using errinfo_at_line = error_info<tags::at_line, int>;
    using errinfo_errno = error_info<tags::errno_info, int>;
    using errinfo_file_handle = error_info<tags::file_handle, int>;
    using errinfo_file_name = error_info<tags::file_name, std::string>;
    using errinfo_file_open_mode = error_info<tags::file_open_mode, std::string>;
    using errinfo_type_info_name = error_info<tags::type_info_name, std::string>;
    
}}                                                          // namespace elib
#endif /* ELIB_EXCEPT_FWD_HPP */