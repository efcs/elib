#ifndef ELIB__SINGLETON_HPP
#define ELIB__SINGLETON_HPP


#ifndef ELIB_SINGLETON_HPP
#   error do not include this file directly
#endif


namespace elib {


////////////////////////////////////////////////////////////////////////////////
//                              singleton                                                    
////////////////////////////////////////////////////////////////////////////////
    
    
template <typename T>
singleton<T>::singleton()
    : m_ptr{ctor_helper()}
{ }

template <typename T>
template <typename... Args>
singleton<T>::singleton(Args&&... args)
    : m_ptr{new type(std::forward<Args>(args)...)}
{ }

template <typename T>
inline T & 
singleton<T>::construct() 
{
    if (! std::is_default_constructible<type>::value)
        throw std::logic_error("no default constructor");
    
    m_ptr.reset(ctor_helper::construct());
    return *m_ptr;
}

template <typename T>
template <typename... Args>
inline T &
singleton<T>::construct(Args&&... args)
{
    m_ptr.reset(new type(std::forward<Args>(args)...));
    return *m_ptr;
}

template <typename T>
inline void
singleton<T>::destruct()
{
    m_ptr.reset(nullptr);
}


template <typename T>
inline T &
singleton<T>::get() const
{
    if (! good())
        throw std::logic_error("null instance");
    
    return *m_ptr;
}

template <typename T>
inline bool
singleton<T>::good() const
{
    return ((bool)m_ptr);
}
    
////////////////////////////////////////////////////////////////////////////////
//                                static_singleton                                                                   
////////////////////////////////////////////////////////////////////////////////
   
template <typename T>
typename static_singleton<T>::ptr_type
static_singleton<T>::m_ptr;

template <typename T>
inline T & 
static_singleton<T>::construct() 
{
    if (! std::is_default_constructible<type>::value)
        throw std::logic_error("no default constructor");
    
    m_ptr.reset(ctor_helper::construct());
    return *m_ptr;
}

template <typename T>
template <typename... Args>
inline T &
static_singleton<T>::construct(Args&&... args)
{
    m_ptr.reset(new type(std::forward<Args>(args)...));
    return *m_ptr;
}

template <typename T>
inline void
static_singleton<T>::destruct()
{
    m_ptr.reset(nullptr);
}


template <typename T>
inline T &
static_singleton<T>::get() 
{
    if (! good())
        throw std::logic_error("null instance");
    
    return *m_ptr;
}

template <typename T>
inline bool
static_singleton<T>::good() 
{
    return ((bool)m_ptr);
}   
    
} /* namespace elib */
#endif /* ELIB__SINGLETON_HPP */
