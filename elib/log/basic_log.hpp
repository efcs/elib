#ifndef ELIB_LOG_BASIC_LOG_HPP
#define ELIB_LOG_BASIC_LOG_HPP

#include <elib/log/log_level.hpp>
# include <elib/aux.hpp>
# include <elib/fmt.hpp>

#include <map>
#include <mutex>
#include <string>
#include <iosfwd>


namespace elib 
{
  namespace log 
  {
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    /* this class defines the basic logging interface used with the
    * classes log, file_log, and elog (static) */
    class basic_log {
    public:
        basic_log() = default;
        basic_log(level_e l);
        
        virtual ~basic_log() {}
        
        /* set & get the prompt for each log level,
        * the prompt is printed before the message for that level 
        * valid levels: debug-fatal */
        const std::string & prompt(level_e l) const;
        void prompt(level_e l, const std::string &prompt);
        
        /* set & get the current logging level
        * valid levels: debug-fatal */
        void level(level_e l);
        level_e level();
        
        /* print a message to a given log level,
        * valid levels: all */
        template <class ...Args>
        void print(level_e l, const char *msg, Args &&... args )
        {
            _log(l, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void print(level_e l, const std::string &msg)
        {
            _log(l, msg);
        }
        
        /* a method for each log level */
        template <class ...Args>
        void debug(const char *msg, Args &&... args )
        {
            _log(level_e::debug, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void debug(const std::string & s)
        {
            _log(level_e::debug, s);
        }
        
        template <class ...Args>
        void info(const char *msg, Args &&... args )
        {
            _log(level_e::info, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void info(const std::string & s)
        {
            _log(level_e::info, s);
        }
        
        template <class ...Args>
        void step(const char *msg, Args &&... args )
        {
            _log(level_e::step, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void step(const std::string & s)
        {
            _log(level_e::step, s);
        }
        
        template <class ...Args>
        void warn(const char *msg, Args &&... args )
        {
            _log(level_e::warn, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void warn(const std::string & s)
        {
            _log(level_e::warn, s);
        }
        
        template <class ...Args>
        void err(const char *msg, Args &&... args )
        {
            _log(level_e::err, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void err(const std::string & s)
        {
            _log(level_e::err, s);
        }
        
        template <class ...Args>
        void fatal(const char *msg, Args &&... args)
        {
            _log(level_e::fatal, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void fatal(const std::string & s)
        {
            _log(level_e::fatal, s);
        }
        
        template <class ...Args>
        void raw_out(const char *msg, Args &&... args)
        {
            _log(level_e::raw_out, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void raw_out(const std::string & s)
        {
            _log(level_e::raw_out, s);
        }
        
        template <class ...Args>
        void raw_err(const char *msg, Args &&... args)
        {
            _log(level_e::raw_err, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void raw_err(const std::string & s)
        {
            _log(level_e::raw_err, s);
        }
        
        /* Turn ALL OUTPUT from log on/off */
        void on(bool p);
        bool on() const;
        
    public:
        /* check properties about a member of level_e 
        * raw_levels: raw_out, raw_err
        * basic_levels: debug-fatal */
        static bool is_raw_level(level_e e);
        static bool is_basic_level(level_e e);  
    protected:
        typedef std::lock_guard<std::mutex> lock_guard;
        
        bool _should_print(level_e l) const;
        
        void _log(level_e l, const std::string & s);
        
        std::mutex & _lock() const;
        
        virtual std::ostream & _get_stream(level_e l) = 0;

    private:
        level_e m_level{default_log_level};
        bool m_on{true};
        mutable std::mutex m_lock{};
        /* prompt maps: level -> prompt */
        std::map<level_e, std::string> m_prompts = 
            {
              {level_e::debug, "Debug: "},
              {level_e::step, "--> "},
              {level_e::info, "Info: "},
              {level_e::warn, "Warning: "},
              {level_e::err, "ERROR: "},
              {level_e::fatal, "FATAL: "},
              {level_e::raw_out, ""},
              {level_e::raw_err, ""} 
            };
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

  } /* namespace log */
} /* namespace elib */
#endif /* ELIB_LOG_BASIC_LOG_HPP */