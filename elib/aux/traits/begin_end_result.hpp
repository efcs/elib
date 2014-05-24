#ifndef ELIB_AUX_TRAITS_BEGIN_END_RESULT_HPP
#define ELIB_AUX_TRAITS_BEGIN_END_RESULT_HPP

# include <elib/aux/traits/has_begin_end.hpp>
# include <elib/aux/declval.hpp>
# include <iterator>

namespace elib { namespace aux
{
    namespace traits
    {
        namespace traits_detail
        {
            namespace begin_end_adl_barrier
            {
                using std::begin;
                using std::end;
                
                template <class T>
                using begin_result_impl = decltype( begin(elib::declval<T>()) );
                
                template <class T>
                using end_result_impl = decltype( end(elib::declval<T>()) );
            }                                // namespace begin_end_adl_barrier
            
            using begin_end_adl_barrier::begin_result_impl;
            using begin_end_adl_barrier::end_result_impl;

        }                                            // namespace traits_detail
        
        ////////////////////////////////////////////////////////////////////////
        template <class T, bool = has_begin<T>::value>
        struct begin_result
        {
            using type = typename traits_detail::begin_result_impl<T>;
        };
        
        template <class T>
        struct begin_result<T, false>
        {
        };
        
        template <class T>
        using begin_result_t = typename begin_result<T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        template <class T, bool = has_end<T>::value>
        struct end_result
        {
            using type = typename traits_detail::end_result_impl<T>;
        };
        
        template <class T>
        struct end_result<T, false>
        {
        };
        
        template <class T>
        using end_result_t = typename end_result<T>::type;
    }                                                       // namespace traits
    
    using namespace traits;
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_BEGIN_END_RESULT_HPP */