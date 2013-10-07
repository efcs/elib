#ifndef ELIB_ARGP_ARG_DESCRIPTION_HPP
# define ELIB_ARGP_ARG_DESCRIPTION_HPP

# include <elib/argp/v2/config.hpp>

# include <elib/argp/v2/detail/parse_helper.hpp>

# include <string>
# include <exception>
# include <memory>
# include <utility>

namespace elib 
{
  namespace argp
  {
    
    
    class invalid_arg_description : public std::exception
    {
    public:
      invalid_arg_description()
        : m_what_arg{std::make_shared<std::string>("invalid arg description")}
      { }
      
      explicit invalid_arg_description(const std::string& short_desc)
        : invalid_arg_description()
      {
        m_format_arg(short_desc);
      }
      
      invalid_arg_description(const std::string& short_desc, 
                              const char* msg)
        : invalid_arg_description() 
      {
        m_format_arg(short_desc, msg);
      }
                        
      virtual const char* what() const noexcept
      {
        return m_what_arg->c_str();
      }
      
      //
    private:
      //
      
      void m_format_arg(const std::string& short_desc, const char* msg=nullptr)
      {
        *m_what_arg += "for arg (\"" + short_desc + "\")";
        if (msg)
        {
          *m_what_arg += " " + msg;
        }
      }
      
      std::shared_ptr<std::string> m_what_arg{nullptr};
      
    };                                         // class invalid_arg_description
    
    class arg_description
    {
    public:
      arg_description(const std::string& short_desc,
                      const std::string& long_desc)
        : m_short_desc{short_desc}, m_long_desc{long_desc}
      {
        // can throw!
        m_parse_names();
      }
      
      // modify description, 
      // return *this to allow easy composing of modifications
      arg_description& required(bool b) noexcept
      {
        m_required = b;
        return *this;
      }
      
      arg_description& optional(bool b) noexcept
      {
        m_optional = b;
        return *this;
      }
        
      bool has_short_name() const noexcept
      {
        return m_short_name.size() != 0;
      }
      
      bool has_long_name() const noexcept
      {
        return m_long_name.size() != 0;
      }
      
      bool has_arg_name() const noexcept
      {
        return m_long_name.size() != 0;
      }
      
      bool has_arg() const noexcept
      {
        return has_arg_name();
      }
      
      const std::string& short_description() const noexcept
      {
        return m_short_desc;
      }
      
      const std::string& long_description() const noexcept
      {
        return m_long_desc;
      }
      
      const std::string& short_name() const noexcept
      {
        return m_short_name;
      }
      
      const std::string& long_name() const noexcept
      {
        return m_long_name;
      }
      
      const std::string& arg_name() const noexcept
      {
        return m_arg_name;
      }
      
      bool required() const noexcept
      {
        return m_required;
      }
      
      bool composing() const noexcept
      {
        return m_composing;
      }
                      
    private:
      
      // m_short_desc must be set
      void m_parse_names();
     
      std::string m_short_desc, m_long_desc;
      
      std::string m_short_name{}, m_long_name{}, m_arg_name{};
      
      bool m_required{false}, m_composing{false};
                      
    };                                                 // class arg_description
    
  }                                                           // namespace argp
}                                                           // namespace elib
#endif /* ELIB_ARGP_ARG_DESCRIPTION_HPP */