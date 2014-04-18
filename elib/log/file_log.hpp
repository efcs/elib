#ifndef ELIB_LOG_FILE_LOG_HPP
#define ELIB_LOG_FILE_LOG_HPP

#include <elib/log/basic_log.hpp>
#include <elib/log/log_level.hpp>

#include <memory>
#include <fstream>

namespace elib 
{
  namespace log
  {

# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif    
    /* file_log implements the basic_log interface,
    * for basic_log method documentation see log.h */
    class file_log final : public basic_log {
    public:
        file_log() = default;
        /* open file for output */
        file_log(const std::string & filename);
        
        virtual ~file_log() { }
        
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
    private:
      
        std::ostream& _get_stream(level_e l);
      
        std::string m_filename {};
        std::ofstream m_out {};
        
    };
    
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

  } /* namespace log */
} /* namespace elib */
#endif /* ELIB_LOG_FILE_LOG_HPP */