#ifndef ELIB_FUSE_CONTAINER_CONS_CONS_FWD_HPP
#define ELIB_FUSE_CONTAINER_CONS_CONS_FWD_HPP

namespace elib { namespace fuse
{
    struct cons_tag;
    
    struct cons_model;
    
    struct cons_nil;
    
    template <class Front, class Back = cons_nil>
    struct cons;
}}                                                          // namespace elib
#endif /* ELIB_FUSE_CONTAINER_CONS_CONS_FWD_HPP */