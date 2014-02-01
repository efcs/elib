#ifndef ELIB_TUPLE_BITS_TUPLE_IMPL_HPP
#define ELIB_TUPLE_BITS_TUPLE_IMPL_HPP

# include <elib/tuple/fwd.hpp>
# include <elib/tuple/bits/tuple_element_impl.hpp>
# include <elib/tuple/bits/tuple_indexes.hpp>
# include <elib/tuple/bits/tuple_types.hpp>
# include <elib/tuple/bits/unique_value_helper.hpp>
# include <elib/aux.hpp>
# include <utility>
# include <cstddef>

namespace elib { namespace tuples
{
    namespace detail
    {
        
        template <class Index, class T, bool IsEmpty>
        struct tuple_item;
        
        template <class T>
        struct is_tuple_item : false_
        {};
        
        template <class Index, class T, bool IsEmpty>
        struct is_tuple_item< tuple_item<Index, T, IsEmpty> >
          : true_
        {};
        
        ////////////////////////////////////////////////////////////////////////
        // detail::swap(tuple_item)
        template <class Index, class T, bool IsEmpty>
        inline void swap(tuple_item<Index, T, IsEmpty> & lhs
                       , tuple_item<Index, T, IsEmpty> & rhs)
        {
            using std::swap;
            swap(lhs.get(), rhs.get());
        }
        
        ////////////////////////////////////////////////////////////////////////
        // detail::tuple_item
        template <class Index, class Type, bool IsEmpty>
        struct tuple_item
        {
        private:
            Type m_value;
            
            tuple_item& operator=(tuple_item const&) = delete;
            
            /* since we allow for explicit conversions to type, we need
             * to disallow recursive storage
             */
            static_assert(
                !is_tuple_item<Type>::value
              , "cannot store a tuple item in a tuple item"
              );
        public:
            
            using index = Index;
            using value_type = Type;
            
            constexpr tuple_item() 
                    noexcept(aux::is_nothrow_default_constructible<Type>::value)
              : m_value()
            {
                static_assert(
                    !aux::is_ref<Type>::value
                  , "Attempting to default construct a reference element in a"
                    " tuple"
                );
            }
            
            constexpr tuple_item(tuple_item const& t) ELIB_NOEXCEPT(m_value(t.get()))
                : m_value(t.get())
            {
                static_assert(
                    !aux::is_rvalue_ref<Type>::value_type
                  , "Cannot copy a tuple with a rvalue reference member"
                );
            }
            
            template <
                class T
              , ELIB_ENABLE_IF(aux::is_constructible<Type, T>::value)
            >
            explicit constexpr tuple_item(T&& t) 
                : m_value(static_cast<T &&>(t))
            {
                static_assert(
                    or_<
                        not_<aux::is_rvalue_ref<Type>>
                      , and_<
                            aux::is_lvalue_ref<Type>
                          , or_<
                                aux::is_lvalue_ref<T>
                              , aux::is_same<
                                    aux::remove_ref_t<T>
                                  , std::reference_wrapper< aux::remove_ref_t<Type> >
                                >
                            >
                        >
                      , and_<
                            aux::is_rvalue_ref<Type>
                        , not_<aux::is_lvalue_ref<T>>
                        >
                    >::value
                    , " Attempted to construct a reference element in a tuple"
                      " with an rvalue"
                );
            }
            
            template <class T>
            explicit constexpr tuple_item(tuple_item<Index, T> const& t)
                : m_value(t.get()) 
            {}
            
            template <class T>
            tuple_item& operator=(T && t) 
            {
                m_value = static_cast<T &&>(t);
                return *this;
            }
            
            int swap(tuple_item& t) noexcept
            {
                detail::swap(*this, t);
                return 1;
            }
            
            Type& get() noexcept
            { return m_value; }
            
            constexpr Type const& get() const noexcept
            { return m_value; }

            
        };
        
        ////////////////////////////////////////////////////////////////////////
        // detail::tuple_item (Empty base class optimization)
        template <class Index, class Type>
        struct tuple_item<Index, Type, true> 
          : private Type
        {
        private:
            
            tuple_item& operator=(tuple_item const&) = delete;
            
        public:
            
            using index = Index;
            using value_type = Type;
            
            constexpr tuple_item() noexcept {}
            
            constexpr tuple_item(tuple_item const& t) ELIB_NOEXCEPT(Type(t.get()))
              : Type(t.get())
            {
                static_assert(
                    !aux::is_rvalue_ref<Type>::value
                  , "Cannot copy a tuple with rvalue refernce member"
                );
            }
            
            template <
                class T
              , ELIB_ENABLE_IF(aux::is_constructible<Type, T>::value)
            >
            explicit constexpr tuple_item(T && t)
              : Type(static_cast<T &&>(t))
            {}
            
            template <class T>
            explicit constexpr tuple_item(tuple_item<Index, T> const& t)
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
                detail::swap(*this, t);
                return 1;
            }
            
            Type& get()  noexcept
            {
                return static_cast<Type &>(*this);
            }
            
            constexpr Type const& get() const  noexcept
            {
                return static_cast<Type const &>(*this);
            }
            
        };
        
        ////////////////////////////////////////////////////////////////////////
        // detail::tuple_impl
        template <class Indexes, class ...Types>
        struct tuple_impl;
        
