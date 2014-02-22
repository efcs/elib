#ifndef ELIB_ANY_HPP
#define ELIB_ANY_HPP

# include <elib/aux.hpp>
# include <typeinfo>
# include <utility>

namespace elib 
{
////////////////////////////////////////////////////////////////////////////////
//                              Forward
////////////////////////////////////////////////////////////////////////////////
    class bad_any_cast;
    
    class any;
    
    void swap(any &, any &) noexcept;
    
    template <class To> 
    To any_cast(any const &);
    
    template <class To> 
    To any_cast(any &);
    
    template <class ValueType> 
    ValueType const* any_cast(any const *) noexcept;
    
    template <class ValueType> 
    ValueType * any_cast(any *) noexcept;
    
////////////////////////////////////////////////////////////////////////////////
//                              bad_any_cast
////////////////////////////////////////////////////////////////////////////////

# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class bad_any_cast : public std::bad_cast
    {
    public:
        virtual const char * what() const noexcept
        {
            return "elib::bad_any_cast: failed conversion using elib::any_cast";
        }
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
////////////////////////////////////////////////////////////////////////////////
//                                  Any
////////////////////////////////////////////////////////////////////////////////
    
    class any
    {
    public:
        any() noexcept : m_holder(nullptr) {}
        
        template <
            class ValueType
          , ELIB_ENABLE_IF(!aux::is_same<ValueType, any>::value)
        >
        any(ValueType const & val) 
          : m_holder(new holder<ValueType>(val))
        {}
        
        
        any(any const & other)
          : m_holder(other.m_holder ? other.m_holder->copy() : nullptr)
        {}
        
        any(any && other) noexcept
          : m_holder(other.m_holder)
        {
            other.m_holder = nullptr;
        }
        
        template <
            class ValueType
          , ELIB_ENABLE_IF(!aux::is_same<any&, ValueType>::value)
        >
        any(ValueType && val)
          : m_holder(
              new holder< aux::remove_reference_t<ValueType> >(
                  static_cast<ValueType &&>(val)
            ))
        {
            using unref = aux::remove_reference_t<ValueType>;
            static_assert(
                !aux::is_reference<unref>::value
              , "ValueType is still reference after remove_reference_t"
            );
        }
        
        ~any() noexcept
        {
            delete m_holder;
        }
        
        any & swap(any & other) noexcept
        {
            std::swap(m_holder, other.m_holder);
            return *this;
        }
        
        any & operator=(any const & rhs)
        {
            any(rhs).swap(*this);
            return *this;
        }
        
        any & operator=(any && rhs) noexcept
        {
            rhs.swap(*this);
            any().swap(rhs);
            return *this;
        }
        
        template <class ValueType>
        any & operator=(ValueType && rhs)
        {
            any(static_cast<ValueType &&>(rhs)).swap(*this);
            return *this;
        }
        
        bool empty() const noexcept
        { return !m_holder; }
        
        operator bool() const noexcept
        { return m_holder; }
        
        std::type_info const & type() const
        {
            return m_holder ? m_holder->type() : typeid(void);
        }
        
    private:
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
        ////////////////////////////////////////////////////////////////////////
        //
        class basic_holder
        {
        public:
            virtual ~basic_holder() {}
            
            virtual std::type_info const & type() const = 0;
            virtual basic_holder * copy() const = 0;
        };
        
        ////////////////////////////////////////////////////////////////////////
        //
        template <class ValueType>
        class holder : public basic_holder
        {
            static_assert(
                !aux::is_same<aux::uncvref<ValueType>, holder>::value
              , "cannot store holder in holder"
            );
        public:
            using value_type = ValueType;
            
            holder(ValueType const & val)
              : m_value(val)
            {}
            
            holder(ValueType && val)
              : m_value(static_cast<ValueType &&>(val))
            {}
            
            holder & operator=(holder const &) = delete;
            holder & operator=(holder &&) = delete;
            
            virtual std::type_info const & type() const
            {
                return typeid(ValueType);
            }
            
            virtual basic_holder * copy() const
            {
                return new holder(m_value);
            }
            
            ValueType m_value;
        };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
        
    private: /* friends */
        
        template <class ValueType>
        friend ValueType * any_cast(any *) noexcept;
        
    private: /* fields */
        basic_holder * m_holder;
    };                                                      // class any
    
    
    ////////////////////////////////////////////////////////////////////////////
    //
    inline void swap(any & lhs, any & rhs) noexcept
    {
        lhs.swap(rhs);
    }
        
////////////////////////////////////////////////////////////////////////////////
//                                any_cast
////////////////////////////////////////////////////////////////////////////////

    template <class To> 
    To any_cast(any const & v)
    {
        using type = aux::remove_reference_t<To>;
        return any_cast<type const &>(const_cast<any &>(v));
        
        static_assert(
            !aux::is_reference<type>::value
          , "type is still reference after remove_reference_t"
        );
    }
    
    template <class To> 
    To any_cast(any & v)
    {
        using type = aux::remove_reference_t<To>;
        
        type * ret = any_cast<type>(&v);
        if (!ret) throw bad_any_cast();
            
        return *ret;
        
        static_assert(
            !aux::is_reference<type>::value
          , "type is still reference after remove_reference_t"
        );
    }
    
    template <class ValueType> 
    ValueType const* any_cast(any const * v) noexcept
    {
        return any_cast<ValueType>(const_cast<any *>(v));
    }
    
    template <class ValueType> 
    ValueType * any_cast(any * v) noexcept
    {
        if (!v || v->type() != typeid(ValueType))
            return nullptr;
        
        return elib::addressof(
            static_cast<any::holder<ValueType> *>(v->m_holder)->m_value
          );
    }
}                                                          // namespace elib
#endif /* ELIB_ANY_HPP */