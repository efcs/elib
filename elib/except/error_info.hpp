#ifndef ELIB_EXCEPT_ERROR_INFO_HPP
#define ELIB_EXCEPT_ERROR_INFO_HPP

# include <elib/except/fwd.hpp>
# include <elib/tuple.hpp>

namespace elib { namespace except
{
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class Tag, class T> 
    class error_info;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class E, class Tag, class T>
    void set_error_info(E const &, error_info<Tag, T> const &);
    
    template <class E, class ...Tags, class ...Types>
    void set_error_info(E const &, elib::tuple<error_info<Tags, Types>...> const &);
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class ErrorInfo, class E>
    typename ErrorInfo::error_info::value_type const * get_error_info(E const &);
    
    template <class ErrorInfo, class E>
    typename ErrorInfo::error_info::value_type * get_error_info(E &);
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class E, class Tag, class T>
    E const & operator<<(E const &, error_info<Tag, T> const &);
    
    template <class E, class ...Tags, class ...Types>
    E const & operator<<(E const &, elib::tuple<error_info<Tags, Types>...> const &);
}}                                                          // namespace elib
#endif /* ELIB_EXCEPT_ERROR_INFO_HPP */