#ifndef ELIB_FUSE_DETAIL_ACCESS_HPP
#define ELIB_FUSE_DETAIL_ACCESS_HPP

# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    namespace detail
    {
        template <class T>
        struct call_param
        {
            using type = T const &;
        };
        
        template <class T>
        struct call_param<T &>
        {
            using type = T &;
        };
        
        template <class T>
        struct call_param<T const>
        {
            using type = T const &;
        };
        
        template <class T>
        struct call_param<T volatile>
        {
            using type = T const &;
        };
        
        template <class T>
        struct call_param<T const volatile>
        {
            using type = T const &;
        };
        
        template <class T>
        using call_param_ = typename call_param<T>::type;
    }                                                       // namespace detail
}}                                                          // namespace elib
#endif /* ELIB_FUSE_DETAIL_ACCESS_HPP */