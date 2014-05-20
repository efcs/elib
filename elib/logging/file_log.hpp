#ifndef ELIB_LOGGING_FILE_LOG_HPP
#define ELIB_LOGGING_FILE_LOG_HPP

# include <elib/logging/basic_log.hpp>
# include <elib/logging/log_level.hpp>
# include <fstream>

namespace elib { namespace logging { inline namespace v1
{
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    /* file_log implements the basic_log interface,
    * for basic_log method documentation see log.h */
    class file_log final : public basic_log 
    {
    public:
        file_log() = default;
        
        /* open file for output */
        file_log(const std::string & xfilename)
        {
            open(xfilename);
        }
        
        /* return the path to the current file */
        std::string const & filename() const noexcept
        {
            return m_filename;
        }
        
        /* open a new output file */
        bool open(
            const std::string & xfilename
          , std::ios_base::openmode mode = std::ios_base::app
          )
        {
            m_filename = xfilename;
            m_out.open(m_filename, mode);
            return m_out.good();
        }
        
        /* check if the output file is good */
        bool good() const
        {
            return m_out.good();
        }
        
        /* close the output file */
        void close()
        {
            m_out.close();
        }
        
    private:
      
        std::ostream & m_get_stream(level_e)
        {
            return m_out;
        }

    private:
        std::string m_filename;
        std::ofstream m_out;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

}}}                                                         // namespace elib
#endif /* ELIB_LOGGING_FILE_LOG_HPP */