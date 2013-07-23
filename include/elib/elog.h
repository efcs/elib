#ifndef ELIB_ELOG_H
#define ELIB_ELOG_H

#include <elib/log.h>

namespace elib {
    
    
/* global logging class */
class elog { 
private:
    elog();
    static std::unique_ptr<log_impl> m_impl;
public:
    
    static const std::string & prompt(level_e l);
    static void prompt(level_e l, const std::string &prompt);
    
    static void level(level_e l);
    static level_e level();
    
    static void print(level_e l, const char *msg, ... );
    static void print(level_e l, const std::string &msg);
    
    static void debug(const char *msg, ... );
    static void debug(const std::string & s);
    
    static void info(const char *msg, ... );
    static void info(const std::string & s);
    
    static void step(const char *msg, ... );
    static void step(const std::string & s);
    
    static void warn(const char *msg, ... );
    static void warn(const std::string & s);
    
    static void err(const char *msg, ... );
    static void err(const std::string & s);
    
    static void fatal(const char *msg, ...);
    static void fatal(const std::string & s);
    
    static void raw_out(const char *msg, ...);
    static void raw_out(const std::string & s);
    
    static void raw_err(const char *msg, ...);
    static void raw_err(const std::string & s);
    
    /* Turn ALL OUTPUT from log on/off */
    static void on(bool p);
    static bool on();
};


} /* namespace elib */
#endif /* ELIB_ELOG_H */