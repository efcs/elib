#ifndef ELIB__SINGLETON_H
#define ELIB__SINGLETON_H

#ifndef ELIB_SINGLETON_H
#   error do not include this file directly
#endif

namespace elib {
    
    
template <typename T>
std::unique_ptr<T>
singleton<T>::m_ptr{nullptr};


template <typename T>
template <typename... Args>
void
singleton<T>::create_singleton(Args&&... args)
{
    m_ptr.reset(new T{std::forward<Args>(args)...});
}

template <typename T>
void
singleton<T>::create_singleton()
{
    m_ptr.reset(new T{});
}

template <typename T>
T &
singleton<T>::get()
{
    return *m_ptr;
}

template <typename T>
bool
singleton<T>::good()
{
    return ((bool)m_ptr);
}
    
    
} /* namespace elib */
#endif /* ELIB__SINGLETON_H */
