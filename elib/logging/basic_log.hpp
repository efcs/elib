#ifndef ELIB_LOGGING_BASIC_LOG_HPP
#define ELIB_LOGGING_BASIC_LOG_HPP

# include <elib/logging/log_level.hpp>
# include <elib/aux/forward.hpp>
# include <elib/fmt.hpp>

# include <map>
# include <mutex>
# include <string>
# include <iosfwd>
# include <ostream>
# include <stdexcept>


namespace elib { namespace logging { inline namespace v1
{
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    /* this class defines the basic logging interface used with the
    * classes log, file_log, and elog (static) */
    class basic_log 
    {
    public:
        basic_log() = default;
        
        basic_log(level_e l)
          : m_level(l)
        {}
        
        virtual ~basic_log() {}
        
        /* set & get the prompt for each log level,
        * the prompt is printed before the message for that level 
        * valid levels: debug-fatal */
        const std::string & prompt(level_e l) const
        {
            /* throw if getting non-basic level */
            if (! is_basic_level(l))
                throw std::logic_error("not a valid basic level");
            
            lock_guard lock(m_lock);
            return m_prompts.at(l);
        }
        
        void prompt(level_e l, const std::string &prompt_str)
        {
            if (! is_basic_level(l))
                throw std::logic_error("not a valid basic level");
            lock_guard lock(m_lock);
            m_prompts[l] = prompt_str;
        }
        
        /* set & get the current logging level
        * valid levels: debug-fatal */
        void level(level_e l)
        {
            if (! is_basic_level(l))
                throw std::logic_error("not a valid basic level");
            
            lock_guard lock(m_lock);
            m_level = l;
        }
        
        level_e level() const { return m_level; }
        
        /* print a message to a given log level,
        * valid levels: all */
        template <class ...Args>
        void print(level_e l, const char *msg, Args &&... args )
        {
            m_log_to(l, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void print(level_e l, const std::string &msg)
        {
            m_log_to(l, msg);
        }
        
        /* a method for each log level */
        template <class ...Args>
        void debug(const char *msg, Args &&... args )
        {
            m_log_to(level_e::debug, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void debug(const std::string & s)
        {
            m_log_to(level_e::debug, s);
        }
        
        template <class ...Args>
        void info(const char *msg, Args &&... args )
        {
            m_log_to(level_e::info, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void info(const std::string & s)
        {
            m_log_to(level_e::info, s);
        }
        
        template <class ...Args>
        void step(const char *msg, Args &&... args )
        {
            m_log_to(level_e::step, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void step(const std::string & s)
        {
            m_log_to(level_e::step, s);
        }
        
        template <class ...Args>
        void warn(const char *msg, Args &&... args )
        {
            m_log_to(level_e::warn, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void warn(const std::string & s)
        {
            m_log_to(level_e::warn, s);
        }
        
        template <class ...Args>
        void err(const char *msg, Args &&... args )
        {
            m_log_to(level_e::err, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void err(const std::string & s)
        {
            m_log_to(level_e::err, s);
        }
        
        template <class ...Args>
        void fatal(const char *msg, Args &&... args)
        {
            m_log_to(level_e::fatal, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void fatal(const std::string & s)
        {
            m_log_to(level_e::fatal, s);
        }
        
        template <class ...Args>
        void raw_out(const char *msg, Args &&... args)
        {
            m_log_to(level_e::raw_out, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void raw_out(const std::string & s)
        {
            m_log_to(level_e::raw_out, s);
        }
        
        template <class ...Args>
        void raw_err(const char *msg, Args &&... args)
        {
            m_log_to(level_e::raw_err, elib::fmt(msg, elib::forward<Args>(args)...));
        }
        
        void raw_err(const std::string & s)
        {
            m_log_to(level_e::raw_err, s);
        }
        
        /* Turn ALL OUTPUT from log on/off */
        void on(bool p) noexcept
        { 
            m_on = p; 
        }
        
        bool on() const noexcept
        {
            return m_on;
        }
        
    public:
        /* check properties about a member of level_e 
        * raw_levels: raw_out, raw_err
        * basic_levels: debug-fatal */
        static bool is_raw_level(level_e l) noexcept
        {
            return (l == level_e::raw_out || l == level_e::raw_err);
        }
        
        static bool is_basic_level(level_e l) noexcept
        {
            return (l >= level_e::debug && l <= level_e::fatal);
        }
    protected:
        typedef std::lock_guard<std::mutex> lock_guard;
        
        bool m_should_print(level_e l) const
        {
            return (m_on && 
                (is_raw_level(l) || 
                (is_basic_level(l) && m_level <= l)));
        }
        
        void m_log_to(level_e l, const std::string & msg)
        {
            if (! m_should_print(l)) return;

            lock_guard lock(m_lock);
            
            std::ostream & out = m_get_stream(l);
            if (! out.good()) return;
            
            out << m_prompts[l] << msg << std::endl;
        }
        
        std::mutex & m_get_lock() const
        {
            return m_lock;
        }
        
        virtual std::ostream & m_get_stream(level_e l) = 0;

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

}}}                                                          // namespace elib
#endif /* ELIB_LOGGING_BASIC_LOG_HPP */