/* 
 * Copyright (C) 2013  Eric Fiselier
 * 
 * This file is part of elib.
 *
 * elib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * elib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elib.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ELIB_LOG_STATIC_LOG_HPP
#define ELIB_LOG_STATIC_LOG_HPP

#include <elib/log/log_level.hpp>
#include <elib/log/log.hpp>
#include <elib/utility/fmt.hpp>
#include <elib/pragma.hpp>

#include <cstdarg>
#include <string>


namespace elib 
{
  namespace log 
  {

          
    /* global logging class, it logs to std::cout and std::cerr,
    * while it does not inherit from basic_log it implements
    * the basic_log interface except the methods are static */
    template <typename Tag>
    class static_log { 
    private:
        /* only a single instance of static_log is allowed */
        static_log();
        static log m_impl;
    public:
        
        static const std::string & 
        prompt(level_e l);
        
        static void 
        prompt(level_e l, const std::string &prompt);
        
        static void 
        level(level_e l);
        
        static level_e 
        level();
        
        static void 
        print(level_e l, const char *msg, ... );
        
        static void 
        print(level_e l, const std::string &msg);
        
        static void 
        debug(const char *msg, ... );
        
        static void 
        debug(const std::string & s);
        
        static void 
        info(const char *msg, ... );
        
        static void 
        info(const std::string & s);
        
        static void 
        step(const char *msg, ... );
        
        static void 
        step(const std::string & s);
        
        static void 
        warn(const char *msg, ... );
        
        static void 
        warn(const std::string & s);
        
        static void 
        err(const char *msg, ... );
        
        static void 
        err(const std::string & s);
        
        static void 
        fatal(const char *msg, ...);
        
        static void 
        fatal(const std::string & s);
        
        static void 
        raw_out(const char *msg, ...);
        
        static void 
        raw_out(const std::string & s);
        
        static void 
        raw_err(const char *msg, ...);
        
        static void 
        raw_err(const std::string & s);
        
        /* Turn ALL OUTPUT from log on/off */
        static void 
        on(bool p);
        
        static bool 
        on();
    };
    
    ELIB_PRAGMA_DIAG_PUSH()
    ELIB_PRAGMA_IGNORE_GLOBAL_CONSTRUCTORS()
    ELIB_PRAGMA_IGNORE_EXIT_TIME_DESTRUCTORS()
          
      template <typename Tag>
      log static_log<Tag>::m_impl;

    ELIB_PRAGMA_DIAG_POP()
    
    #define ELIB_LOG_FUNC_HANDLER(level) \
        va_list __args; \
        va_start(__args, msg); \
        std::string __str = fmt(msg, __args); \
        va_end(__args); \
        m_impl._log(level, __str)
    

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
        ELIB_LOG_FUNC_HANDLER(level);
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
        ELIB_LOG_FUNC_HANDLER(level_e::debug);
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
        ELIB_LOG_FUNC_HANDLER(level_e::info);
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
        ELIB_LOG_FUNC_HANDLER(level_e::step);
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
        ELIB_LOG_FUNC_HANDLER(level_e::warn);
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
        ELIB_LOG_FUNC_HANDLER(level_e::err);
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
        ELIB_LOG_FUNC_HANDLER(level_e::fatal);
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
        ELIB_LOG_FUNC_HANDLER(level_e::raw_out);
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
        ELIB_LOG_FUNC_HANDLER(level_e::raw_err);
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
       
# undef ELIB_LOG_FUNC_HANDLER

  }                                                         // namespace log
}                                                           // namespace elib
#endif /* ELIB_LOG_STATIC_LOG_HPP */