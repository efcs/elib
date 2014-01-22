#ifndef ELIB_TUPLE_HELPER_HPP
#define ELIB_TUPLE_HELPER_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/is_tuple_like.hpp>
# include <elib/tuple/tuple_types.hpp>
# include <elib/aux.hpp>
# include <cstddef>

namespace elib { namespace aux
{
    namespace tuple_detail
    {
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_convertible_impl
        template <bool IsSameSize, class From, class To>
        struct tuple_convertible_impl : false_
        {};
        
        template <class ...From, class ...To>
        struct tuple_convertible_impl<true, tuple_types<From...>, tuple_types<To...>>
          : and_< true_, true_, is_convertible<From, To>... >
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_convertible
        template <
            class From, class To
          , bool /* = is_tuple_like<From>::value */
          , bool /* = is_tuple_like<To>::value */
        >
        struct tuple_convertible : false_
        {};
        
        template <class From, class To>
        struct tuple_convertible<From, To, true, true>
          : tuple_convertible_impl<
                is_tuple_same_size<From, To>::value
              , make_tuple_types_t<From>
              , make_tuple_types_t<To>
            >
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_assignable_impl
        template <bool IsSameSize, class Target, class From>
        struct tuple_assignable_impl : false_
        {};
        
        template <class ...Target, class ...From>
        struct tuple_assignable_impl<true, tuple_types<Target...>, tuple_types<From...>>
          : and_< true_, true_, is_assignable<Target, From>... >
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_assignable
        template <
            class Target, class From
          , bool /* = is_tuple_like<Target>::value */
          , bool /* = is_tuple_like<From>::value */
        >
        struct tuple_assignable : false_
        {};
        
        template <class Target, class From>
        struct tuple_assignable<Target, From, true, true>
          : tuple_assignable_impl<
              is_tuple_same_size<Target, From>::value
            , make_tuple_types_t<Target>
            , make_tuple_types_t<From>
          >
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_equal
        template <std::size_t I>
        struct tuple_equal
        {
            template <class Tp1, class Tp2>
            bool operator()(Tp1 const& t1,  Tp2 const& t2)
            {
                return tuple_equal<I - 1>()(t1, t2) &&
                    (get<I - 1>(t1) == get<I - 1>(t2));
            }
        };
        
        template <>
        struct tuple_equal<0>
        {
            template <class Tp1, class Tp2>
            bool operator()(Tp1 const&, Tp2 const&) noexcept
            { return true; }
        };
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_less
        template <std::size_t I>
        struct tuple_less
        {
            template <class Tp1, class Tp2>
            bool operator()(Tp1 const& t1, Tp2 const& t2)
            {
                return tuple_less<I-1>()(t1, t2)
                        || (!tuple_less<I-1>()(t2, t1) 
                            && get<I-1>(t1) < get<I-1>(t2)
                          );
            }
        };
        
        template <>
        struct tuple_less<0>
        {
            template <class Tp1, class Tp2>
            bool operator()(Tp1 const&, Tp2 const&) noexcept
            { return false; }
        };
    }                                                       // namespace tuple_detail
}}                                                          // namespace elib
# endif /* ELIB_TUPLE_HELPER_HPP */