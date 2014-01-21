#ifndef ELIB_FUSE_SUPPORT_TRAITS_HPP
#define ELIB_FUSE_SUPPORT_TRAITS_HPP

# include <elib/fuse/support/support_fwd.hpp>
# include <elib/fuse/support/iterator_base.hpp>
# include <elib/fuse/support/sequence_base.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/type_traits.hpp>
# include <functional>

namespace elib { namespace fuse
{
    namespace detail
    {
        template <class T>
        struct fuse_tag_detector
        {
            template <class U>
            static aux::true_ test(typename U::fuse_tag*);
            
            template <class>
            static aux::false_ test(...);
        
            using type = decltype( test<T>(nullptr) );
        };
    }                                                       // namespace detail
    
    namespace traits
    {
        template <class T>
        struct has_fuse_tag
          : detail::fuse_tag_detector<T>::type
        {};
        
        template <class T>
        struct fuse_category_of
        {
            using type = typename T::category;
        };
        
        template <class T>
        struct is_fuse_iterator
          : aux::is_base_of<iterator_root, T>
        {};
        
        template <class Seq, class Enable /* = void */>
        struct is_native_fusion_sequence
          : aux::is_convertible<Seq, detail::from_sequence_convertible_type>
        {};
        
        template <class T>
        struct fuse_is_view
          : T::is_view
        {};
    }                                                       // namespace traits
    
    namespace detail
    {
        template <class T>
        struct normalized_tag_of
            : traits::tag_of< aux::remove_const_t<T> >
        {};
        
        // TODO
        // fix for mpl sequences? 
        template <class T, class Enable>
        struct tag_of_impl
        {
            using type = non_fuse_tag;
        };
        
        template <class T>
        struct tag_of_impl<T, aux::enable_if_t<traits::has_fuse_tag<T>>>
        {
            using type = typename T::fuse_tag;
        };
    }                                                       // namespace detail
    
    namespace extension
    {
        ////////////////////////////////////////////////////////////////////////
        // extension::category_of_impl
        template <class Tag>
        struct category_of_impl
        {
            template <class T>
            using apply = traits::fuse_category_of<T>;
        };
        
        template <>
        struct category_of_impl<elib_tuple_tag>;
        
        template <>
        struct category_of_impl<elib_pair_tag>;
        
        template <>
        struct category_of_impl<std_array_tag>;
        
        template <>
        struct category_of_impl<std_tuple_tag>;
        
        template <>
        struct category_of_impl<std_pair_tag>;
        
        ////////////////////////////////////////////////////////////////////////
        // extension::is_segmented_impl
        template <class Tag>
        struct is_segmented_impl
        {
            template <class Seq>
            struct apply : aux::false_
            {};
        };
        
        template <>
        struct is_segmented_impl< sequence_facade_tag >
        {
            template <class Seq>
            using apply = typename Seq::is_segmented;
        };
        
        template <>
        struct is_segmented_impl<iterator_range_tag>;
        
        ////////////////////////////////////////////////////////////////////////
        // extension::is_sequence_impl
        template <class T>
        struct is_sequence_impl
        {
            template <class Seq>
            using apply = 
                aux::is_convertible<Seq, detail::from_sequence_convertible_type>;
        };
        
        template <>
        struct is_sequence_impl<non_fuse_tag>
        {
            template <class T>
            struct apply : aux::false_
            {};
        };
        
        template <>
        struct is_sequence_impl<elib_tuple_tag>;
        
        template <>
        struct is_sequence_impl<elib_pair_tag>;
        
        template <>
        struct is_sequence_impl<std_array_tag>;
        
        template <>
        struct is_sequence_impl<std_tuple_tag>;
        
        template <>
        struct is_sequence_impl<std_pair_tag>;
        
        ////////////////////////////////////////////////////////////////////////
        // extension::is_view_impl
        template <class Tag>
        struct is_view_impl
        {
            template <class T>
            using apply = traits::fuse_is_view<T>;
        };
        
        template <>
        struct is_view_impl< sequence_facade_tag >
        {
            template <class Seq>
            using apply = typename Seq::is_view;
        };
        
