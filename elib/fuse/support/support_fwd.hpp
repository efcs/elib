#ifndef ELIB_FUSE_SUPPORT_SUPPORT_FWD_HPP
#define ELIB_FUSE_SUPPORT_SUPPORT_FWD_HPP

# define ELIB_FUSE_SUPPORT_EXPO 0

namespace elib { namespace fuse
{
    ////////////////////////////////////////////////////////////////////////////
    // tags
    struct non_fuse_tag;
    
    struct sequence_facade_tag;
    struct iterator_range_tag;
    
    struct elib_tuple_tag;
    struct elib_pair_tag;
    struct std_array_tag;
    struct std_tuple_tag;
    struct std_pair_tag;
    
    namespace model
    {
        struct fuse_sequence;
        
        struct incrementable;
        struct single_pass;
        struct forward;
        struct bidirectional;
        struct random_access;
        struct associative;
    }                                                       // namespace model

    namespace extension
    {
        ////////////////////////////////////////////////////////////////////////
        // category_of_impl
        template <class T>
        struct category_of_impl;
        
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
        // is_segmented_impl
        template <class T>
        struct is_segmented_impl;
        
        template <>
        struct is_segmented_impl<sequence_facade_tag>;
        
        template <>
        struct is_segmented_impl<iterator_range_tag>;
        
        ////////////////////////////////////////////////////////////////////////
        // extension::is_sequence_impl
        template <class T>
        struct is_sequence_impl;
        
        template <>
        struct is_sequence_impl<non_fuse_tag>;
        
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
        template <class T>
        struct is_view_impl;
        
        template <>
        struct is_view_impl<sequence_facade_tag>;
        
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
    
    namespace detail
    {
        template <class T, class Active>
        struct tag_of_impl;
        
        template <class T>
        struct normalized_tag_of;
        
        template <class T>
        using normalized_tag_of_t = typename normalized_tag_of<T>::type;
        
        template <class T>
        struct fuse_tag_detector;
    }                                                       // namespace detail
    
    namespace traits
    {
        template <class T>
        struct has_fuse_tag;
        
        template <class T>
        struct fuse_category_of;
        
        template <class T>
        using fuse_category_of_t = typename fuse_category_of<T>::type;
        
        template <class T>
        struct is_fuse_iterator;
        
        template <class T, class Enable = void>
        struct is_native_fuse_sequence;
        
        template <class T>
        struct fuse_is_view;
        
        
        template <class T>
        struct category_of;
        
        template <class T>
        using category_of_t = typename category_of<T>::type;
        
        
        template <class T, class Active = void>
        struct tag_of;
        
        template <class T, class Active = void>
        using tag_of_t = typename tag_of<T, Active>::type;
        
        
        template <class T>
        struct is_associative;
        
        template <class T>
        struct is_incrementable;
        
        template <class T>
        struct is_single_pass;
        
        template <class T>
        struct is_forward;
        
        template <class T>
        struct is_bidirectional;
        
        template <class T>
        struct is_random_access;
        
        template <class T>
        struct is_segmented;
        
        template <class T>
        struct is_sequence;
        
        template <class T>
        struct is_view;
        
        template <class T>
        struct deduce;
    
        template <class T>
        struct deduce_sequence;
    }                                                       // namespace traits
    
   
    
    struct iterator_root;
    
    template <class Iter>
    struct iterator_base;
    
    template <class T>
    struct is_fuse_iterator;
    
    namespace result_of
    {
        template <class Seq, class State, class Fn>
        struct segmented_fold_until;
        
        template <class Seq, class State, class Fn>
        using segmented_fold_until_t = typename 
            segmented_fold_until<Seq, State, Fn>::type;
    }                                                       // namespace result_of
    
# if ELIB_FUSE_SUPPORT_EXPO
    template <class Seq, class State, class Fn>
        result_of::segmented_fold_until_t<Seq, State, Fn>
    segmented_fold_until(Seq & seq,  State const& state, Fn const& fn);
    
    template <class Seq, class State, class Fn>
        result_of::segmented_fold_until_t<Seq, State, Fn>
    segmented_fold_until(Seq const& seq, State const& state, Fn const& fn);
# endif
    
    namespace detail
    {
        struct from_sequence_convertible_type;
    }                                                       // namespace detail
    
    template <class Seq>
    struct sequence_base;
    
    struct unused_type;
    
    namespace detail
    {
        struct unused_only;
    }                                                       // namespace detail
    
# if ELIB_FUSE_SUPPORT_EXPO
    constexpr std::ostream& 
    operator<<(std::ostream & out, detail::unused_only const&) noexcept;
    
    constexpr std::istream& operator>>(std::istream&, unused_type&) noexcept;
# endif

}}                                                          // namespace elib
#endif /* ELIB_FUSE_SUPPORT_SUPPORT_FWD_HPP */