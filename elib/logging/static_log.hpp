#ifndef ELIB_LOGGING_STATIC_LOG_HPP
#define ELIB_LOGGING_STATIC_LOG_HPP

# include <elib/logging/log_level.hpp>
# include <elib/logging/log.hpp>
# include <elib/aux.hpp>
# include <elib/fmt.hpp>
# include <cstdarg>
# include <string>


namespace elib { namespace logging
{
          
    /* global logging class, it logs to std::cout and std::cerr,
    * while it does not inherit from basic_log it implements
    * the basic_log interface except the methods are static */
    template <typename Tag>
    class static_log { 
    private:
        /* only a single instance of static_log is allowed */
        static_log() = delete;
        static log & get_instance();
    public:
        
        static const std::string & 
        prompt(level_e l)
        {
            return get_instance().prompt(l);
        }
        
        static void 
        prompt(level_e l, const std::string &p)
        {
            get_instance().prompt(l, p);
        }
        
        static void 
        level(level_e l)
        {
            get_instance().level(l);
        }
        
        static level_e 
        level()
        {
            return get_instance().level();
        }
        
        template <class ...Args>
        static void 
        print(level_e l, const char *msg, Args &&... args)
        {
            get_instance().print(l, msg, elib::forward<Args>(args)...);
        }
        
        
        static void 
        print(level_e l, const std::string &msg)
        {
            get_instance().print(l, msg);
        }
        
        template <class ...Args>
        static void 
        debug(const char *msg, Args &&... args)
        {
            get_instance().debug(msg, elib::forward<Args>(args)...);
        }
        
        static void 
        debug(const std::string & s)
        {
            get_instance().debug(s);
        }
        
        template <class ...Args>
        static void 
        info(const char *msg, Args &&... args)
        {
            get_instance().info(msg, elib::forward<Args>(args)...);
        }
        
        static void 
        info(const std::string & s)
        {
            get_instance().info(s);
        }
        
        template <class ...Args>
        static void 
        step(const char *msg, Args &&... args)
        {
            get_instance().step(msg, elib::forward<Args>(args)...);
        }
        
        static void 
        step(const std::string & s)
        {
            get_instance().step(s);
        }
        
        template <class ...Args>
        static void 
        warn(const char *msg, Args &&... args)
        {
            get_instance().warn(msg, elib::forward<Args>(args)...);
        }
        
        static void 
        warn(const std::string & s)
        {
            get_instance().warn(s);
        }
        
        template <class ...Args>
        static void 
        err(const char *msg, Args &&... args)
        {
            get_instance().err(msg, elib::forward<Args>(args)...);
        }
        
        static void 
        err(const std::string & s)
        {
            get_instance().err(s);
        }
        
        template <class ...Args>
        static void 
        fatal(const char *msg, Args &&... args)
        {
            get_instance().fatal(msg, elib::forward<Args>(args)...);
        }
        
        static void 
        fatal(const std::string & s)
        {
            get_instance().fatal(s);
        }
        
        template <class ...Args>
        static void 
        raw_out(const char *msg, Args &&... args)
        {
            get_instance().raw_out(msg, elib::forward<Args>(args)...);
        }
        
        static void 
        raw_out(const std::string & s)
        {
            get_instance().raw_out(s);
        }
        
        template <class ...Args>
        static void 
        raw_err(const char *msg, Args &&... args)
        {
            get_instance().raw_err(msg, elib::forward<Args>(args)...);
        }
        
        static void 
        raw_err(const std::string & s)
        {
            get_instance().raw_err(s);
        }
        
        /* Turn ALL OUTPUT from log on/off */
        static void 
        on(bool p)
        {
            get_instance().on(p);
        }
        
        static bool 
        on()
        {
            return get_instance().on();
        }
    };

      
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
# endif
    template <class Tag>
    log & static_log<Tag>::get_instance()
    {
        static log m_instance;
        return m_instance;
    }
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

}}                                                          // namespace elib
#endif /* ELIB_LOGGING_STATIC_LOG_HPP */