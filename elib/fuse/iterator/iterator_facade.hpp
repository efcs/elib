#ifndef ELIB_FUSE_ITERATOR_ITERATOR_FACADE_HPP
#define ELIB_FUSE_ITERATOR_ITERATOR_FACADE_HPP

# include <elib/fuse/iterator/iterator_fwd.hpp>
# include <elib/fuse/support/iterator_base.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/aux.hpp>

namespace elib { namespace fuse
{
    template <class Derived, class Category>
    struct iterator_facade : iterator_base<Derived>
    {
        using fuse_tag = iterator_facade_tag;
        using derived_type = Derived;
        using category = Category;
        
        template <class I1, class I2>
        using equal_to = 
            aux::is_same<
                typename I1::derived_type
              , typename I2::derived_type
            >;
            
        //TODO
        template <
            class It, class N
          , ELIB_ENABLE_IF(!traits::is_random_access<It>::value)
        >
        struct advance;
        
        //TODO
        template <class First, class Last>
        struct distance;
    };
}}                                                          // namespace elib
#endif /* ELIB_FUSE_ITERATOR_ITERATOR_FACADE_HPP */
