#ifndef ELIB_FILELOG_H
#define ELIB_FILELOG_H

#include <elib/log.h>


namespace elib {
    

class file_log_impl;

    
class file_log : public basic_log {
public:
    file_log();
    file_log(const std::string & filename);
    ~file_log();
    
    const std::string & filename() const;
    bool open(const std::string & s);
    bool good() const;
    void close();
    
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
    std::shared_ptr<file_log_impl> m_impl;
};
    

} /* namespace elib */
#endif /* ELIB_FILELOG_H */