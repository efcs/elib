#ifndef ELIB_AUX_TRAITS_HAS_BEGIN_END_HPP
#define ELIB_AUX_TRAITS_HAS_BEGIN_END_HPP

# include <elib/aux/declval.hpp>
# include <elib/aux/enable_if.hpp>
# include <elib/aux/integral_constant.hpp>
# include <iterator>

namespace elib { namespace aux
{

    namespace detail
    {
        namespace begin_end_adl_barrier
        {
            using std::begin;
            using std::end;
                
            template <class T>
            struct has_begin_impl
            {
            private:
                template <
                    class U
                  , ELIB_ENABLE_IF_VALID_EXPR( begin(elib::declval<U>()) )
                  >
                static elib::true_ test(int);
                    
                template <class>
                static elib::false_ test(long);
                    
            public:
                using type = decltype( test<T>(0) );
            };
                
            template <class T>
            struct has_end_impl
            {
            private:
                template <
                    class U
                  , ELIB_ENABLE_IF_VALID_EXPR( end(elib::declval<U>()) )
                  >
                static elib::true_ test(int);
                    
                template <class>
                static elib::false_ test(long);
                    
            public:
                using type = decltype( test<T>(0) );
            };
        }                                    // namespace begin_end_adl_barrier
            
            using begin_end_adl_barrier::has_begin_impl;
            using begin_end_adl_barrier::has_end_impl;
    }                                                       // namespace detail
        
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_begin = typename detail::has_begin_impl<T>::type;
        
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    using has_end = typename detail::has_end_impl<T>::type;

}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_HAS_BEGIN_END_HPP */