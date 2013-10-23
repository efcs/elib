#ifndef ELIB_ARGP_ARGP_ERROR_HPP
# define ELIB_ARGP_ARGP_ERROR_HPP

# include <elib/config.hpp>

# include <string>
# include <exception>
# include <memory>
# include <utility>

namespace elib 
{
  namespace argp
  {
    
    
    class argp_error : public std::exception
    {
    public:
      explicit argp_error(const char* msg)
        : m_what{std::make_shared<std::string>(msg)}
      { }
      
      explicit argp_error(std::string msg)
        : m_what{std::make_shared<std::string>(std::move(msg))}
      { }
      
      
      virtual ~argp_error() noexcept = default;
      
      virtual const char* what() const noexcept { return m_what->c_str(); }
        
      //
    private:
      //
      
      std::shared_ptr<std::string> m_what;
      
    };                                                      // class argp_error
    
    
    class runtime_error : public argp_error
    {
    public:
      
      explicit runtime_error(const char* msg)
        : argp_error{msg}
      { }
      
      explicit runtime_error(std::string msg)
        : argp_error{msg}
      { }
      
      virtual ~runtime_error() noexcept = default;
      
    };                                                   // class runtime_error
    
    
    class logic_error : public argp_error
    {
    public:
      
      explicit runtime_error(const char* msg)
        : argp_error{msg}
      { }
      
      explicit logic_error(std::string msg)
        : argp_error{msg}
      { }
      
      virtual ~logic_error() noexcept = default;
      
    };                                                   // class logic_error
    
    
  }                                                           // namespace argp
}                                                           // namespace elib
#endif /* ELIB_ARGP_ARGP_ERROR_HPP */