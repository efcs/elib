#ifndef ELIB_ANY_HPP
#define ELIB_ANY_HPP

# include <elib/aux.hpp>
# include <elib/compressed_pair.hpp>
# include <elib/memory/allocator_destructor.hpp>
# include <memory> /* for allocator_arg_t, std::unique_ptr */
# include <new>
# include <typeinfo>

namespace elib
{

# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    ////////////////////////////////////////////////////////////////////////////
    class bad_any_cast : std::bad_cast
    {
    public:
        bad_any_cast() noexcept 
        {}
        
        virtual const char* what() const noexcept
        {
            return "bad any cast";
        }
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
    namespace detail
    {
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
        ////////////////////////////////////////////////////////////////////////
        struct any_storage_base
        {
            any_storage_base() = default;
            any_storage_base(any_storage_base const &) = delete;
            any_storage_base(any_storage_base &&) = delete;
            
            virtual ~any_storage_base() { }
            
            virtual any_storage_base* copy() const = 0;
            virtual any_storage_base* copy(void*) const = 0;
            virtual any_storage_base* move(void*) = 0;
            
            virtual void destroy() noexcept = 0;
            virtual void destroy_deallocate() noexcept = 0;
            
            virtual void* target() const noexcept = 0;
            virtual void* target_if(std::type_info const &) const noexcept = 0;
            virtual std::type_info const & target_type() const noexcept = 0;
        };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
                
        ////////////////////////////////////////////////////////////////////////
        template <
            class ValueType
          , class Alloc = std::allocator<ValueType>
          >
        struct any_storage_type : public any_storage_base
        {
        public:
            using value_type = ValueType;
            using allocator_type = Alloc;
            
        public:
            any_storage_type(ValueType const & v)
              : m_pair(v, Alloc())
            {}
            
            any_storage_type(ValueType && v)
              : m_pair(elib::move(v), Alloc())
            {}
            
            any_storage_type(ValueType const & v, Alloc const & a)
              : m_pair(v, a)
            {}
            
    
            any_storage_type(ValueType && v, Alloc const & a)
              : m_pair(elib::move(v), a)
            {}
            
        public:
            any_storage_base* copy() const
            {
                using NewAlloc = typename Alloc::template rebind<any_storage_type>::other;
                NewAlloc a(m_pair.second());
                using Dtor = allocator_destructor<NewAlloc>;
                
                std::unique_ptr<any_storage_type, Dtor> tmp(
                    a.allocate(1), Dtor(a, 1)
                  );
                ::new ((void*)tmp.get()) any_storage_type(
                    m_pair.first(), Alloc(a)
                  );
                return tmp.release();
            }
            
            any_storage_base* copy(void* dest) const
            {
                return 
                  ::new (dest) any_storage_type(
                    m_pair.first()
                  , m_pair.second()
                  );
            }
            
            any_storage_base* move(void* dest)
            {
                return 
                  ::new (dest) any_storage_type(
                    elib::move(m_pair.first())
                  , elib::move(m_pair.second())
                  );
            }
            
            void destroy() noexcept
            {
                m_pair.~compressed_pair<ValueType, Alloc>();
            }
            
            void destroy_deallocate() noexcept
            {
                using NewAlloc = typename 
                    Alloc::template rebind<any_storage_type>::other;
                NewAlloc a(m_pair.second());
                m_pair.~compressed_pair<ValueType, Alloc>();
                a.deallocate(this, 1);
            }
            
            void* target() const noexcept
            {
                return static_cast<void*>(
                    const_cast<ValueType*>(elib::addressof(m_pair.first()))
                  );
            }
            
            void* target_if(std::type_info const & info) const noexcept
            {
                return info == typeid(ValueType) ? target() : nullptr;
            }
            
            std::type_info const & target_type() const noexcept
            {
                return typeid(ValueType);
            }
            
        private:
            elib::compressed_pair<ValueType, Alloc> m_pair;
        };
        
        ////////////////////////////////////////////////////////////////////////
        using any_buffer_t = aux::aligned_storage_t<3*sizeof(void*)>;
        
