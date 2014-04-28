#ifndef ELIB_AUX_BEGIN_END_HPP
#define ELIB_AUX_BEGIN_END_HPP

/// This header provides helpers for working with begin and end. There are three
/// primary helpers: get_begin, try_get_begin, and adl_begin
/// (and their 'end' counter parts)
/// get_begin<T>: 
///    Return: a functor that can be used to invoke begin on type T
///    Note: get_begin fails to compile if there is no call to begin for T
/// try_get_begin<T>: 
///    Return: a functor pointer that invokes begin on a type or nullptr
///            if begin(T) is ill-formed. This can be used to determine if T
///            has a begin method at runtime
/// adl_begin(T):
///    Return: the result of calling begin(T) on a overload set that includes
///            std::begin and begin looked up by ADL.
# include <elib/aux/declval.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/forward.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/traits/has_begin_end.hpp>
# include <elib/aux/traits/begin_end_result.hpp>
# include <iterator>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T, bool = has_begin<T>::value>
        struct get_begin_type_impl
        {
            using type = begin_result_t<T>(*)(T &&);
        };
        
        template <class T>
        struct get_begin_type_impl<T, false>
        {
            using type = void(*)();
        };
        
        template <class T, bool = has_end<T>::value>
        struct get_end_type_impl
        {
            using type = end_result_t<T>(*)(T &&);
        };
        
        template <class T>
        struct get_end_type_impl<T, false>
        {
            using type = void(*)();
        };
    }                                                       // namespace detail
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using get_begin_t = typename detail::get_begin_type_impl<T>::type;
    
    template <class T>
    using get_end_t = typename detail::get_end_type_impl<T>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <
            class T
          , ELIB_ENABLE_IF(has_begin<T>::value)
          >
        get_begin_t<T> get_begin_impl(int)
        {
            static auto get_fn = 
            [](T && v) 
            { 
                using std::begin;
                return begin(elib::forward<T>(v)); 
            };
            
            return get_fn;
        }
        
        template <class T>
        get_begin_t<T> get_begin_impl(long)
        {
            return ((get_begin_t<T>)nullptr);
        }
        
        template <
            class T
          , ELIB_ENABLE_IF(has_end<T>::value)
          >
        get_end_t<T> get_end_impl(int)
        {
            static auto get_fn = 
            [](T && v) 
            { 
                using std::end;
                return end(elib::forward<T>(v)); 
            };
            
            return get_fn;
        }
        
        template <class T>
        get_end_t<T> get_end_impl(long)
        {
            return ((get_end_t<T>)nullptr);
        }
    }                                                       // namespace detail
   
    ////////////////////////////////////////////////////////////////////////////
    template <class T, ELIB_ENABLE_IF(has_begin<T>::value)>
    get_begin_t<T> get_begin(T &&)
    {
        return detail::get_begin_impl<T>(0);
    }
    
    template <class T, ELIB_ENABLE_IF(has_end<T>::value)>
    get_end_t<T> get_end(T &&)
    {
        return detail::get_end_impl<T>(0);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    get_begin_t<T> get_begin_ptr(T &&)
    {
        return detail::get_begin_impl<T>(0);
    }
    
    template <class T>
    get_end_t<T> get_end_ptr(T &&)
    {
        return detail::get_end_impl<T>(0);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    begin_result_t<T> adl_begin(T && t)
    {
        using std::begin;
        return begin(elib::forward<T>(t));
    }
    
    template <class T>
    end_result_t<T> adl_end(T && t)
    {
        using std::end;
        return end(elib::forward<T>(t));
    }
}}                                                          // namespace elib
namespace elib
{
    using aux::get_begin_t;
    using aux::get_end_t;
    using aux::get_begin;
    using aux::get_end;
    using aux::get_begin_ptr;
    using aux::get_end_ptr;
    using aux::adl_begin;
    using aux::adl_end;
}                                                           // namespace elib
#endif /* ELIB_AUX_BEGIN_END_HPP */