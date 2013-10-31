#ifndef ELIB_LOG_BASIC_LOG_HPP
#define ELIB_LOG_BASIC_LOG_HPP

#include <elib/log/log_level.hpp>

#include <map>
#include <mutex>
#include <string>
#include <iosfwd>


namespace elib 
{
  namespace log 
  {
    

    /* this class defines the basic logging interface used with the
    * classes log, file_log, and elog (static) */
    class basic_log {
    public:
        basic_log() = default;
        basic_log(level_e l);
        
        virtual ~basic_log() noexcept;
        
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
        void print(level_e l, const char *msg, ... );
        void print(level_e l, const std::string &msg);
        
        /* a method for each log level */
        void debug(const char *msg, ... );
        void debug(const std::string & s);
        
        void info(const char *msg, ... );
        void info(const std::string & s);
        
        void step(const char *msg, ... );
        void step(const std::string & s);
        
        void warn(const char *msg, ... );
        void warn(const std::string & s);
        
        void err(const char *msg, ... );
        void err(const std::string & s);
        
        void fatal(const char *msg, ...);
        void fatal(const std::string & s);
        
        void raw_out(const char *msg, ...);
        void raw_out(const std::string & s);
        
        void raw_err(const char *msg, ...);
        void raw_err(const std::string & s);
        
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
              {level_e::info, "Info: "},
              {level_e::step, "--> "},
              {level_e::warn, "Warning: "},
              {level_e::err, "ERROR: "},
              {level_e::fatal, "FATAL: "},
              {level_e::raw_out, ""},
              {level_e::raw_err, ""} 
            };
        
    private:
        template <typename T>
        friend class static_log;
    };


  } /* namespace log */
} /* namespace elib */
#endif /* ELIB_LOG_BASIC_LOG_HPP */