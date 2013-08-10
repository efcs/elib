#ifndef ELIB_FILE_LOG_H
#define ELIB_FILE_LOG_H

#include "basic_log.h"
#include "log_level.h"

#include <memory>
#include <ios>

namespace elib {
    
namespace detail { class file_log_impl; }

 
/* file_log implements the basic_log interface,
 * for basic_log method documentation see log.h */
class file_log : public basic_log {
public:
    file_log();
    /* open file for output */
    file_log(const std::string & filename);
    ~file_log();
    
    /* return the path to the current file */
    const std::string & filename() const;
    
    /* open a new output file */
    bool open(const std::string & s);
    
    bool open(const std::string & s,
              std::ios_base::openmode);
    
    /* check if the output file is good */
    bool good() const;
    
    /* close the output file */
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
    std::shared_ptr<detail::file_log_impl> m_impl;
};

} /* namespace elib */
#endif /* ELIB_FILE_LOG_H */