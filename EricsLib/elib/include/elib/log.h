#ifndef ELIB_LOG_H
#define ELIB_LOG_H

#include <cstdarg>
#include <string>
#include <memory>

namespace elib {

	
namespace _elib {
	class LogImpl;
	class LogFileImpl;
}

	
enum LevelEnum { DEBUG_L, INFO_L, STEP_L, WARNING_L, ERROR_L, FATAL_L };
	

class Log 
{
public:
	/* default log values */
	static constexpr int default_log_level = STEP_L;
	
	/* static interface uses std::cout and std::cerr */
	static void set_level(int new_level);
	static int get_level();
	
	/* logging methods */
	static void debug(const char *msg, ... );
	static void info(const char *msg, ... );
	static void step(const char *msg, ... );
	static void warning(const char *msg, ... );
	static void error(const char *msg, ... );
	static void fatal(const char *msg, ... ); 
	
	/* raw methods are always on */
	static void raw_out(const char *msg, ... );
	static void raw_err(const char *msg, ... );
};


namespace _elib { class LogFileImpl; }
class LogFile 
{
public:
	LogFile(const char *filename);
	~LogFile();
	
	/* extra file interface */
	void set_file(const char *filename);
	void close_file();
	std::string filename() const;
	bool good() const;
	
	/* same as static log interface */
	void set_level(int new_level);
	int get_level() const;
	void debug(const char *msg, ... );
	void info(const char *msg, ... );
	void step(const char *msg, ... );
	void warning(const char *msg, ... );
	void error(const char *msg, ... );
	void fatal(const char *msg, ... ); 
	void raw_out(const char *msg, ...);
private:
	std::shared_ptr<_elib::LogFileImpl> m_impl;
};


} /* namespace elib */
#endif /* ELIB_LOG_H */
