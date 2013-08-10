#ifndef ELIB_BASIC_LOG_H
#define ELIB_BASIC_LOG_H

#include "log_level.h"


#include <string>


namespace elib {
    


/* this class defines the basic logging interface used with the
 * classes log, file_log, and elog (static) */
class basic_log {
public:
    /* set & get the prompt for each log level,
     * the prompt is printed before the message for that level 
     * valid levels: debug-fatal */
    virtual const std::string & prompt(level_e l) const = 0;
    virtual void prompt(level_e l, const std::string &prompt) = 0;
    
    /* set & get the current logging level
     * valid levels: debug-fatal */
    virtual void level(level_e l) = 0;
    virtual level_e level() = 0;
    
    /* print a message to a given log level,
     * valid levels: all */
    virtual void print(level_e l, const char *msg, ... ) = 0;
    virtual void print(level_e l, const std::string &msg) = 0;
    
    /* a method for each log level */
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





} /* namespace elib */
#endif /* ELIB_BASIC_LOG_H */