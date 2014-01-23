#ifndef ELIB_FUSE_ITERATOR_EQUAL_TO_HPP
#define ELIB_FUSE_ITERATOR_EQUAL_TO_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/fuse/support/traits.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag>
        struct equal_to_impl
        {
            template <class I1, class I2>
            using apply = aux::is_same< aux::add_const_t<I1>, aux::add_const_t<I2> >;
        };
        
        template <>
        struct equal_to_impl<iterator_facade_tag>
        {
            template <
                class It1, class It2
              , bool = aux::is_same<
                  typename It1::fuse_tag
                , typename It2::fuse_tag
                >::value
            >
            struct dispatch : false_ {};
            
            template <class It1, class It2>
            struct dispatch<It1, It2, true>
              : It1::template equal_to_impl<It1, It2>
            {};
            
            template <class It1, class It2>
            using apply = dispatch<It1, It2>;
        };
        
        template <> struct equal_to_impl<elib_pair_iterator_tag>;
        template <> struct equal_to_impl<elib_tuple_iterator_tag>;
        template <> struct equal_to_impl<std_pair_iterator_tag>;
        template <> struct equal_to_impl<std_tuple_iterator_tag>;
        template <> struct equal_to_impl<std_array_iterator_tag>;
    }                                                       // namespace extension
    
    namespace result_of
    {
        template <class It1, class It2>
        struct equal_to
          : extension::equal_to_impl< detail::get_tag_of_t<It1> >
                ::template apply<It1, It2>
        {};
    }                                                       // namespace result_of
    
    namespace iterator_operators
    {
        template <
            class It1, class It2
          , ELIB_ENABLE_IF(is_fuse_iterator<It1>::value
                         && is_fuse_iterator<It2>::value)
        >
        constexpr bool operator==(It1 const&, It2 const&)
        {
            return result_of::equal_to<It1, It2>::value;
        }
        
        template <
            class It1, class It2
          , ELIB_ENABLE_IF(is_fuse_iterator<It1>::value
                         && is_fuse_iterator<It2>::value)
        >
        constexpr bool operator!=(It1 const&, It2 const&)
        {
            return !result_of::equal_to<It1, It2>::value;
        }
    }                                           // namespace iterator_operators
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_EQUAL_TO_HPP */