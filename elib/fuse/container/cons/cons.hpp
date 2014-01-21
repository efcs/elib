#ifndef ELIB_FUSE_CONTAINER_CONS_CONS_HPP
#define ELIB_FUSE_CONTAINER_CONS_CONS_HPP

# include <elib/fuse/container/cons/cons_fwd.hpp>
# include <elib/fuse/support/sequence_base.hpp>
# include <elib/fuse/support/tags.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/type_traits.hpp>
# include <elib/aux/none.hpp>

namespace elib { namespace fuse 
{
    struct cons_tag
    {};
    
    struct cons_model
      : model::fuse_sequence
      , model::single_pass
    {};
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::cons_nil
    struct cons_nil
      : sequence_base< cons_nil >
    {
        using size = aux::size_type_<0>;
        using fuse_tag = cons_tag;
        using category = cons_model;
        
        using front_type = aux::none;
        using back_type = aux::none;
        
        cons_nil() noexcept
        {}
        
        template <class Iter>
        cons_nil(Iter const&, aux::true_)
        {}
        
        template <class Iter>
        void assign_from_iter(Iter const&)
        {}
    };
    
    ////////////////////////////////////////////////////////////////////////////
    // fuse::cons
    template <class Front, class Back /* = cons_nil */>
    struct cons
      : sequence_base< cons<Front, Back> >
    {
        using size = aux::size_type_<Back::size::value + 1>;
        using fuse_tag = cons_tag;
        using category = cons_model;
        using front_type = Front;
        using back_type = Back;
        
        Front front;
        Back back;
        
        cons() noexcept(aux::is_nothrow_default_constructible<Front>::value
                     && aux::is_nothrow_default_constructible<Back>::value)
          : front(), back()
        {}
        
        explicit cons(Front f) 
            : front(f), back()
        {}
        
        explicit cons(Front && f)
            : front(aux::move(f)), back()
        {}
        
        cons(Front f, Back b)
            : front(f), back(b)
        {}
        
        cons(Front && f, Back && b)
          : front(aux::move(f)), back(aux::move(b))
        {}
        
        cons(
        
    };
          
}}                                                          // namespace elib
#endif /* ELIB_FUSE_CONTAINER_CONS_CONS_HPP */