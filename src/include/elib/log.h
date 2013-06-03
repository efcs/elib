#ifndef ELIBOG_H
#define ELIBOG_H

#include <cstdarg>
#include <string>
#include <memory>

namespace elib {

	
namespace _elib {
	class LogImpl;
	class FileLogImpl;
}

/* RAW levels are always on, and the logging level cannot effect that */
enum LevelEnum { LDEBUG, LINFO, LSTEP, LWARNING, LERROR, LFATAL,
				LRAW_OUT, LRAW_ERR };
				
constexpr int LDEFAULT = LSTEP;

	
/* global logging class */
class Log
{ 
public:
	Log(); // sets to default level 
	explicit Log(int level);
	
	virtual ~Log();
	
	/* same as static log interface */
	std::string get_prompt(int level) const;
	bool set_prompt(int level, const std::string &prompt);
	
	void set_level(int new_level);
	int modify_level(int delta);
	int get_level() const;
	
	void log(int level, const char *msg, ... );
	void log(int level, const std::string &msg);
	
	void debug(const char *msg, ... );
	void info(const char *msg, ... );
	void step(const char *msg, ... );
	void warning(const char *msg, ... );
	void error(const char *msg, ... );
	void fatal(const char *msg, ...);
	
	void raw_out(const char *msg, ...);
	void raw_out(const std::string &msg);
	
	void raw_err(const char *msg, ...);
	void raw_err(const std::string &msg);
	
private:
	std::shared_ptr<_elib::LogImpl> m_impl;
};


class FileLog : public Log
{
public:
	explicit FileLog(const char *filename);
	FileLog(int level, const char *filename);
	~FileLog();
	
	/* extra file interface */
	void set_file(const char *filename);
	void close();
	std::string filename() const;
	bool good() const;
	
	/* same as static log interface */
	std::string get_prompt(int level) const;
	bool set_prompt(int level, const std::string &n_prompt);
	
	void set_level(int new_level);
	int modify_level(int delta);
	int get_level() const;
	
	void log(int level, const char *msg, ... );
	void log(int level, const std::string &msg);
	
	void debug(const char *msg, ... );
	void info(const char *msg, ... );
	void step(const char *msg, ... );
	void warning(const char *msg, ... );
	void error(const char *msg, ... );
	void fatal(const char *msg, ...);
	
	void raw_out(const char *msg, ...);
	void raw_out(const std::string &msg);
	/* same as raw_out */
	void raw_err(const char *msg, ...);
	void raw_err(const std::string &msg);
private:
	std::shared_ptr<_elib::FileLogImpl> m_impl;
};



} /* namespace elib */
#endif /* ELIBOG_H */
