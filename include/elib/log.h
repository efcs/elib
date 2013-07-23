#ifndef ELIB_LOG_H
#define ELIB_LOG_H

#include <elib/base_enum.h>

#include <cstdarg>
#include <string>
#include <memory>


namespace elib {

	
class log_impl;


/* RAW levels are not affected by the level */
enum class level_e : BASE_ENUM
{ 	
   none = 0,
	debug,
	info,
	step,
	warn,
	err,
	fatal,
	raw_out,
	raw_err
};


class basic_log {
public:
    static constexpr level_e default_level = level_e::step;
public:
    /* same as static log interface */
    virtual const std::string & prompt(level_e l) const = 0;
    virtual void prompt(level_e l, const std::string &prompt) = 0;
    
    virtual void level(level_e l) = 0;
    virtual level_e level() = 0;
    
    virtual void print(level_e l, const char *msg, ... ) = 0;
    virtual void print(level_e l, const std::string &msg) = 0;
    
    virtual void debug(const char *msg, ... ) = 0;
    virtual void debug(const std::string & s) = 0;
    
    virtual void info(const char *msg, ... ) = 0;
    virtual void info(const std::string & s) = 0;
    
    virtual void step(const char *msg, ... ) = 0;
    virtual void step(const std::string & s) = 0;
    
    virtual void warn(const char *msg, ... ) = 0;
    virtual void warn(const std::string & s) = 0;
    
    virtual void err(const char *msg, ... ) = 0;
    virtual void err(const std::string & s) = 0;
    
    virtual void fatal(const char *msg, ...) = 0;
    virtual void fatal(const std::string & s) = 0;
    
    virtual void raw_out(const char *msg, ...) = 0;
    virtual void raw_out(const std::string & s) = 0;
    
    virtual void raw_err(const char *msg, ...) = 0;
    virtual void raw_err(const std::string & s) = 0;
    
    /* Turn ALL OUTPUT from log on/off */
    virtual void on(bool p) = 0;
    virtual bool on() const = 0;
};


class log : public basic_log {
public:
    log();
    
    /* same as static log interface */
    const std::string & prompt(level_e l) const;
    void prompt(level_e l, const std::string &prompt);
    
    void level(level_e l);
    level_e level();
    
    void print(level_e l, const char *msg, ... );
    void print(level_e l, const std::string &msg);
    
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
private:
    std::shared_ptr<log_impl> m_impl;
};


template <>
struct enum_traits<level_e> {
    static constexpr level_e none_value = level_e::none;
    static constexpr level_e default_value = log::default_level;
    static constexpr level_e first_value = level_e::none;
    static constexpr level_e last_value = level_e::raw_err;
    static constexpr unsigned size = enum_size(first_value, last_value);
    
    typedef const std::map<level_e, std::string> map_type;
    static map_type name_map;
};



} /* namespace elib */
#endif /* ELIB_LOG_H */
