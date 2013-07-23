#include "elib/file_log.h"
#include "./detail/_file_log.h"

#define BUFF_MAX 1024

#define __FMT_ARGS() char __fmt_buff[BUFF_MAX]; \
    va_list __args; \
    va_start(__args, msg); \
    vsnprintf(__fmt_buff, BUFF_MAX, msg, __args); \
    va_end(__args)
    
    
#define LOG_FUNC_HANDLER(level) __FMT_ARGS(); \
    m_impl->log(level, __fmt_buff) 

namespace elib {
    
file_log::file_log()
    : m_impl(new file_log_impl)
{
}

file_log::file_log(const std::string & filename)
    : m_impl(new file_log_impl)
{
    m_impl->open(filename);
}

file_log::~file_log()
{
}

const std::string &
file_log::filename() const
{
    return m_impl->filename();
}

bool
file_log::open(const std::string & filename)
{
    return m_impl->open(filename);
}

bool
file_log::good() const
{
    return m_impl->good();
}

void
file_log::close()
{
    m_impl->close();
}


const std::string &
file_log::prompt(level_e level) const
{
    return m_impl->prompt(level);
}

void 
file_log::prompt(level_e level, const std::string &prompt)
{
    m_impl->prompt(level, prompt);
}

void 
file_log::level(level_e level)
{
    m_impl->level(level);
}

level_e 
file_log::level()
{
    return m_impl->level();
}

void 
file_log::print(level_e level, const char *msg, ... ) 
{
    LOG_FUNC_HANDLER(level);
}

void 
file_log::print(level_e level, const std::string &msg)
{
    m_impl->log(level, msg.c_str());
}
    
void 
file_log::debug(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::debug);
}

void 
file_log::debug(const std::string & s)
{
    m_impl->log(level_e::debug, s.c_str());
}

void 
file_log::info(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::info);
}

void 
file_log::info(const std::string & s)
{
    m_impl->log(level_e::info, s.c_str());
}

void 
file_log::step(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::step);
}

void 
file_log::step(const std::string & s)
{
    m_impl->log(level_e::step, s.c_str());
}

void 
file_log::warn(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::warn);
}

void 
file_log::warn(const std::string & s)
{
    m_impl->log(level_e::warn, s.c_str());
}

void 
file_log::err(const char *msg, ... )
{
    LOG_FUNC_HANDLER(level_e::err);
}

void 
file_log::err(const std::string & s)
{
    m_impl->log(level_e::err, s.c_str());
}

void 
file_log::fatal(const char *msg, ...)
{
    LOG_FUNC_HANDLER(level_e::fatal);
}

void 
file_log::fatal(const std::string & s)
{
    m_impl->log(level_e::fatal, s.c_str());
}

void 
file_log::raw_out(const char *msg, ...)
{
    LOG_FUNC_HANDLER(level_e::raw_out);
}

void 
file_log::raw_out(const std::string &msg)
{
    m_impl->log(level_e::raw_out, msg.c_str());
}

void 
file_log::raw_err(const char *msg, ...)
{
    LOG_FUNC_HANDLER(level_e::raw_err);
}

void
file_log::raw_err(const std::string & msg)
{
    m_impl->log(level_e::raw_err, msg.c_str());
}

void
file_log::on(bool p) 
{
    m_impl->on(p);
}

bool
file_log::on() const
{
    return m_impl->on();
}

} /* namespace elib */