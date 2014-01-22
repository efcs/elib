#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_FWD_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_FWD_HPP

# include <elib/fuse/support/traits.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    namespace extension
    {
        template <class Tag> 
        struct at_impl;
        
        template <class Tag> 
        struct begin_impl;
        
        template <class Tag> 
        struct empty_impl;
        
        template <class Tag> 
        struct end_impl;
        
        template <class Tag> 
        struct has_key_impl;
        
        template <class Tag> 
        struct segments_impl;
        
        template <class Tag> 
        struct size_impl;
        
        template <class Tag> 
        struct value_at_impl;
        
        template <class Tag> 
        struct key_at_impl;
        
        template <class Tag> 
        struct value_at_key_impl;
    }                                                       // namespace extension
    
    namespace result_of
    {
        ////////////////////////////////////////////////////////////////////////
        // result_of::at
        template <class Seq, class N>
        struct at;
        
        template <class Seq, class N>
        using at_t = typename at<Seq, N>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::at_c
        template <typename Seq, int N>
        struct at_c;
        
        template <class Seq, int N>
        using at_c_t = typename at_c<Seq, N>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::back
        template <class Seq>
        struct back;
        
        template <class Seq>
        using back_t = typename back<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::begin
        template <class Seq>
        struct begin;
        
        template <class Seq>
        using begin_t = typename begin<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::empty
        template <class Seq>
        struct empty;
        
        template <class Seq>
        using empty_t = typename empty<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::end
        template <class Seq>
        struct end;
        
        template <class Seq>
        using end_t = typename end<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::front
        template <class Seq>
        struct front;
        
        template <class Seq>
        using front_t = typename front<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::has_key
        template <class Seq, class Key>
        struct has_key;
        
        template <class Seq, class Key>
        using has_key_t = typename has_key<Seq, Key>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::segments
        template <class Seq>
        struct segments;
        
        template <class Seq>
        using segments_t = typename segments<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::size
        template <class Seq>
        struct size;
        
        template <class Seq>
        using size_t = typename size<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::value_at
        template <class Seq, class N>
        struct value_at;
        
        template <class Seq, class N>
        using value_at_t = typename value_at<Seq, N>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::value_at_c
        template <class Seq, int N>
        struct value_at_c;
        
        template <class Seq, int N>
        using value_at_c_t = typename value_at_c<Seq, N>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::at_key
        template <class Seq, class Key>
        struct at_key;
        
        template <class Seq, class Key>
        using at_key_t = typename at_key<Seq, Key>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::value_at_key
        template <class Seq, class N>
        struct value_at_key;
        
        template <class Seq, class N>
        using value_at_key_t = typename value_at_key<Seq, N>::type;
    }                                                       // namespace result_of
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::at(seq)
    template <class N, class Seq>
    constexpr 
        aux::lazy_disable_if_t<
            aux::is_const<Seq>
          , result_of::at<Seq, N>
        >
    at(Seq& seq);
    
    template <class N, class Seq>
    constexpr result_of::at_t<Seq const, N>
    at(Seq const& seq);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::at_c(seq)
    template <int N, class Seq>
    constexpr 
        aux::lazy_disable_if_t<
            aux::is_const<Seq>
          , result_of::at_c<Seq, N>
        >
    at_c(Seq & seq);
    
    template <int N, class Seq>
    constexpr result_of::at_c_t<Seq const, N>
    at_c(Seq const& seq);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::back(seq)
    template <class Seq>
    constexpr result_of::back_t<Seq>
    back(Seq & seq);
    
    template <class Seq>
    constexpr result_of::back_t<Seq const>
    back(Seq const& seq);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::begin(seq)
    template <class Seq>
    constexpr
        aux::lazy_enable_if_t<
            traits::is_sequence<Seq>
          , result_of::begin<Seq>
        > const
    begin(Seq & seq);
    
    template <class Seq>
    constexpr
        aux::lazy_enable_if_t<
            traits::is_sequence<Seq>
          , result_of::begin<Seq const>
        > const
    begin(Seq const& seq);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::empty(seq)
    template <class Seq>
    constexpr result_of::empty_t<Seq>
    empty(Seq const&);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::end(seq)
    template <class Seq>
    constexpr
        aux::lazy_enable_if_t<
            traits::is_sequence<Seq>
          , result_of::end<Seq>
        > const
    end(Seq & seq);
    
    template <class Seq>
    constexpr
        aux::lazy_enable_if_t<
            traits::is_sequence<Seq>
          , result_of::end<Seq const>
        > const
    end(Seq const& seq);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::front(seq)
    template <class Seq>
    constexpr result_of::front_t<Seq>
    front(Seq & seq);
    
    template <class Seq>
    constexpr result_of::front_t<Seq const>
    front(Seq const& seq);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::has_key(seq)
    template <class Key, class Seq>
    constexpr result_of::has_key_t<Seq, Key>
    has_key(Seq const& seq);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::segments(seq)
    template <class Seq>
    constexpr
        aux::lazy_disable_if_t<
            aux::is_const<Seq>
          , result_of::segments<Seq>
        >
    segments(Seq & seq);
    
    template <class Seq>
    constexpr result_of::segments_t<Seq const>
    segments(Seq const& seq);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::size(seq)
    template <class Seq>
    constexpr result_of::size_t<Seq>
    size(Seq const& seq);
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::at_key(seq)
    template <class Key, class Seq>
    constexpr
        aux::lazy_disable_if_t<
            aux::is_const<Seq>
          , result_of::at_key<Seq, Key>
        >
    at_key(Seq & seq);
    
    template <class Key, class Seq>
    constexpr result_of::at_key_t<Seq const, Key>
    at_key(Seq const& seq);
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_FWD_HPP */