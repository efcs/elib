#ifndef ELIB_RANGES_TRAITS_HPP
#define ELIB_RANGES_TRAITS_HPP

# include <elib/aux.hpp>
# include <elib/iterator/traits.hpp>

# include <array>
# include <string>
# include <vector>
# include <cstddef>

namespace elib { namespace ranges
{
    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <
            class T
          , bool = elib::and_<aux::has_begin<T>, aux::has_end<T>>::value
          >
        struct is_range_impl
        {
            using is_same_result_ = 
                aux::is_same<
                    aux::begin_result_t<T>
                  , aux::end_result_t<T>
                  >;
                
            using type = typename
              elib::and_<
                  is_same_result_
                , not_<aux::is_pointer<T>>
              >::type;
        };
            
        template <class T>
        struct is_range_impl<T, false>
        {
            using type = elib::false_;
        };
    }                                                       // namespace detail
        
    ////////////////////////////////////////////////////////////////////////
    template <class T>
    using is_range = typename detail::is_range_impl<T>::type;
    
    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <class T>
        struct is_contigious_range_impl : elib::false_ {};
        
        template <class T>
        struct is_contigious_range_impl<T &> : is_contigious_range_impl<T> {};
        
        template <class T>
        struct is_contigious_range_impl<T &&> : is_contigious_range_impl<T> {};
        
        template <class T>
        struct is_contigious_range_impl<T const> : is_contigious_range_impl<T> {};
        
        template <class T, std::size_t N>
        struct is_contigious_range_impl<T[N]> : elib::true_ {};
        
        template <class T, std::size_t N>
        struct is_contigious_range_impl<const T[N]> : elib::true_ {};
        
        template <class T, std::size_t N>
        struct is_contigious_range_impl<std::array<T, N>> : elib::true_ {};
        
        template <>
        struct is_contigious_range_impl<std::string> : elib::true_ {};
        
        template <class T, class Alloc>
        struct is_contigious_range_impl<std::vector<T, Alloc>> : elib::true_ {}; 
    }                                                       // namespace detail
        
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    struct is_contigious_range : detail::is_contigious_range_impl<T>::type
    {};
        
}}                                                          // namespace elib
namespace elib
{
    using ranges::is_range;
    using ranges::is_contigious_range;
}                                                           // namespace elib
#endif /* ELIB_RANGES_TRAITS_HPP */