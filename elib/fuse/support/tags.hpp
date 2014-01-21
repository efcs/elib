#ifndef ELIB_FUSE_SUPPORT_TAGS_HPP
#define ELIB_FUSE_SUPPORT_TAGS_HPP

# include <elib/fuse/support/support_fwd.hpp>

namespace elib { namespace fuse
{
    ////////////////////////////////////////////////////////////////////////////
    // Tags
    struct non_fuse_tag {};
    
    struct sequence_facade_tag {};
    struct iterator_range_tag {};
    
    struct elib_tuple_tag {};
    struct elib_pair_tag {};
    struct std_array_tag {};
    struct std_tuple_tag {};
    struct std_pair_tag {};
    
    ////////////////////////////////////////////////////////////////////////////
    // Models
    namespace model
    {
        struct fuse_sequence {};
        
        struct incrementable {};
        struct single_pass : incrementable {};
        struct forward : single_pass {};
        struct bidirectional : forward {};
        struct random_access : bidirectional {};
    }                                                       // namespace model
}}                                                          // namespace elib
#endif /* ELIB_FUSE_SUPPORT_TAGS_HPP */