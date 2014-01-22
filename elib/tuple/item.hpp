#ifndef ELIB_TUPLE_ITEM_HPP
#define ELIB_TUPLE_ITEM_HPP

# include <elib/config.hpp>
# include <elib/aux/tuple/fwd.hpp>
# include <elib/aux/integral_constant.hpp>
# include <elib/aux/move.hpp>
# include <elib/aux/no_decay.hpp>
# include <elib/aux/type_traits.hpp>
# include <utility>
# include <cstddef>

namespace elib { namespace aux
{
    namespace tuple_detail
    {
        using std::swap;
        
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
        // tuple_detail::swap(tuple_item)
        template <class Index, class T, bool IsEmpty>
        inline void swap(tuple_item<Index, T, IsEmpty> & lhs
                       , tuple_item<Index, T, IsEmpty> & rhs)
        {
            swap(lhs.get(), rhs.get());
        }
        
        ////////////////////////////////////////////////////////////////////////
        // tuple_detail::tuple_item
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
                    noexcept(is_nothrow_default_constructible<Type>::value)
              : m_value()
            {
                static_assert(
                    !is_ref<Type>::value
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
    }                                                       // namespace tuple_detail
}}                                                          // namespace elib
#endif /* ELIB_TUPLE_ITEM_HPP */