#ifndef ELIB_AUX_TUPLE_ELIB_PAIR_HPP
#define ELIB_AUX_TUPLE_ELIB_PAIR_HPP

# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/tuple/apply_tuple.hpp>
# include <elib/aux/tuple/piecewise_construct.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/type_traits.hpp>
# include <elib/functional.hpp>
# include <utility>

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
    // aux::pair
    template <class First, class Second>
    struct pair
    {
        using first_type = First;
        using second_type = Second;
        
        First first;
        Second second;
        
        constexpr pair() 
                noexcept(is_nothrow_default_constructible<First>::value
                      && is_nothrow_default_constructible<Second>::value)
          : first(), second()
        {
            static_assert(
                !is_ref<First>::value && !is_ref<Second>::value
              , "Attempting to default construct a reference type in pair"
            );
        }
        
        constexpr pair(const First& f, const Second& s)
                noexcept(is_nothrow_copy_constructible<First>::value
                      && is_nothrow_copy_constructible<Second>::value)
            : first(f), second(s)
        {}
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value
                        && is_convertible<Second, U>::value)
        >
        constexpr pair(T && t, U && u) 
            : first(static_cast<T &&>(t))
            , second(static_cast<U &&>(u))
        {}
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value
                        && is_convertible<Second, U>::value)
        >
        constexpr pair( pair<T, U> const& p) 
            : first(p.first), second(p.second)
        {}
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value
                        && is_convertible<Second, U>::value)
        >
        constexpr pair( pair<T, U> && p )
            : first(aux::move(p.first)), second(aux::move(p.second))
        {}
        
        template <class ...Args1, class ...Args2>
        pair( piecewise_construct_t, 
              tuple<Args1...> first_args
            , tuple<Args2...> second_args )
          : first{ apply_tuple(functional::construct<First>{}, first_args) }
          , second{ apply_tuple(functional::construct<Second>{}, second_args) }
        {}
        
        template <class ...Args1, class ...Args2>
        pair( std::piecewise_construct_t
              , std::tuple<Args1...> first_args
              , std::tuple<Args2...> second_args)
          : first{ apply_tuple(functional::construct<First>{}, first_args) }
          , second{ apply_tuple(functional::construct<Second>{}, second_args) }
        {}
        
        pair( pair const& ) = default;
        pair( pair&& ) = default;
        
        pair& operator=( pair const& p ) 
                noexcept(is_nothrow_copy_assignable<First>::type
                      && is_nothrow_copy_assignable<Second>::type)
        {
            if (this != &p)
            {
                first = p.first;
                second = p.second;
            }
            return *this;
        }
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value
                        && is_convertible<Second, U>::value)
        >
        pair& operator=( pair<T, U> const& p)
        {
            first = p.first;
            second = p.second;
            return *this;
        }
        
        pair& operator=(pair && p)
                noexcept(is_nothrow_move_assignable<First>::value
                      && is_nothrow_move_assignable<Second>::value)
        
        {
            first = aux::move(p.first);
            second = aux::move(p.second);
            return *this;
        }
        
        template <
            class T, class U
          , ELIB_ENABLE_IF(is_convertible<First, T>::value 
                        && is_convertible<Second, U>::value)
        >
        pair& operator=(pair<T, U> && p)
        {
            first = aux::move(p.first);
            second = aux::move(p.second);
        }
        
        void swap(pair& p) 
                noexcept(noexcept(std::swap(first, p.first))
                      && noexcept(std::swap(second, p.second)))
        {
            std::swap(first, p.first);
            std::swap(second, p.second);
        }
    };
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_ELIB_PAIR_HPP */