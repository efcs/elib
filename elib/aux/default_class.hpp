#ifndef ELIB_AUX_DEFAULT_CLASS_HPP
#define ELIB_AUX_DEFAULT_CLASS_HPP
# 
# /// Macros to provide defaulted constructors and assignments
# 
# define ELIB_DEFAULT_CLASS(Class)          \
  Class() = default;                        \
                                            \
  Class(const Class&) = default;            \
  Class(Class&&) = default;                 \
                                            \
  Class& operator=(const Class&) = default; \
  Class& operator=(Class&&) = default
# 

# define ELIB_DEFAULT_COPY(Class)   \
    Class(Class const &) = default; \
    Class & operator=(Class const &) = default
# 

# define ELIB_DEFAULT_MOVE(Class) \
    Class(Class &&) = default;    \
    Class & operator=(Class &&) = default
# 
    
# define ELIB_DEFAULT_COPY_MOVE(Class) \
    ELIB_DEFAULT_COPY(Class);          \
    ELIB_DEFAULT_MOVE(Class)
# 
    
# define ELIB_DELETE_COPY(Class)   \
    Class(Class const &) = delete; \
    Class & operator=(Class const &) = delete
# 
    
# define ELIB_DELETE_MOVE(Class) \
    Class(Class &&) = delete;    \
    Class & operator=(Class &&) = delete
# 
    
# define ELIB_DELETE_COPY_MOVE(Class) \
    ELIB_DELETE_COPY(Class);          \
    ELIB_DELETE_MOVE(Class)
# 
# 
#endif /* ELIB_AUX_DEFAULT_CLASS_HPP */