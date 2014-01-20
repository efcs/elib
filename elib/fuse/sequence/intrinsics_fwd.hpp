#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_FWD_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_FWD_HPP

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
        using at_ = typename at<Seq, N>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::at_c
        template <typename Seq, int N>
        struct at_c;
        
        template <class Seq, int N>
        using at_c_ = typename at_c<Seq, N>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::back
        template <class Seq>
        struct back;
        
        template <class Seq>
        using back_ = typename back<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::begin
        template <class Seq>
        struct begin;
        
        template <class Seq>
        using begin_ = typename begin<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::empty
        template <class Seq>
        struct empty;
        
        template <class Seq>
        using empty_ = typename empty<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::end
        template <class Seq>
        struct end;
        
        template <class Seq>
        using end_ = typename end<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::front
        template <class Seq>
        struct front;
        
        template <class Seq>
        using front_ = typename front<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::has_key
        template <class Seq, class Key>
        struct has_key;
        
        template <class Seq, class Key>
        using has_key_ = typename has_key<Seq, Key>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::segments
        template <class Seq>
        struct segments;
        
        template <class Seq>
        using segments_ = typename segments<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::size
        template <class Seq>
        struct size;
        
        template <class Seq>
        using size_ = typename size<Seq>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::value_at
        template <class Seq, class N>
        struct value_at;
        
        template <class Seq, class N>
        using value_at_ = typename value_at<Seq, N>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::value_at_c
        template <class Seq, int N>
        struct value_at_c;
        
        template <class Seq, int N>
        using value_at_c_ = typename value_at_c<Seq, N>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::at_key
        template <class Seq, class Key>
        struct at_key;
        
        template <class Seq, class Key>
        using at_key_ = typename at_key<Seq, Key>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // result_of::value_at_key
        template <class Seq, class N>
        struct value_at_key;
        
        template <class Seq, class N>
        using value_at_key_ = typename value_at_key<Seq, N>::type;
    }                                                       // namespace result_of
    

}}                                                          // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_FWD_HPP */