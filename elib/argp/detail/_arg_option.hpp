#ifndef ELIB_ARGP__ARG_OPTION_HPP
#define ELIB_ARGP__ARG_OPTION_HPP

#include <string>


namespace elib {
namespace argp {
    

enum class arg_type_e;
class arg_token;
    
    
namespace detail {
    
class arg_option {
public:
    arg_option(arg_type_e arg_type,
               const std::string & name,
               const std::string & cmd_desc,
               const std::string & desc);
    
    virtual ~arg_option() { }
    
    inline arg_type_e
    arg_type() const
    {return m_arg_type; }
    
    const std::string & 
    command_description() const;
    
    const std::string & 
    description() const;
    
    std::string 
    fmt_description() const;
    
    virtual void 
    notify(const arg_token &tk) = 0;

public:
    virtual bool has_implicit_value() const = 0;
    
    bool has_short_name() const;
    bool has_long_name() const;
    
    const std::string & short_name() const;
    const std::string & long_name() const;
    
    bool match(const std::string & name) const;
    bool match(const std::string & name, std::string & dest) const;
    
    bool match(const arg_option & opt) const;
    bool match(const arg_option & opt, std::string & dest) const;
private:
    void parse_name_and_set(const std::string & s);
    void handle_name_part(std::string s);
private:
    arg_type_e m_arg_type;
    std::string m_cmd_desc, m_desc;
    std::string m_short_name{}, m_long_name{};
};
    

} /* namespace detail */    
} /* namespace argp */    
} /* namespace elib */
#endif /* ELIB_ARGP__ARG_OPTION_HPP */