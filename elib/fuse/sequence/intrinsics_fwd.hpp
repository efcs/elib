#ifndef ELIB_FUSE_SEQUENCE_INTRINSICS_FWD_HPP
#define ELIB_FUSE_SEQUENCE_INTRINSICS_FWD_HPP

# include <elib/utility.hpp>

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
        template <class Seq, class N>
        struct at;
        
        template <typename Seq, int N>
        struct at_c;
        
        template <class Seq>
        struct back;
        
        template <class Seq>
        struct begin;
        
        template <class Seq>
        struct empty;
        
        template <class Seq>
        struct end;
        
        template <class Seq>
        struct front;
        
        template <class Seq, class Key>
        struct has_key;
        
        template <class Seq>
        struct segments;
        
        template <class Seq>
        struct size;
        
        template <class Seq, class N>
        struct value_at;
        
        template <class Seq, int N>
        struct value_at_c;
        
        template <class Seq, class Key>
        struct at_key;
        
        template <class Seq, class N>
        struct value_at_key;
    }                                                       // namespace result_of
}                                                           // namespace elib
#endif /* ELIB_FUSE_SEQUENCE_INTRINSICS_FWD_HPP */