#include "elib/log.h"
#include "_log.h"

#define BUFF_MAX 1024

#define __FMT_ARGS() char __fmt_buff[BUFF_MAX]; \
	va_list __args; \
	va_start(__args, msg); \
	vsnprintf(__fmt_buff, BUFF_MAX, msg, __args); \
	va_end(__args)

#define STATIC_FUNC_HANDLER(level) __FMT_ARGS(); \
	_static_log(level, __fmt_buff) 
	
#define LOGFILE_FUNC_HANDLER(level) __FMT_ARGS(); \
	m_impl->_log(level, __fmt_buff) 

	
namespace elib {

	
/* for static Log */
_elib::LogImpl g_log;


/* helper for static log */
inline void _static_log(int level, const char* msg) 
{
	/* special case for raw */
	if (level == _elib::RAW_OUT_L)
		g_log.print(std::cout, "%s%s", "", msg);
	else if (level == _elib::RAW_ERR_L)
		g_log.print(std::cerr, "%s%s", "", msg);
	else
		g_log.log(level, msg, std::cout, std::cerr);
}

void Log::set_level(int new_level) 
{
	g_log.set_level(new_level);
}

int Log::get_level() 
{
	return g_log.get_level();
}

void Log::debug(const char *msg, ... ) 
{
	STATIC_FUNC_HANDLER(DEBUG_L);
}

void Log::info(const char *msg, ... )
{
	STATIC_FUNC_HANDLER(INFO_L);
}

void Log::step(const char *msg, ... )
{
	STATIC_FUNC_HANDLER(STEP_L);
}

void Log::warning(const char *msg, ... )
{
	STATIC_FUNC_HANDLER(WARNING_L);
}

void Log::error(const char *msg, ... )
{
	STATIC_FUNC_HANDLER(ERROR_L);
}

void Log::fatal(const char *msg, ... )
{
	STATIC_FUNC_HANDLER(FATAL_L);
}

void Log::raw_out(const char *msg, ... )
{
	STATIC_FUNC_HANDLER(_elib::RAW_OUT_L);
}

void Log::raw_err(const char *msg, ... )
{
	STATIC_FUNC_HANDLER(_elib::RAW_ERR_L);
}


LogFile::LogFile(const char *filename) : m_impl(new _elib::LogFileImpl(filename)) 
{
} 

LogFile::~LogFile() 
{ 
}

void LogFile::set_file(const char *filename) 
{
	m_impl->set_file(filename);
}

void LogFile::close_file()
{
	m_impl->close_file();
}

std::string LogFile::filename() const
{
	return m_impl->filename();
}

bool LogFile::good() const
{
	return m_impl->good();
}

void LogFile::set_level(int new_level) 
{
	m_impl->set_level(new_level);
}

int LogFile::get_level() const
{
	return m_impl->get_level();
}

void LogFile::debug(const char *msg, ...) 
{
	LOGFILE_FUNC_HANDLER(DEBUG_L);
}

void LogFile::info(const char *msg, ...) 
{
	LOGFILE_FUNC_HANDLER(INFO_L);
}

void LogFile::step(const char *msg, ...) 
{
	LOGFILE_FUNC_HANDLER(STEP_L);
}

void LogFile::warning(const char *msg, ...) 
{
	LOGFILE_FUNC_HANDLER(WARNING_L);
}

void LogFile::error(const char *msg, ...) 
{
	LOGFILE_FUNC_HANDLER(ERROR_L);
}

void LogFile::fatal(const char *msg, ...) 
{
	LOGFILE_FUNC_HANDLER(FATAL_L);
}

void LogFile::raw_out(const char *msg, ...)
{
	LOGFILE_FUNC_HANDLER(_elib::RAW_OUT_L);
}

	
} /* namespace elib */