        template <std::size_t ...Indexes, class ...Types>
        struct tuple_impl< tuple_indexes<Indexes...>, Types...>
          : tuple_item_c<Indexes, Types>...
        {
            ////////////////////////////////////////////////////////////////////
            // item_at_index_lookup
            template <class Index, class Value>
            static tuple_item<Index, Value>
            item_at_index_lookup(tuple_item<Index, Value> const&);
            
            template <class Index>
            static aux::none item_at_index_lookup(...);
            
            ////////////////////////////////////////////////////////////////////
            //
            template <std::size_t Index>
            struct item_at_index
            {
                using result = decltype(
                    item_at_index_lookup<size_type_<Index>>(std::declval<tuple_impl>())
                );
                
                static_assert(
                    !aux::is_same<result, aux::none>::value
                  , "Index lookup failed"
                  );
                
                using type = typename result::value_type;
                using index = typename result::index;
                
                static constexpr type& call(tuple_impl& im) noexcept
                {
                    return static_cast<type &>(
                        static_cast<result &>(im).get()
                      );
                }
                
                static constexpr type const & call(tuple_impl const& im) noexcept
                {
                    return static_cast<type const &>(
                            static_cast<result const&>(im).get()
                        );
                }
                
                static constexpr type && call(tuple_impl && im) noexcept
                {
                    return static_cast<type &&>(
                                static_cast<result &&>(im).get()
                            );
                }
            };
            
            ////////////////////////////////////////////////////////////////////
            //
            template <class Value, class Index>
            static tuple_item<Index, Value>
            item_at_value_lookup(tuple_item<Index, Value> const&);
            
            template<class Value>
            static aux::none item_at_value_lookup(...);
            
            ////////////////////////////////////////////////////////////////////
            //
            template <class Value>
            struct item_at_value
            {
                using result = decltype(
                    item_at_value_lookup<Value>(std::declval<tuple_impl>())
                  );
                
                static_assert( 
                    !aux::is_same<result, aux::none>::value
                  , "item at value lookup failed"
                  );
                
                using type = typename result::value_type;
                using index = typename result::index;
                
                static_assert(
                    is_unique_value<
                        index::value, Value
                      , tuple_indexes<Indexes...>
                      , tuple_types<Types...>
                    >::value
                  , "item_at_value: duplicates in tuple"
                );
                
                static constexpr type& call(tuple_impl & im) noexcept
                {
                    return static_cast<type &>(
                            static_cast<result &>(im).get()
                      );
                }
                
                static constexpr type const& call(tuple_impl const& im) noexcept
                {
                    return static_cast<type const &>(
                        static_cast<result const &>(im).get()
                      );
                }
                
                static constexpr type && call(tuple_impl && im) noexcept
                {
                    return static_cast<type &&>(
                        static_cast<result &&>( std::move(im) ).get()
                      );
                }
            };
            
            ////////////////////////////////////////////////////////////////////
            //
            template <class Key, class Index, class Value>
            static tuple_item<Index, pair<Key, Value>>
            item_at_key_lookup(tuple_item<Index, pair<Key, Value>> const&);
            
            template <class Key>
            static aux::none item_at_key_lookup(...);
            
            ////////////////////////////////////////////////////////////////////
            //
            template <class Key>
            struct item_at_key
            {
                using result = decltype(
                    item_at_key_lookup<Key>(std::declval<tuple_impl>())
                  );
                
                static_assert( 
                    !aux::is_same<result, aux::none>::value
                  , "item at key lookup failed"
                  );
                
                using type = typename result::value_type;
                using index = typename result::index;
                
                static_assert(
                    is_unique_key<
                          index::value, Key
                        , tuple_indexes<Indexes...>
                        , tuple_types<Types...>
                    >::value
                    , "item_at_key:: duplicates in tuple"
                 );
                
                static constexpr type& call(tuple_impl & im) noexcept
                {
                    return static_cast<type &>(
                            static_cast<result &>(im).get()
                      );
                }
                
                static constexpr type const& call(tuple_impl const& im) noexcept
                {
                    return static_cast<type const &>(
                        static_cast<result const &>(im).get()
                      );
                }
                
                static constexpr type && call(tuple_impl && im) noexcept
                {
                    return static_cast<type &&>(
                        static_cast<result &&>( std::move(im) ).get()
                      );
                }
            };
            
            template <
                std::size_t ...I0, class ...Ts0
              , std::size_t ...I1, class ...Ts1
              , class ...ValueTypes
            >
            explicit tuple_impl(
                    tuple_indexes<I0...>, tuple_types<Ts0...>
                  , tuple_indexes<I1...>, tuple_types<Ts1...>
                  , ValueTypes &&... values)
                : tuple_item_c<I0, Ts0>(static_cast<ValueTypes &&>(values))...
                , tuple_item_c<I1, Ts1>()...
            {}
            
            template <class OtherT>
            tuple_impl(OtherT && t)
              : tuple_item_c<Indexes, Types>(
                    elib::forward<
                        tuple_element_impl_t<Indexes,  make_tuple_types_t<OtherT>>
                    >(get<Indexes>(t))
                )...
            {}
            
            template <class OtherT>
            tuple_impl& operator=(OtherT && t)
            {
                swallow(
                    tuple_item_c<Indexes, Types>::operator=(
                        elib::forward<
                            tuple_element_impl_t<Indexes, make_tuple_types_t<OtherT>>
                        >(get<Indexes>(t))
                    )...
                  );
                return *this;
            }
            
            tuple_impl& operator=(tuple_impl const& t)
            {
                swallow(tuple_item_c<Indexes, Types>::operator=(
                    static_cast<tuple_item_c<Indexes, Types>& >(t).get()
                    )...
                );
                
                return *this;
            }
            
            void swap(tuple_impl & t)
            {
                swallow(tuple_item_c<Indexes, Types>::swap(
                    static_cast<tuple_item_c<Indexes, Types> &>(t)
                  )...
                );
            }
        };
    }                                                       // namespace detail
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_BITS_TUPLE_IMPL_HPP */