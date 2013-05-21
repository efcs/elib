#ifndef _LOG_H
#define _LOG_H

#include "elib/log.h"
#include <iostream>
#include <fstream>
#include <mutex>
#include <map>

#define PRINT_BUFF_MAX 1024

namespace elib {
namespace _elib {
	
/* RAW levels */
constexpr int RAW_OUT_L = FATAL_L + 1;
constexpr int RAW_ERR_L = RAW_OUT_L + 1;
	
class LogImpl
{
public:
	LogImpl() : m_level(Log::default_log_level) {
		m_prompts[DEBUG_L] = "DEBUG:";
		m_prompts[INFO_L] = "Info:";
		m_prompts[STEP_L] = "-->";
		m_prompts[WARNING_L] = "Warning:";
		m_prompts[ERROR_L] = "Error:";
		m_prompts[FATAL_L] = "FATAL:";
	}
	
	virtual ~LogImpl() { } 
	
	inline void set_level(int new_level) { 
		m_level = new_level; 
	}
	
	inline int get_level() const { 
		return m_level; 
	}	
	
	/* do not use with raw levels */
	inline void log(int level, const char *msg, 
					std::ostream &out, std::ostream &err) {
		if (m_level >= level && level <= STEP_L)
			print(out, "%s %s", m_prompts[level], msg);
		else if (m_level >= level && level >= WARNING_L)
			print(err, "%s %s", m_prompts[level], msg);
	}
	
	inline void print(std::ostream &out, const char *fmt, 
			   const char *prompt, const char *msg) {
		char buff[PRINT_BUFF_MAX];
		snprintf(buff, PRINT_BUFF_MAX, fmt, prompt, msg);
		/* get lock and write */
		std::lock_guard<std::mutex> lock(m_lock);
		out << buff << std::endl;
		out.flush();
	}
	
	inline void panic(int exit_code) {
		exit(exit_code);
	}
	
private:
	int m_level;
	std::mutex m_lock;
	std::map<int, const char*> m_prompts;
	DISALLOW_COPY_AND_ASSIGN(LogImpl);
};


class LogFileImpl : public LogImpl {
public:
	explicit LogFileImpl(const char* filename) 
			: m_filename(filename), m_log(new LogImpl()) {
		m_file.open(filename);
	}
	
	~LogFileImpl() { 
		this->close_file();
	}
	
	void set_file(const char* filename) {
		this->close_file();
		m_filename = filename;
		m_file.open(filename);
	}
	
	void close_file() {
		if (m_file.is_open())
			m_file.close();
	}
	
	std::string filename() const {
		return m_filename;
	}
	
	bool good() const { 
		return m_file.good();
	} 
	
	void _log(int level, const char *msg) {
		if (level == RAW_OUT_L) 
			m_log->print(m_file, "%s%s", "", msg);
		else
			m_log->log(level, msg, m_file, m_file);
	}
	
private:
	std::string m_filename;
	std::ofstream m_file;
	std::unique_ptr<LogImpl> m_log;
	DISALLOW_COPY_AND_ASSIGN(LogFileImpl);
};

	
} /* namespace _elib */
} /* namespace elib */
#endif /* _LOG_H */