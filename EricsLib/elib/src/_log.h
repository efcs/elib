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
	

using lock_guard = std::lock_guard<std::mutex>;
using rec_lock_guard = std::lock_guard<std::recursive_mutex>;


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
	
	virtual ~LogImpl() {
		
	}
	
	inline void set_level(int new_level) {
		lock_guard lock(m_lock);
		m_level = new_level; 
	}
	
	inline int get_level() const {
		return m_level; 
	}	
	
	/* do not use with raw levels */
	inline void log(int level, const char *msg, 
					std::ostream &out, std::ostream &err) {
		lock_guard lock(m_lock);
		if (m_level >= level && level <= STEP_L)
			print(out, "%s %s", m_prompts[level], msg);
		else if (m_level >= level && level >= WARNING_L)
			print(err, "%s %s", m_prompts[level], msg);
	}
	
	inline void print(std::ostream &out, const char *fmt, 
			   const char *prompt, const char *msg) {
		
		char buff[PRINT_BUFF_MAX];
		snprintf(buff, PRINT_BUFF_MAX, fmt, prompt, msg);
		buff[PRINT_BUFF_MAX-1] = '\0';
		/* get lock and write */
		lock_guard lock(m_write_lock);
		out << buff << std::endl;
		out.flush();
	}
	
	inline void panic(int exit_code) {
		exit(exit_code);
	}
	
private:
	int m_level;
	std::mutex m_lock, m_write_lock;
	std::map<int, const char*> m_prompts;
	DISALLOW_COPY_AND_ASSIGN(LogImpl);
};


class LogFileImpl : public LogImpl {
public:
	explicit LogFileImpl(const char* filename) 
					: LogImpl(), m_filename(filename) {
		m_file.open(filename);
	}
	
	~LogFileImpl() { 
		this->close_file();
	}
	
	void set_file(const char* filename) {
		rec_lock_guard lock(m_file_lock);
		this->close_file();
		m_filename = filename;
		m_file.open(filename);
	}
	
	void close_file() {
		rec_lock_guard lock(m_file_lock);
		if (m_file.is_open())
			m_file.close();
	}
	
	std::string filename() const {
		rec_lock_guard lock(m_file_lock);
		return m_filename;
	}
	
	bool good() const { 
		rec_lock_guard lock(m_file_lock);
		return m_file.good();
	} 
	
	void _log(int level, const char *msg) {
		if (level == RAW_OUT_L) 
			this->print(m_file, "%s%s", "", msg);
		else
			this->log(level, msg, m_file, m_file);
	}
	
private:
	std::string m_filename;
	mutable std::recursive_mutex m_file_lock;
	std::ofstream m_file;
	DISALLOW_COPY_AND_ASSIGN(LogFileImpl);
};

	
} /* namespace _elib */
} /* namespace elib */
#endif /* _LOG_H */