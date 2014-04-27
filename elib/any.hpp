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
    ////////////////////////////////////////////////////////////////////////////
    class bad_any_cast : std::bad_cast
    {
    public:
        virtual const char* what() const noexcept
        {
            return "bad any cast";
        }
    };
    
    namespace any_detail
    {
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
        ////////////////////////////////////////////////////////////////////////
        struct storage_base
        {
            storage_base() = default;
            storage_base(storage_base const &) = delete;
            storage_base(storage_base &&) = delete;
            
            virtual ~storage_base() { }
            
            virtual storage_base* copy() const = 0;
            virtual storage_base* copy(storage_base *) const = 0;
            virtual storage_base* move(storage_base *) = 0;
            
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
        struct storage_type : public storage_base
        {
        public:
            using value_type = ValueType;
            using allocator_type = Alloc;
            
        public:
            storage_type(ValueType const & v)
              : m_pair(v, Alloc())
            {}
            
            storage_type(ValueType && v)
              : m_pair(elib::move(v), Alloc())
            {}
            
            storage_type(ValueType const & v, Alloc const & a)
              : m_pair(v, a)
            {}
            
            storage_type(ValueType const & v, Alloc && a)
              : m_pair(v, elib::move(a))
            {}
            
            storage_type(ValueType && v, Alloc && a)
              : m_pair(elib::move(v), elib::move(a))
            {}
            
        public:
            storage_base* copy() const
            {
                using NewAlloc = typename Alloc::template rebind<storage_type>::other;
                NewAlloc a(m_pair.second());
                using Dtor = allocator_destructor<NewAlloc>;
                std::unique_ptr<storage_type, Dtor> tmp(a.allocate(1), Dtor(a, 1));
                ::new ((void*)tmp.get()) storage_type(m_pair.first(), Alloc(a));
                return tmp.release();
            }
            
            storage_base* copy(storage_base* dest) const
            {
                ::new ((void*)dest) storage_type(
                    m_pair.first()
                  , m_pair.second()
                  );
                return dest;
            }
            
            storage_base* move(storage_base* dest)
            {
                ::new ((void*)dest) storage_type(
                    elib::move(m_pair.first())
                  , elib::move(m_pair.second())
                  );
                return dest;
            }
            
            void destroy() noexcept
            {
                m_pair.~compressed_pair<ValueType, Alloc>();
            }
            
            void destroy_deallocate() noexcept
            {
                using NewAlloc = typename 
                    Alloc::template rebind<storage_type>::other;
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
        using buffer_t = aux::aligned_storage_t<sizeof(void*)*3>;
        
        ////////////////////////////////////////////////////////////////////////
        template <
            class ValueType
          , class Alloc = std::allocator<ValueType>
          >
        using store_locally = 
        elib::and_c<
            sizeof(storage_type<ValueType, Alloc>) <= sizeof(buffer_t)
          , aux::alignment_of<buffer_t>::value 
                % std::alignment_of<storage_type<ValueType, Alloc>>::value == 0
          , aux::is_nothrow_move_constructible<ValueType>::value
        >;
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    class any
    {
    public:
        ////////////////////////////////////////////////////////////////////////
        any() noexcept
          : m_base_ptr(nullptr)
        {}
        
        ////////////////////////////////////////////////////////////////////////
        any(any const & other)
          : m_base_ptr(nullptr)
        {
            if (other.m_base_ptr == (const storage_base*)&other.m_buff ) {
                m_base_ptr = other.m_base_ptr->copy(m_buff_ptr());
            }
            else if (other.m_base_ptr) {
                m_base_ptr = other.m_base_ptr->copy();
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        any(any && other)
          : m_base_ptr(nullptr)
        {
            if (other.m_base_ptr == other.m_buff_ptr()) {
                m_base_ptr = other.m_base_ptr->move(m_buff_ptr());
            } 
            else if (other.m_base_ptr) {
                m_base_ptr = other.m_base_ptr;
                other.m_base_ptr = nullptr;
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class ValueType>
        any(ValueType && value)
          : m_base_ptr(nullptr)
        {
            using StoredValue = aux::decay_t<ValueType>;
            using Storage = storage_type<StoredValue>;
            if (store_locally<StoredValue>::value) {
                ::new ((void*)&m_buff) Storage(elib::forward<ValueType>(value));
                m_base_ptr = m_buff_ptr();
            } else {
                using Alloc = typename Storage::allocator_type::template rebind<Storage>::other;
                using Dtor = allocator_destructor<Alloc>;
                Alloc a;
                std::unique_ptr<Storage, Dtor> tmp(a.allocate(1), Dtor(a, 1));
                ::new ((void*)tmp.get()) Storage(
                    elib::forward<ValueType>(value)
                  , typename Storage::allocator_type(a)
                  );
                m_base_ptr = tmp.release();
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        // template <class Allocator>
        // any(std::allocator_arg_t, Allocator const & alloc);
        
        ////////////////////////////////////////////////////////////////////////
        template <class Allocator, class ValueType>
        any(std::allocator_arg_t, Allocator const & alloc, ValueType && value)
        {
            using StoredValue = aux::decay_t<ValueType>;
            using StoredAlloc = typename Allocator::template rebind<StoredValue>::other;
            
            using Storage = storage_type<StoredValue, StoredAlloc>;
            if (store_locally<Storage>::value) {
                ::new ((void*)m_buff_ptr()) Storage(
                    elib::forward<ValueType>(value)
                  , StoredAlloc(alloc)
                  );
                m_base_ptr = m_buff_ptr();
            } else {
                using OtherAlloc = typename Allocator::template rebind<Storage>::other;
                using Dtor = allocator_destructor<OtherAlloc>;
                OtherAlloc a(alloc);
                std::unique_ptr<Storage, Dtor> tmp(a.allocate(1), Dtor(a, 1));
                ::new ((void*)tmp.get()) Storage(
                    elib::forward<ValueType>(value)
                  , StoredAlloc(a)
                  );
                m_base_ptr = (storage_base*)tmp.release();
            }
        }
        
        ~any()
        {
            clear();
        }
        
        // TODO offer strong exception safety guarentee
        any & operator=(any const & other)
        {
            any(other).swap(*this);
            return *this;
        }
        
        any & operator=(any && other) noexcept
        {
            this->swap(other);
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        template <class ValueType>
        any & operator=(ValueType && value)
        {
            any(elib::forward<ValueType>(value)).swap(*this);
            return *this;
        }
        
        ////////////////////////////////////////////////////////////////////////
        void clear() noexcept
        {
            if (m_base_ptr == m_buff_ptr()) {
                m_base_ptr->destroy();
            }
            else if (m_base_ptr) {
                m_base_ptr->destroy_deallocate();
            } 
            m_base_ptr = nullptr;
        }
        
        ////////////////////////////////////////////////////////////////////////
        void swap(any & other) noexcept
        {
            if (m_stored_locally() && other.m_stored_locally()) {
                buffer_t tmp_buff;
                storage_base *tmp_ptr = m_base_ptr->move((storage_base*)&tmp_buff);
                m_base_ptr->destroy();
                m_base_ptr = other.m_base_ptr->move(m_buff_ptr());
                other.m_base_ptr->destroy();
                other.m_base_ptr = tmp_ptr->move(other.m_buff_ptr());
                tmp_ptr->destroy();
            } 
            else if (m_stored_locally()) {
                m_base_ptr->move(other.m_buff_ptr());
                m_base_ptr->destroy();
                m_base_ptr = other.m_base_ptr;
                other.m_base_ptr = (storage_base*)&other.m_buff;
            }
            else if (other.m_stored_locally()) {
                other.m_base_ptr->move(m_buff_ptr());
                other.m_base_ptr->destroy();
                other.m_base_ptr = m_base_ptr;
                m_base_ptr = m_buff_ptr();
            } else {
                storage_base *tmp_ptr = m_base_ptr;
                m_base_ptr = other.m_base_ptr;
                other.m_base_ptr = tmp_ptr;
            }
        }
        
        ////////////////////////////////////////////////////////////////////////
        bool empty() const noexcept
        {
            return (m_base_ptr == nullptr);
        }
        
        explicit operator bool() const noexcept
        {
            return (not empty());
        }
        
        ////////////////////////////////////////////////////////////////////////
        std::type_info const & type() const noexcept
        {
            return m_base_ptr ? m_base_ptr->target_type() : typeid(void);
        }

    private:
        using buffer_t = any_detail::buffer_t;
        using storage_base = any_detail::storage_base;
        
        template <class ValueType, class Alloc = std::allocator<ValueType>>
        using storage_type = any_detail::storage_type<ValueType, Alloc>;
        
        template <class ValueType, class Alloc = std::allocator<ValueType>>
        using store_locally = any_detail::store_locally<ValueType, Alloc>;
        
    private:
        storage_base * m_buff_ptr() noexcept
        {
            return static_cast<storage_base*>(
                static_cast<void*>(&m_buff)
              );
        }
        
        storage_base const * m_buff_ptr() const noexcept
        {
            return static_cast<storage_base const*>(
                static_cast<void const*>(&m_buff)
              );
        }
        
        bool m_stored_locally() const noexcept
        {
            return m_base_ptr == m_buff_ptr();
        }
        
        bool m_stored_remotely() const noexcept
        {
            return (m_base_ptr && not m_stored_locally());
        }

    private:
        template <class T> friend T any_cast(any const &);
        template <class T> friend T any_cast(any &);
        template <class T> friend T any_cast(any &&);
        template <class T> friend T const * any_cast(any const *) noexcept;
        template <class T> friend T * any_cast(any *) noexcept;
        
    private:
        buffer_t m_buff;
        storage_base *m_base_ptr;
    
    };
    
    ////////////////////////////////////////////////////////////////////////////
    inline void swap(any & lhs, any & rhs) noexcept
    {
        lhs.swap(rhs);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ValueType>
    inline ValueType const * any_cast(any const * v) noexcept
    {
        return v && v->m_base_ptr 
          ? static_cast<ValueType const *>(v->m_base_ptr->target_if(typeid(ValueType)))
          : nullptr;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class ValueType>
    inline ValueType * any_cast(any * v) noexcept
    {
        return v && v->m_base_ptr 
          ? static_cast<ValueType*>(v->m_base_ptr->target_if(typeid(ValueType))) 
          : nullptr;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    // TODO Don't accept rvalue references
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
        return any_cast<ValueType>(static_cast<any const &>(v));
    }

}                                                           // namespace elib
#endif /* ELIB_ANY_HPP */