#ifndef ELIB_ARGP_DETAIL_BASIC_OPTION_HPP
#define ELIB_ARGP_DETAIL_BASIC_OPTION_HPP

# include <elib/argp/fwd.hpp>
# include <elib/argp/parsed_option.hpp>
# include <elib/argp/option_semantics.hpp>
# include <elib/any.hpp>

# include <memory>
# include <string>
# include <vector>

namespace elib { namespace argp { namespace detail
{
    constexpr struct switch_tag_t {} switch_tag {};
    constexpr struct option_tag_t {} option_tag {};
    constexpr struct positional_tag_t {} positional_tag {};
    
    
    class basic_option
    {
    protected:
        basic_option(
            switch_tag_t
          , std::string xname, std::string xdesc
          , option_semantics sem
          , elib::any xdefault, std::string default_str
          , elib::any ximplicit, std::string implicit_str
          );
        
        basic_option(
            option_tag_t
          , std::string xname, std::string xdesc, std::string xparam_name
          , option_semantics sem
          , elib::any xdefault, std::string default_str
          , elib::any ximplicit, std::string implicit_str
          );
        
        basic_option(
            positional_tag_t
          , std::string xname, std::string xdesc, std::string xparam_name
          , option_semantics sem
          , elib::any xdefault, std::string default_str
          , elib::any ximplicit, std::string implicit_str
          );
            
    
        virtual ~basic_option() {};
    public:
        std::string const & name() const noexcept;
        std::string const & parameter_name() const noexcept;
        std::string const & description() const noexcept;
        
        std::string formatted_name() const;
        std::string formatted_parameter() const;
        
    public:
        bool has_long_name() const noexcept;
        bool has_short_name() const noexcept;
        
        std::string const & long_name() const;
        std::string const & short_name() const;
        
        std::string const & string_key() const noexcept;
        unsigned position_key() const noexcept;
        
        bool matches(basic_option const & opt) const;
        
    public:
        option_semantics semantics() const noexcept;
        
        bool required() const noexcept;
        bool composing() const noexcept;
        bool optional_value() const noexcept;
        bool required_value() const noexcept;
        bool multi_value() const noexcept;
    private:
        option_type m_opt_type;
        option_semantics m_semantics;
        
        std::string m_description;
        
        std::string m_short_name, m_long_name;
        unsigned m_position_key;
        
        std::vector<parsed_option> m_parsed_options;
        
        std::string m_parameter_name;
        elib::any m_value;
        
        std::shared_ptr<elib::any> m_default_value;
        std::string m_default_value_name;
        
        std::shared_ptr<elib::any> m_implicit_value;
        std::string m_implicit_value_name;
    };
}}}                                                         // namespace elib
#endif /* ELIB_ARGP_DETAIL_BASIC_OPTION_HPP */