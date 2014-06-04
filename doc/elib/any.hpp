/*! \file any.hpp
 * 
 * A type-erased container. It implements the std::any proposal.
 */
namespace elib
{
    /// The exception thrown by any_cast(any &).
    class bad_any_cast : std::bad_cast
    {
    public:
        bad_any_cast() noexcept;
        virtual const char* what() const noexcept;
    };
    

    /// A type erased container.
    class any
    {
    public:
        
        /// \post this->empty(); 
        any() noexcept;
        
        /// \pre other.empty() or is_copy_constructible<T> where T is the type
        /// stored by other.
        /// \remarks constructs an object in the same state as other.
        /// \throws Exception throws any exception arising from copy construction.
        any(any const & other);
        
        /// \pre other.empty() or is_move_constructible<T> where T is the type stored
        /// by other.
        /// \remarks Move constructs the object from other.
        /// \throws Exception any exception arising from the copy construction.
        any(any && other);
        
        ////////////////////////////////////////////////////////////////////////
        template <class ValueType>
        any(ValueType && value);
        
        ////////////////////////////////////////////////////////////////////////
        template <class Allocator>
        any(std::allocator_arg_t, Allocator const &) noexcept;
        
        ////////////////////////////////////////////////////////////////////////
        template <class Allocator, class ValueType>
        any(std::allocator_arg_t, Allocator const & alloc, ValueType && value);
        
        ~any();
        
        any & operator=(any const & other);
        
        any & operator=(any && other) noexcept;
        
        ////////////////////////////////////////////////////////////////////////
        template <class ValueType>
        any & operator=(ValueType && value);
        
        /// If !empty() destroy stored value. 
        /// \post empty()
        void clear() noexcept;
        
        /// Swap the value stored in this with the value stored in other.
        void swap(any & other) noexcept;
        
        /// \returns True if the object is empty. False otherwise.
        bool empty() const noexcept;
        
        /// \returns True if the object in empty. False otherwise.
        explicit operator bool() const noexcept;
        
        /// \returns The type_info of the stored value of typeid(void) if empty().
        std::type_info const & type() const noexcept;    
    };                                                      // class any
    
    inline void swap(any & lhs, any & rhs) noexcept;
 
    template <class ValueType>
    inline ValueType const * any_cast(any const * v) noexcept;
  
    template <class ValueType>
    inline ValueType * any_cast(any * v) noexcept;

    template <class ValueType>
    ValueType any_cast(any const & v);

    template <class ValueType>
    ValueType any_cast(any & v);
 
    template <class ValueType>
    ValueType any_cast(any && v);

}                                                           // namespace elib
