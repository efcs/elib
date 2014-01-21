#ifndef ELIB_AUX_TUPLE_HPP
#define ELIB_AUX_TUPLE_HPP

# include <elib/aux/tuple_fwd.hpp>
# include <elib/aux/if.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/integer_sequence.hpp>
# include <elib/aux/logical.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/pair.hpp>
# include <elib/aux/swallow.hpp>
# include <elib/aux/type_traits.hpp>
# include <elib/params.hpp>
# include <array>
# include <functional>
# include <tuple>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    namespace tuple_detail
    {
        using std::swap;
        
        template <std::size_t I, class T, bool IsEmpty>
        struct tuple_item;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::swap(tuple_item)
        template <std::size_t I, class T, bool IsEmpty>
        inline void swap(tuple_item<I, T, IsEmpty> & lhs
                       , tuple_item<I, T, IsEmpty> & rhs)
        {
            swap(lhs.get(), rhs.get());
        }
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_item
        template <std::size_t I, class Type, bool IsEmpty>
        struct tuple_item
        {
        private:
            using value_type = Type;
            Type m_value;
            
            tuple_item& operator=(tuple_item const&) = delete;
            
        public:
            
            constexpr tuple_item() 
                    noexcept(is_nothrow_default_constructible<Type>::value)
              : m_value()
            {
                static_assert(
                    !is_ref<Type>::value_type
                  , "Attempting to default construct a reference element in a"
                    " tuple"
                );
            }
            
            constexpr tuple_item(tuple_item const& t) ELIB_NOEXCEPT_2(m_value(t.get()))
                : m_value(t.get())
            {
                static_assert(
                    !is_rvalue_ref<Type>::value_type
                  , "Cannot copy a tuple with a rvalue reference member"
                );
            }
            
            template <
                class T
              , ELIB_ENABLE_IF(is_constructible<Type, T>::value)
            >
            explicit constexpr tuple_item(T&& t) 
                    ELIB_NOEXCEPT_2(m_value(static_cast<T &&>(t)))
                : m_value(static_cast<T &&>(t))
            {
                static_assert(
                    or_<
                        not_<is_rvalue_ref<Type>>
                      , and_<
                            is_lvalue_ref<Type>
                          , or_<
                                is_lvalue_ref<T>
                              , is_same<
                                    remove_ref_t<T>
                                  , std::reference_wrapper< remove_ref_t<Type> >
                                >
                            >
                        >
                      , and_<
                            is_rvalue_ref<Type>
                        , not_<is_lvalue_ref<T>>
                        >
                    >::value
                    , " Attempted to construct a reference element in a tuple"
                      " with an rvalue"
                );
            }
            
            template <class T>
            explicit constexpr tuple_item(tuple_item<I, T> const& t)
                    ELIB_NOEXCEPT_2(m_value(t.get()))
                : m_value(t.get()) 
            {}
            
            template <class T>
            tuple_item& operator=(T && t) 
            {
                m_value = static_cast<T &&>(t);
                return *this;
            }
            
            int swap(tuple_item& t) noexcept(noexcept(tuple_detail::swap(*this, t)))
            {
                tuple_detail::swap(*this, t);
                return 1;
            }
            
            Type& get() noexcept
            { return m_value; }
            
            Type const& get() const noexcept
            { return m_value; }
        };
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_item (Empty base class optimization)
        template <std::size_t I, class Type>
        struct tuple_item<I, Type, true> 
          : private Type
        {
        private:
            using value_type = Type;
            
            tuple_item& operator=(tuple_item const&) = delete;
            
        public:
            
            constexpr tuple_item() noexcept {}
            
            constexpr tuple_item(tuple_item const& t) ELIB_NOEXCEPT_2(Type(t.get()))
              : Type(t.get())
            {
                static_assert(
                    !is_rvalue_ref<Type>::value
                  , "Cannot copy a tuple with rvalue refernce member"
                );
            }
            
            template <
                class T
              , ELIB_ENABLE_IF(is_constructible<Type, T>::value)
            >
            explicit constexpr tuple_item(T && t)
              : Type(static_cast<T &&>(t))
            {}
            
            template <class T>
            explicit constexpr tuple_item(tuple_item<I, T> const& t)
              : Type(t.get())
            {}
            
            template <class T>
            tuple_item& operator=(T && t)
            {
                Type::operator=(static_cast<T &&>(t));
                return *this;
            }
            
            int swap(tuple_item & t)
            {
                tuple_detail::swap(*this, t);
                return 1;
            }
            
            Type& get() noexcept
            {
                return static_cast<Type &>(*this);
            }
            
            Type const& get() const noexcept
            {
                return static_cast<Type const &>(*this);
            }
        };
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_indexes
        template <std::size_t ...I>
        struct tuple_indexes {};
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::make_tuple_indexes_impl
        template <std::size_t Start, class Indexes, std::size_t End>
        struct make_tuple_indexes_impl;
        
        template <std::size_t Start, std::size_t ...Indexes, std::size_t End>
        struct make_tuple_indexes_impl<Start, tuple_indexes<Indexes...>, End>
        {
            using type = typename
                make_tuple_indexes_impl< 
                    Start + 1
                  , tuple_indexes<Indexes..., Start>
                  , End
                >::type;
        };
        
        template <std::size_t End, std::size_t ...Indexes>
        struct make_tuple_indexes_impl<End, tuple_indexes<Indexes...>, End>
        {
            using type = tuple_indexes<Indexes...>;
        };
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::make_tuple_indexes
        template <std::size_t End, std::size_t Start = 0>
        struct make_tuple_indexes
        {
            using type = typename 
                make_tuple_indexes_impl<Start, tuple_indexes<>, End>::type;
                
            static_assert(
                Start <= End
              , "Invalid parameters for make_tuple_indexes"
            );
        };
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::make_tuple_indexes_t
        template <std::size_t End, std::size_t Start = 0>
        using make_tuple_indexes_t = typename make_tuple_indexes<End, Start>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_type
        template <class ...Types>
        struct tuple_types {};
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_size_impl
        template <class T>
        struct tuple_size_impl
          : std::tuple_size<T>
        {};
        
        template <class T>
        struct tuple_size_impl<T const>
          : tuple_size_impl<T>
        {};
        
        template <class T>
        struct tuple_size_impl<T volatile>
          : tuple_size_impl<T>
        {};
        
        template <class T>
        struct tuple_size_impl<T const volatile>
          : tuple_size_impl<T>
        {};
        
        template <class ...Types>
        struct tuple_size_impl< tuple_types<Types...> >
          : size_type_<sizeof...(Types)>
        {};
        
        template <class ...Types>
        struct tuple_size_impl< aux::tuple<Types...> >
          : size_type_<sizeof...(Types)>
        {};
        
        template <class First, class Second>
        struct tuple_size_impl< aux::pair<First, Second>>
          : size_type_<2>
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_element_impl
        template <std::size_t I, class T>
        struct tuple_element_impl
          : std::tuple_element<I, T>
        {};
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, tuple_types<Args...> >
          : params::at<tuple_types<Args...>, I>
        {};
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, aux::tuple<Args...>>
          : params::at<aux::tuple<Args...>, I>
        {};
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, aux::tuple<Args...> const>
        {
            using type = 
                add_const_t<
                    params::at_t<aux::tuple<Args...>, I>
                >;  
        };
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, aux::tuple<Args...> volatile>
        {
            using type =
                add_volatile_t<
                    params::at_t<aux::tuple<Args...>, I>
                >;
        };
        
        template <std::size_t I, class ...Args>
        struct tuple_element_impl<I, aux::tuple<Args...> const volatile>
        {
            using type = 
                add_cv_t<
                    params::at_t<aux::tuple<Args...>, I>
                  >;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, aux::pair<First, Second>>
        {
            using type = params::at_t<aux::pair<First, Second>, I>;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, aux::pair<First, Second> const>
        {
            using type = 
                add_const_t<
                    params::at_t<aux::pair<First, Second>, I>
                >;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, aux::pair<First, Second> volatile>
        {
            using type = 
                add_volatile_t<
                    params::at_t<aux::pair<First, Second>, I>
                >;
        };
        
        template <std::size_t I, class First, class Second>
        struct tuple_element_impl<I, aux::pair<First, Second> const volatile>
        {
            using type = 
                add_cv_t<
                    params::at_t<aux::pair<First, Second>, I>
                >;
        };
        
        template <std::size_t I, class T>
        using tuple_element_impl_t = typename tuple_element_impl<I, T>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::make_tuple_types_impl
        template <
            class TupleTypes, class Tuple
          , std::size_t Start, std::size_t End
        >
        struct make_tuple_types_impl;
        
        template <
            class ...Types, class Tuple
          , std::size_t Start, std::size_t End
        >
        struct make_tuple_types_impl<tuple_types<Types...>, Tuple, Start, End>
        {
            using TupleType = remove_ref_t<Tuple>;
            using ElementType =
                if_t<
                    is_lvalue_ref<Tuple>
                  , tuple_element_impl_t<Start, TupleType>&
                  , tuple_element_impl_t<Start, TupleType>
                  >;
            
            using type = typename
                make_tuple_types_impl<
                    tuple_types<Types..., ElementType>
                  , Tuple
                  , Start + 1, End
                >::type;
        };
        
        template <
            class ...Types, class Tuple
          , std::size_t End
        >
        struct make_tuple_types_impl<tuple_types<Types...>, Tuple, End, End>
        {
            using type = tuple_types<Types...>;
        };
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::make_tuple_types
        template <
            class Tuple
          , std::size_t End = tuple_size_impl<remove_ref_t<Tuple>>::value
          , std::size_t Start = 0
        >
        struct make_tuple_types
        {
            using type = typename
                make_tuple_types_impl<tuple_types<>, Tuple, Start, End>::type;
                
            static_assert( Start <= End, "make_tuple_types: invalid params");
        };
        
        template <
            class Tuple
          , std::size_t End = tuple_size_impl<remove_ref_t<Tuple>>::value
          , std::size_t Start = 0
        >
        using make_tuple_types_t = typename make_tuple_types<Tuple, End, Start>::type;
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_impl
        template <class Indexes, class ...Types>
        struct tuple_impl;
        
        template <std::size_t ...Indexes, class ...Types>
        struct tuple_impl< tuple_indexes<Indexes...>, Types...>
          : tuple_item<Indexes, Types>...
        {
            template <
                std::size_t ...I0, class ...Ts0
              , std::size_t ...I1, class ...Ts1
              , class ...ValueTypes
            >
            explicit tuple_impl(
                    tuple_indexes<I0...>, tuple_types<Ts0...>
                  , tuple_indexes<I1...>, tuple_types<Ts1...>
                  , ValueTypes &&... values)
                : tuple_item<I0, Ts0>(static_cast<ValueTypes &&>(values))...
                , tuple_item<I1, Ts1>()...
            {}
            
            template <class OtherT>
            tuple_impl(OtherT && t)
              : tuple_item<Indexes, Types>(
                    aux::forward<
                        tuple_element_impl_t<Indexes,  make_tuple_types_t<OtherT>>
                >(get<Indexes>(t)))...
            {}
            
            template <class OtherT>
            tuple_impl& operator=(OtherT && t)
            {
                swallow(
                    tuple_item<Indexes, Types>::operator=(
                        aux::forward<
                            tuple_element_impl_t<Indexes, make_tuple_types_t<OtherT>>
                        >(get<Indexes>(t))
                    )...
                  );
                return *this;
            }
            
            tuple_impl& operator=(tuple_impl const& t)
            {
                swallow(tuple_item<Indexes, Types>::operator=(
                    static_cast<tuple_item<Indexes, Types>& >(t).get()
                    )...
                );
                
                return *this;
            }
            
            void swap(tuple_impl & t)
            {
                swallow(tuple_item<Indexes, Types>::swap(
                    static_cast<tuple_item<Indexes, Types> &>(t)
                  )...
                );
            }
        };
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_like
        template <class T>
        struct tuple_like : false_
        {};
        
        template <class T>
        struct tuple_like<T const> : tuple_like<T>
        {};
        
        template <class T>
        struct tuple_like<T volatile> : tuple_like<T>
        {};
        
        template <class T>
        struct tuple_like<T const volatile> : tuple_like<T>
        {};
        
        template <class ...Ts>
        struct tuple_like<aux::tuple<Ts...>> : true_
        {};
        
        template <class ...Ts>
        struct tuple_like<tuple_types<Ts...>> : true_
        {};
        
        template <class First, class Second>
        struct tuple_like<aux::pair<First, Second>> : true_
        {};
        
        template <class ...Ts>
        struct tuple_like<std::tuple<Ts...>> : true_
        {};
        
        template <class First, class Second>
        struct tuple_like<std::pair<First, Second>> : true_
        {};
        
        template <class T, std::size_t N>
        struct tuple_like<std::array<T, N>> : true_
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_same_size
        template <class T, class U>
        using tuple_same_size = 
            bool_<
                tuple_size_impl<remove_ref_t<T>>::value
                  == tuple_size_impl<remove_ref_t<U>>::value
            >;
        
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
          , bool = tuple_like< remove_ref_t<From> >::value
          , bool = tuple_like< remove_ref_t<To> >::value
        >
        struct tuple_convertible : false_
        {};
        
        template <class From, class To>
        struct tuple_convertible<From, To, true, true>
          : tuple_convertible_impl<
                tuple_same_size<From, To>::value
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
          , bool = tuple_like< remove_ref_t<Target> >::value
          , bool = tuple_like< remove_ref_t<From> >::value
        >
        struct tuple_assignable : false_
        {};
        
        template <class Target, class From>
        struct tuple_assignable<Target, From, true, true>
          : tuple_assignable_impl<
              tuple_same_size<Target, From>::value
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
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple_size
    template <class T>
    struct tuple_size : tuple_detail::tuple_size_impl<T>
    {};
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple_element
    template <std::size_t I, class T>
    struct tuple_element : tuple_detail::tuple_element_impl<I, T>
    {};
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple
    template <class ...Types>
    struct tuple
    {
    private:
        using Impl = 
            tuple_detail::tuple_impl<
                tuple_detail::make_tuple_indexes_t<sizeof...(Types)>
              , Types...
            >;
        
        Impl m_impl;
        
        template <std::size_t I, class ...Ts>
        friend tuple_element_t<I, tuple<Ts...>>&
        get(tuple<Ts...> & t);
        
        template <std::size_t I, class ...Ts>
        friend tuple_element_t<I, tuple<Ts...>> const &
        get(tuple<Ts...> const& t);
        
        template <std::size_t I, class ...Ts>
        friend tuple_element_t<I, tuple<Ts...>>&&
        get_tuple(tuple<Ts...> && t);
        
    public:
        
        explicit tuple(Types const&... t)
          : m_impl(
                tuple_detail::make_tuple_indexes_t<sizeof...(Types)>()
              , tuple_detail::make_tuple_types_t<tuple, sizeof...(Types)>()
              , tuple_detail::make_tuple_indexes_t<0>()
              , tuple_detail::make_tuple_types_t<tuple, 0>()
              , t...
            )
        {}
        
        template <
            class ...Us
          , ELIB_ENABLE_IF(
                sizeof...(Us) <= sizeof...(Types) 
                && tuple_detail::tuple_convertible<
                        tuple_detail::make_tuple_types_t<tuple<Us...>>
                      , tuple_detail::make_tuple_types_t<tuple, 
                            sizeof...(Us) < sizeof...(Types)
                                ? sizeof...(Us)
                                : sizeof...(Types)
                        >
                    >::value
            )
        >
        explicit tuple(Us &&... t)
          : m_impl(
                tuple_detail::make_tuple_indexes_t<sizeof...(Us)>()
              , tuple_detail::make_tuple_types_t<tuple, sizeof...(Us)>()
              , tuple_detail::make_tuple_indexes_t<sizeof...(Types), sizeof...(Us)>()
              , tuple_detail::make_tuple_types_t<tuple, sizeof...(Types), sizeof...(Us)>()
              , static_cast<Us &&>(t)...
              )
            {}
        
        
        template <
            class OtherT
          , ELIB_ENABLE_IF(tuple_detail::tuple_convertible<OtherT, tuple>::value)
        >
        tuple(OtherT && t)
          : m_impl(static_cast<OtherT &&>(t))
        {}
        
        template <
            class OtherT
          , ELIB_ENABLE_IF(tuple_detail::tuple_assignable<OtherT, tuple>::value)
        >
        tuple& operator=(OtherT && t)
        {
            m_impl.operator=(static_cast<OtherT &&>(t));
            return *this;
        }
        
        void swap(tuple& t) noexcept(noexcept(m_impl.swap(t)))
        {
            m_impl.swap(t);
        }
    };
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::tuple<> (Empty)
    template <>
    struct tuple<>
    {
        tuple() noexcept {}
        
        template <
            class Other
          , ELIB_ENABLE_IF(tuple_detail::tuple_convertible<Other, tuple>::value)
        >
        tuple(Other &&)
        {}
        
        template <
            class Other
          , ELIB_ENABLE_IF(tuple_detail::tuple_assignable<Other, tuple>::value)
        >
        tuple& operator=(Other &&) noexcept
        { return *this; }
        
        void swap(tuple &)
        {}
    };
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::get(tuple)
    template <std::size_t I, class ...Ts>
    inline tuple_element_t<I, tuple<Ts...>>&
    get(tuple<Ts...> & t)
    {
        using Type = tuple_element_t<I, tuple<Ts...>>;
        return static_cast<tuple_detail::tuple_item<I, Type> &>(t.m_impl).get();
    }
    
    template <std::size_t I, class ...Ts>
    inline tuple_element_t<I, tuple<Ts...>> const &
    get(tuple<Ts...> const& t)
    {
        using Type = tuple_element_t<I, tuple<Ts...>>;
        return static_cast<tuple_detail::tuple_item<I, Type> const &>(t.m_impl).get();
    }
    
    template <std::size_t I, class ...Ts>
    inline tuple_element_t<I, tuple<Ts...>> &&
    get(tuple<Ts...> && t)
    {
        using Type = tuple_element_t<I, tuple<Ts...>>;
        return 
            static_cast<Type &&>(
                static_cast<tuple_detail::tuple_item<I, Type> &&>(t.m_impl).get()
            );
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::swap
    template <class ...Ts>
    inline void swap(tuple<Ts...> & lhs, tuple<Ts...> & rhs)
    {
        lhs.swap(rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator==, aux::operator!=
    template <class ...Ts1, class ...Ts2>
    inline bool operator==(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    {
        return tuple_detail::tuple_equal<sizeof...(Ts1)>()(t1, t2);
    }
    
    template <class ...Ts1, class ...Ts2>
    inline bool operator!=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    {
        return !(t1 == t2);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator<, aux::operator>
    template <class ...Ts1, class ...Ts2>
    inline bool operator<(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    {
        return tuple_detail::tuple_less<sizeof...(Ts1)>()(t1, t2);
    }
    
    template <class ...Ts1, class ...Ts2>
    inline bool operator>(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    {
        return t2 < t1;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // aux::operator<=, aux::operator>=
    template <class ...Ts1, class ...Ts2>
    inline bool operator<=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    {
        return !(t2 < t1);
    }
    
    template <class ...Ts1, class ...Ts2>
    inline bool operator>=(tuple<Ts1...> const& t1, tuple<Ts2...> const& t2)
    {
        return !(t1 < t2);
    }
    
    
}}                                                          // namespace elib
#endif /* ELIB_AUX_TUPLE_HPP */