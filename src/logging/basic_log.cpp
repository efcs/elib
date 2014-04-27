#include <elib/logging/basic_log.hpp>
#include <elib/aux.hpp>
#include <elib/fmt.hpp>
#include <ostream>
#include <cstdarg>

//#define ELIB_LOG_LOCK_FREE 1
    
namespace elib { namespace logging
{
    std::string const & basic_log::prompt(level_e l) const
    {
        /* throw if getting non-basic level */
        if (! is_basic_level(l))
            throw std::logic_error("not a valid basic level");
        
    #if !defined(ELIB_LOG_LOCK_FREE)
        lock_guard lock(m_lock);
    #endif
        return m_prompts.at(l);
    }

    void 
    basic_log::prompt(level_e l, const std::string &prompt_str)
    {
        if (! is_basic_level(l))
            throw std::logic_error("not a valid basic level");
    #if !defined(ELIB_LOG_LOCK_FREE)
        lock_guard lock(m_lock);
    #endif
        m_prompts[l] = prompt_str;
    }

    void 
    basic_log::level(level_e l)
    {
        if (! is_basic_level(l))
            throw std::logic_error("not a valid basic level");
    #if !defined(ELIB_LOG_LOCK_FREE)
        lock_guard lock(m_lock);
    #endif
        m_level = l;
    }

    void basic_log::m_log_to(level_e l, const std::string & msg) 
    {
        if (! m_should_print(l))
            return;

    #if !defined(ELIB_LOG_LOCK_FREE)
        lock_guard lock(m_lock);
    #endif
        
        std::ostream & out = m_get_stream(l);
        if (! out.good())
            return;
        
        out << m_prompts[l] << msg << std::endl;
    }

    bool basic_log::m_should_print(level_e l) const 
    {
        return (m_on && 
                (is_raw_level(l) || 
                (is_basic_level(l) && m_level <= l)));
    }

    bool basic_log::is_raw_level(level_e l)
    {
        return (l == level_e::raw_out || l == level_e::raw_err);
    }

    bool basic_log::is_basic_level(level_e l)
    {
        return (l >= level_e::debug && l <= level_e::fatal);
    }


    std::mutex & basic_log::m_get_lock() const
    {
    #if defined(ELIB_LOG_LOCK_FREE)
        ELIB_ASSERT(false);
    #endif
        return m_lock;
    }
}}                                                          // namespace elib