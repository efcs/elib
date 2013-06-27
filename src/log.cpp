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
#include "elib/log.h"
#include "_log.h"

#define BUFF_MAX 1024

#define __FMT_ARGS() char __fmt_buff[BUFF_MAX]; \
	va_list __args; \
	va_start(__args, msg); \
	vsnprintf(__fmt_buff, BUFF_MAX, msg, __args); \
	va_end(__args)
	
	
#define LOG_FUNC_HANDLER(level) __FMT_ARGS(); \
	m_impl->log(level, __fmt_buff) 

	
namespace elib {


Log::Log() : m_impl(new _elib::LogImpl(LDEFAULT))
{
}

Log::Log(int level) : m_impl(new _elib::LogImpl(level))
{
}

Log::~Log()
{
}

std::string Log::get_prompt(int level) const
{
	return m_impl->get_prompt(level);
}

bool Log::set_prompt(int level, const std::string &prompt)
{
	return m_impl->set_prompt(level, prompt);
}

void Log::set_level(int level)
{
	m_impl->set_level(level);
}

int Log::modify_level(int delta)
{
	return m_impl->modify_level(delta);
}

int Log::get_level() const
{
	return m_impl->get_level();
}

void Log::log(int level, const char *msg, ... ) 
{
	LOG_FUNC_HANDLER(level);
}

void Log::log(int level, const std::string &msg)
{
	m_impl->log(level, msg.c_str());
}
	
void Log::debug(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LDEBUG);
}

void Log::info(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LINFO);
}

void Log::step(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LSTEP);
}

void Log::warning(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LWARNING);
}

void Log::error(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LERROR);
}

void Log::fatal(const char *msg, ...)
{
	LOG_FUNC_HANDLER(LFATAL);
}
	
void Log::raw_out(const char *msg, ...)
{
	LOG_FUNC_HANDLER(LRAW_OUT);
}

void Log::raw_out(const std::string &msg)
{
	m_impl->log(LRAW_OUT, msg.c_str());
}

void Log::raw_err(const char *msg, ...)
{
	LOG_FUNC_HANDLER(LRAW_ERR);
}

void Log::raw_err(const std::string &msg)
{
	m_impl->log(LRAW_ERR, msg.c_str());
}


/* --------------- FILE LOG ---------------------- */
FileLog::FileLog(const char* filename) 
			: m_impl(new _elib::FileLogImpl(LDEFAULT, filename))
{
}


FileLog::FileLog(int level, const char *filename) 
			: m_impl(new _elib::FileLogImpl(level, filename))
{
}

FileLog::~FileLog()
{
}

void FileLog::set_file(const char* filename)
{
	m_impl->set_file(filename);
}

std::string FileLog::filename() const
{
	return m_impl->filename();
}

void FileLog::close()
{
	m_impl->close();
}

std::string FileLog::get_prompt(int level) const
{
	return m_impl->get_prompt(level);
}

bool FileLog::set_prompt(int level, const std::string &prompt)
{
	return m_impl->set_prompt(level, prompt);
}

void FileLog::set_level(int level)
{
	m_impl->set_level(level);
}

int FileLog::modify_level(int delta)
{
	return m_impl->modify_level(delta);
}

int FileLog::get_level() const
{
	return m_impl->get_level();
}

void FileLog::log(int level, const char *msg, ... ) 
{
	LOG_FUNC_HANDLER(level);
}

void FileLog::log(int level, const std::string &msg)
{
	m_impl->log(level, msg.c_str());
}
	
void FileLog::debug(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LDEBUG);
}

void FileLog::info(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LINFO);
}

void FileLog::step(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LSTEP);
}

void FileLog::warning(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LWARNING);
}

void FileLog::error(const char *msg, ... )
{
	LOG_FUNC_HANDLER(LERROR);
}

void FileLog::fatal(const char *msg, ...)
{
	LOG_FUNC_HANDLER(LFATAL);
}
	
void FileLog::raw_out(const char *msg, ...)
{
	LOG_FUNC_HANDLER(LRAW_OUT);
}

void FileLog::raw_out(const std::string &msg)
{
	m_impl->log(LRAW_OUT, msg.c_str());
}

void FileLog::raw_err(const char *msg, ...)
{
	LOG_FUNC_HANDLER(LRAW_ERR);
}

void FileLog::raw_err(const std::string &msg)
{
	m_impl->log(LRAW_ERR, msg.c_str());
}


} /* namespace elib */