        template <>
        struct is_view_impl<elib_tuple_tag>;
        
        template <>
        struct is_view_impl<elib_pair_tag>;
        
        template <>
        struct is_sequence_impl<std_array_tag>;
        
        template <>
        struct is_view_impl<std_tuple_tag>;
        
        template <>
        struct is_view_impl<std_pair_tag>;
    }                                                       // namespace extension
    
    namespace traits
    {
        template <class T>
        struct category_of
          : extension::category_of_impl< detail::normalized_tag_of_t<T> >
                ::template apply<T>
        {};
        
        template <class Seq, class Enable /* = void */>
        struct tag_of
          : detail::tag_of_impl<Seq, Enable>
        {};
        
        template <class T>
        struct is_associative
          : aux::is_base_of< model::associative, category_of_t<T> >
        {};
        
        template <class T>
        struct is_incrementable
          : aux::is_base_of< model::incrementable, category_of_t<T> >
        {};
        
        template <class T>
        struct is_single_pass
          : aux::is_base_of< model::single_pass, category_of_t<T> >
        {};
        
        template <class T>
        struct is_forward
          : aux::is_base_of< model::forward, category_of_t<T> >
        {};
        
        template <class T>
        struct is_bidirectional
          : aux::is_base_of< model::bidirectional, category_of_t<T> >
        {};
        
        template <class T>
        struct is_random_access
          : aux::is_base_of< model::random_access, category_of_t<T> >
        {};
        
        template <class T>
        struct is_segmented
          : aux::bool_cast<typename
                extension::is_segmented_impl<traits::tag_of_t<T>>
                  ::template apply<T>
            >
        {};
        
        template <class T>
        struct is_sequence
          : aux::bool_cast<typename
                extension::is_segmented_impl<detail::normalized_tag_of_t<T>>
                  ::template apply<T>
            >
        {};
        
        template <class T>
        struct is_view
          : aux::bool_cast<typename
                extension::is_view_impl<detail::normalized_tag_of_t<T>>
                  ::template apply<T>
          >
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // traits::deduce
        template <class T>
        struct deduce
        {
            using type = T;
        };
        
        template <class T>
        struct deduce<T const>
        {
            using type = T;
        };
        
        template <class T>
        struct deduce<T volatile>
        {
            using type = T;
        };
        
        template <class T>
        struct deduce<T const volatile>
        {
            using type = T;
        };
        
        template <class T>
        struct deduce<T &>
        {
            using type = T &;
        };
        
        template <class T>
        struct deduce<T volatile &>
        {
            using type = T volatile &;
        };
        
        template <class T>
        struct deduce<T const &>
        {
            using type = T;
        };
        
        template <class T>
        struct deduce<T const volatile &>
        {
            using type = T;
        };
        
        template <class T>
        struct deduce<std::reference_wrapper<T> &>
        {
            using type = T &;
        };
        
        template <class T>
        struct deduce<std::reference_wrapper<T> const &>
        {
            using type = T &;
        };
        
        template <class T, int N>
        struct deduce<T(&)[N]>
        {
            using type = T(&)[N];
        };
        
        template <class T, int N>
        struct deduce<volatile T(&)[N]>
        {
            using type = volatile T(&)[N];
        };
        
        template <class T, int N>
        struct deduce<const T(&)[N]>
        {
            using type = const T(&)[N];
        };
        
        template <class T, int N>
        struct deduce<const volatile T(&)[N]>
        {
            using type = const volatile T(&)[N];
        };
    }                                                       // namespace traits
    
    namespace detail
    {
        struct deducer
        {
            template <class Sig>
            struct result;
            
            template <class Self, class T>
            struct result< Self(T) >
              : traits::deduce<T>
            {};
            
            template <class T>
            typename result< deducer(T) >::type
            operator()(T&&) const;
        };
    }                                                       // namespace detail
    
    namespace traits
    {
        //TODO
        template <class Seq>
        struct deduce_sequence;
    }                                                       // namespace traits
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SUPPORT_TRAITS_HPP */