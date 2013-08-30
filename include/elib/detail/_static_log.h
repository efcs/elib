#ifndef ELIB__STATIC_LOG_H
#define ELIB__STATIC_LOG_H


#ifndef ELIB_STATIC_LOG_H
#   error this file must only be included through static_log.h
#endif

#ifdef _ELIB_LOG_FUNC_HANDLER
#   error needed macro name already defined
#endif

    
#define _ELIB_LOG_FUNC_HANDLER(level) \
    va_list __args; \
    va_start(__args, msg); \
    std::string __str = fmt(msg, __args); \
    va_end(__args); \
    m_impl._log(level, __str)
    

namespace elib {
    
    
template <typename Tag>
log
static_log<Tag>::m_impl;


template <typename Tag>
inline const std::string &
static_log<Tag>::prompt(level_e level)
{
    return m_impl.prompt(level);
}

template <typename Tag>
inline void 
static_log<Tag>::prompt(level_e level, const std::string &prompt)
{
    m_impl.prompt(level, prompt);
}

template <typename Tag>
inline void 
static_log<Tag>::level(level_e level)
{
    m_impl.level(level);
}

template <typename Tag>
inline level_e 
static_log<Tag>::level()
{
    return m_impl.level();
}

template <typename Tag>
inline void 
static_log<Tag>::print(level_e level, const char *msg, ... ) 
{
    _ELIB_LOG_FUNC_HANDLER(level);
}

template <typename Tag>
inline void 
static_log<Tag>::print(level_e level, const std::string &msg)
{
    m_impl._log(level, msg.c_str());
}

template <typename Tag>
inline void 
static_log<Tag>::debug(const char *msg, ... )
{
    _ELIB_LOG_FUNC_HANDLER(level_e::debug);
}

template <typename Tag>
inline void 
static_log<Tag>::debug(const std::string & s)
{
    m_impl._log(level_e::debug, s.c_str());
}

template <typename Tag>
inline void 
static_log<Tag>::info(const char *msg, ... )
{
    _ELIB_LOG_FUNC_HANDLER(level_e::info);
}

template <typename Tag>
inline void 
static_log<Tag>::info(const std::string & s)
{
    m_impl._log(level_e::info, s.c_str());
}

template <typename Tag>
inline void 
static_log<Tag>::step(const char *msg, ... )
{
    _ELIB_LOG_FUNC_HANDLER(level_e::step);
}

template <typename Tag>
inline void 
static_log<Tag>::step(const std::string & s)
{
    m_impl._log(level_e::step, s.c_str());
}

template <typename Tag>
inline void 
static_log<Tag>::warn(const char *msg, ... )
{
    _ELIB_LOG_FUNC_HANDLER(level_e::warn);
}

template <typename Tag>
inline void 
static_log<Tag>::warn(const std::string & s)
{
    m_impl._log(level_e::warn, s.c_str());
}

template <typename Tag>
inline void 
static_log<Tag>::err(const char *msg, ... )
{
    _ELIB_LOG_FUNC_HANDLER(level_e::err);
}

template <typename Tag>
inline void 
static_log<Tag>::err(const std::string & s)
{
    m_impl._log(level_e::err, s.c_str());
}

template <typename Tag>
inline void 
static_log<Tag>::fatal(const char *msg, ...)
{
    _ELIB_LOG_FUNC_HANDLER(level_e::fatal);
}

template <typename Tag>
inline void 
static_log<Tag>::fatal(const std::string & s)
{
    m_impl._log(level_e::fatal, s.c_str());
}

template <typename Tag>
inline void 
static_log<Tag>::raw_out(const char *msg, ...)
{
    _ELIB_LOG_FUNC_HANDLER(level_e::raw_out);
}

template <typename Tag>
inline void 
static_log<Tag>::raw_out(const std::string &msg)
{
    m_impl._log(level_e::raw_out, msg.c_str());
}

template <typename Tag>
inline void 
static_log<Tag>::raw_err(const char *msg, ...)
{
    _ELIB_LOG_FUNC_HANDLER(level_e::raw_err);
}

template <typename Tag>
inline void
static_log<Tag>::raw_err(const std::string & msg)
{
    m_impl._log(level_e::raw_err, msg.c_str());
}

template <typename Tag>
inline void
static_log<Tag>::on(bool p) 
{
    m_impl.on(p);
}

template <typename Tag>
inline bool
static_log<Tag>::on()
{
    return m_impl.on();
}
    
    
} /* namespace elib */


#undef _ELIB_LOG_FUNC_HANDLER


#endif /* ELIB__STATIC_LOG_H */