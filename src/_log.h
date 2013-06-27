/* 
 * Copyright (C) 2013  Eric Fiselier
 * 
 * This file is part of elib.
 *
 * elib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * elib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elib.  If not, see <http://www.gnu.org/licenses/>.
 */
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


inline bool is_raw_level(int level)
{
	return (level == LRAW_OUT || level == LRAW_ERR);
}

inline bool is_basic_level(int level)
{
	return (level >= LDEBUG && level <= LFATAL);
}

inline bool is_valid_level(int level) 
{ 
	return (is_raw_level(level) || is_basic_level(level));
}


class LogImpl
{
private:
	friend class FileLogImpl;
protected:
	LogImpl() { }
public:
	explicit LogImpl(int level) : m_level(level), 
				m_out(&std::cout), m_err(&std::cerr) { }
	
	virtual ~LogImpl() { }
	
	inline std::string get_prompt(int level) const {
		if (! is_valid_level(level))
			return std::string("");
		
		lock_guard lock(m_lock);
		return m_prompts.at(level);
	}
	
	inline bool set_prompt(int level, const std::string &prompt){
		if (! is_basic_level(level))
			return false;
		
		lock_guard lock(m_lock);
		m_prompts[level] = prompt;
		return true;
	}
	
	inline void set_level(int n_level) {
		lock_guard lock(m_lock);
		m_level = n_level;
	}
	
	inline int modify_level(int delta) {
		lock_guard lock(m_lock);
		m_level += delta;
		return m_level;
	}
	
	inline int get_level() const {
		return m_level;
	}
	
	inline void log(int level, const char *msg) {
		if (! _should_print(level))
			return;
	
		lock_guard lock(m_lock);
		_get_stream(level) << m_prompts[level] << msg << std::endl;
	}
	
private:
	virtual std::ostream& _get_stream(int level) {
		if (level == LRAW_OUT || (level >= LDEBUG && level <= LSTEP)) 
			return *m_out;
		 else 
			return *m_err;
	}
	
	inline bool _should_print(int level) const {
		return (is_raw_level(level) || 
				(is_basic_level(level) && m_level <= level));
	}
	
private:
	int m_level;
	mutable std::mutex m_lock;
	std::ostream *m_out, *m_err;
	std::map<int, std::string> m_prompts = {
								{LDEBUG, "Debug: "},
								{LINFO, "Info: "},
								{LSTEP, "--> "},
								{LWARNING, "Warning: "},
								{LERROR, "ERROR: "},
								{LFATAL, "FATAL: "},
								{LRAW_OUT, ""},
								{LRAW_ERR, ""} };
								
	DISALLOW_COPY_AND_ASSIGN(LogImpl);
};


class FileLogImpl : public LogImpl {
public:
	FileLogImpl(int level, const char* filename) : LogImpl() {
		m_level = level;
		set_file(filename);
		m_out = &m_file;
		m_err = &m_file;
	}
	
	~FileLogImpl() { 
		if (m_file.is_open())
			m_file.close();
	}
	
	void set_file(const char* filename) {
		lock_guard lock(m_lock);
		rec_lock_guard flock(m_file_lock);
		
		if (m_file.is_open())
			m_file.close();
		
		m_filename = filename;
		m_file.open(filename);
	}
	
	void close() {
		lock_guard lock(m_lock);
		rec_lock_guard flock(m_file_lock);
		
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
		
private:
	std::string m_filename;
	std::ofstream m_file;
	mutable std::recursive_mutex m_file_lock;
	DISALLOW_COPY_AND_ASSIGN(FileLogImpl);
};

	
} /* namespace _elib */
} /* namespace elib */
#endif /* _LOG_H */