        ////////////////////////////////////////////////////////////////////////
        template <class StorageType>
        using store_locally = 
        elib::and_c<
            sizeof(StorageType) <= sizeof(any_buffer_t)
          , aux::alignment_of<any_buffer_t>::value 
                % std::alignment_of<StorageType>::value == 0
          , aux::is_nothrow_move_constructible<typename StorageType::value_type>::value
        >;
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    class any
    {
    public:
        ////////////////////////////////////////////////////////////////////////
        any() noexcept
          : m_store_ptr(nullptr)
        {}
        
        ////////////////////////////////////////////////////////////////////////
        any(any const & other)
          : m_store_ptr(nullptr)
        {
            if (other.m_stored_locally()) {
                m_store_ptr = other.m_store_ptr->copy((void*)&m_buff);
            }
            else if (other.m_stored_remotely()) {
                m_store_ptr = other.m_store_ptr->copy();
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        any(any && other)
          : m_store_ptr(nullptr)
        {
            if (other.m_stored_locally()) {
                m_store_ptr = other.m_store_ptr->move((void*)&m_buff);
            } 
            else if (other.m_stored_remotely()) {
                m_store_ptr = other.m_store_ptr;
                other.m_store_ptr = nullptr;
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class ValueType
          , ELIB_ENABLE_IF(not aux::is_same<aux::decay_t<ValueType>, any>::value)
          >
        any(ValueType && value)
          : m_store_ptr(nullptr)
        {
            using StoredValue = aux::decay_t<ValueType>;
            using Storage = any_storage_type<StoredValue>;
            
            if (store_locally<Storage>::value) {
                m_store_ptr = ::new ((void*)&m_buff) Storage(
                    elib::forward<ValueType>(value)
                  );
            } else {
                using Alloc = typename Storage::allocator_type::template rebind<Storage>::other;
                using Dtor = allocator_destructor<Alloc>;
                Alloc a;
                std::unique_ptr<Storage, Dtor> tmp(a.allocate(1), Dtor(a, 1));
                ::new ((void*)tmp.get()) Storage(
                    elib::forward<ValueType>(value)
                  , typename Storage::allocator_type(a)
                  );
                m_store_ptr = tmp.release();
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class Allocator>
        any(std::allocator_arg_t, Allocator const &) noexcept
          : m_store_ptr(nullptr)
        {}
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class Allocator, class ValueType
          , ELIB_ENABLE_IF(not aux::is_same<aux::decay_t<ValueType>, any>::value)
          >
        any(std::allocator_arg_t, Allocator const & alloc, ValueType && value)
          : m_store_ptr(nullptr)
        {
            using StoredValue = aux::decay_t<ValueType>;
            using StoredAlloc = typename Allocator::template 
                rebind<StoredValue>::other;
            using Storage = any_storage_type<StoredValue, StoredAlloc>;
            
            if (store_locally<Storage>::value) {
                m_store_ptr = ::new ((void*)&m_buff) Storage(
                    elib::forward<ValueType>(value)
                  , StoredAlloc(alloc)
                  );
            } else {
                using OtherAlloc = typename Allocator::template
                    rebind<Storage>::other;
                using Dtor = allocator_destructor<OtherAlloc>;
                
                OtherAlloc a(alloc);
                std::unique_ptr<Storage, Dtor> tmp(
                    a.allocate(1), Dtor(a, 1)
                  );
                ::new ((void*)tmp.get()) Storage(
                    elib::forward<ValueType>(value)
                  , StoredAlloc(a)
                  );
                m_store_ptr = tmp.release();
            }
        }
        
        ~any()
        {
            clear();
        }
        
        any & operator=(any const & other)
        {
            any(other).swap(*this);
            return *this;
        }
        
        any & operator=(any && other) noexcept
        {
            clear();
            if (other.m_stored_locally()) {
                m_store_ptr = other.m_store_ptr->move((void*)&m_buff);
            } 
            else if (other.m_stored_remotely()) {
                m_store_ptr = other.m_store_ptr;
                other.m_store_ptr = nullptr;
            }
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class ValueType
          , ELIB_ENABLE_IF(not aux::is_same<aux::decay_t<ValueType>, any>::value)
          >
        any & operator=(ValueType && value)
        {
            any(elib::forward<ValueType>(value)).swap(*this);
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        void clear() noexcept
        {
            if (m_stored_locally()) {
                m_store_ptr->destroy();
            }
            else if (m_stored_remotely()) {
                m_store_ptr->destroy_deallocate();
            } 
            m_store_ptr = nullptr;
        }
        
        ////////////////////////////////////////////////////////////////////////
        void swap(any & other) noexcept
        {
            // both objects are local
            if (m_stored_locally() && other.m_stored_locally()) {
                // move our value to tmp_buff, destroy our value
                any_buffer_t tmp_buff;
                any_storage_base* tmp_ptr = m_store_ptr->move((void*)&tmp_buff);
                m_store_ptr->destroy();
                // move other's value in, destroy other
                m_store_ptr = other.m_store_ptr->move((void*)&m_buff);
                other.m_store_ptr->destroy();
                // move tmp_buff into other. destroy tmp_buff
                other.m_store_ptr = tmp_ptr->move((void*)&other.m_buff);
                tmp_ptr->destroy();
            } 
            // Our object is local, other's object is remote (or null)
            else if (m_stored_locally()) {
                // move our object into others buffer. 
                // other.m_store_base remains unchanged.
                m_store_ptr->move((void*)&other.m_buff);
                m_store_ptr->destroy();
                // steal other's remote object
                m_store_ptr = other.m_store_ptr;
                // point other at local object
                other.m_store_ptr = static_cast<any_storage_base*>(
                    (void*)&other.m_buff
                  );
            }
            // Our object is remote (or null), other's object is local
            else if (other.m_stored_locally()) {
                other.m_store_ptr->move((void*)&m_buff);
                other.m_store_ptr->destroy();
                other.m_store_ptr = m_store_ptr;
                m_store_ptr = static_cast<any_storage_base*>(
                    (void*)&m_buff
                  );
            // Both objects are remote.
            } else {               
                any_storage_base* tmp_ptr = m_store_ptr;
                m_store_ptr = other.m_store_ptr;
                other.m_store_ptr = tmp_ptr;
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        bool empty() const noexcept
        {
            return (m_store_ptr == nullptr);
        }
        
        explicit operator bool() const noexcept
        {
            return (not empty());
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::type_info const & type() const noexcept
        {
            return m_store_ptr ? m_store_ptr->target_type() 
                              : typeid(void);
        }

    private:
        using any_buffer_t = detail::any_buffer_t;
        using any_storage_base = detail::any_storage_base;
        
        template <class ValueType, class Alloc = std::allocator<ValueType>>
        using any_storage_type = detail::any_storage_type<ValueType, Alloc>;
        
        template <class StorageType>
        using store_locally = detail::store_locally<StorageType>;
        
    private:
        
        bool m_stored_locally() const noexcept
        {
            return static_cast<void const*>(m_store_ptr) 
                == static_cast<void const*>(&m_buff);
        }
        
        bool m_stored_remotely() const noexcept
        {
            return (m_store_ptr && not m_stored_locally());
        }

    private:
        template <class T> friend T any_cast(any const &);
        template <class T> friend T any_cast(any &);
        template <class T> friend T any_cast(any &&);
        template <class T> friend T const * any_cast(any const *) noexcept;
        template <class T> friend T * any_cast(any *) noexcept;
        
    private:
        any_buffer_t m_buff;
        any_storage_base* m_store_ptr;
    };                                                      // class any
    
    ////////////////////////////////////////////////////////////////////////////
    inline void swap(any & lhs, any & rhs) noexcept
    {
        lhs.swap(rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ValueType>
    inline ValueType const * any_cast(any const * v) noexcept
    {
        return v && v->m_store_ptr 
          ? static_cast<ValueType const *>(v->m_store_ptr->target_if(typeid(ValueType)))
          : nullptr;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ValueType>
    inline ValueType * any_cast(any * v) noexcept
    {
        return v && v->m_store_ptr 
          ? static_cast<ValueType*>(v->m_store_ptr->target_if(typeid(ValueType))) 
          : nullptr;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ValueType>
    ValueType any_cast(any const & v)
    {
        static_assert(
            aux::is_reference<ValueType>::value
            || aux::is_copy_constructible<ValueType>::value
          , "ValueType must be a reference or copy constructible"
          );
        
        using CastType = aux::add_const_t<aux::remove_reference_t<ValueType>>;
        auto ptr = any_cast<CastType>(&v);
        if (not ptr) {
            throw bad_any_cast();
        }
        return *ptr;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ValueType>
    ValueType any_cast(any & v)
    {
        static_assert(
            aux::is_reference<ValueType>::value
            || aux::is_copy_constructible<ValueType>::value
          , "ValueType must be a reference or copy constructible"
          );
        
        using CastType = aux::remove_reference_t<ValueType>;
        auto ptr = any_cast<CastType>(&v);
        if (not ptr) {
            throw bad_any_cast();
        }
        return *ptr;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ValueType>
    ValueType any_cast(any && v)
    {
        return any_cast<ValueType>(static_cast<any &>(v));
    }

}                                                           // namespace elib
#endif /* ELIB_ANY_HPP */