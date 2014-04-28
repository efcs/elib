#ifndef ELIB_CMD_OPTIONS_BASIC_OPTION_HPP
#define ELIB_CMD_OPTIONS_BASIC_OPTION_HPP

# include <elib/cmd_options/fwd.hpp>
# include <elib/cmd_options/option_semantics.hpp>
# include <elib/cmd_options/parsed_option.hpp>
# include <elib/aux.hpp>
# include <elib/any.hpp>
# include <memory>
# include <string>
# include <typeinfo>
# include <vector>
# include <cstddef>

namespace elib { namespace cmd_options
{
    namespace detail
    {
        constexpr struct basic_option_tag_t {}
        basic_option_tag {};
        
        constexpr struct switch_option_tag_t : basic_option_tag_t {} 
        switch_option_tag {};
        
        constexpr struct positional_option_tag_t : basic_option_tag_t {} 
        positional_option_tag {};
        
        constexpr struct value_option_tag_t : basic_option_tag_t {}
        value_option_tag {};
        
        constexpr struct multi_option_tag_t : value_option_tag_t {}
        multi_option_tag {};
    }                                                       // namespace detail
    
    class basic_option
    {
    protected:
        basic_option() = delete;
        
        basic_option(
            detail::switch_option_tag_t
          , option_semantics sem
          , std::string const & name
          , std::string const & desc
          , std::string const & type_name
          , std::shared_ptr<elib::any> default_value = std::shared_ptr<elib::any>()
          );
        
        basic_option(
            detail::positional_option_tag_t
          , option_semantics sem
          , std::string const & name
          , std::string const & desc
          , std::string const & type_name
          , std::type_info const & xtarget_type
          , unsigned pos
          , std::shared_ptr<elib::any> default_value = std::shared_ptr<elib::any>()
          );
        
        basic_option(
            detail::value_option_tag_t
          , option_semantics sem
          , std::string const & name
          , std::string const & desc
          , std::string const & type_name
          , std::type_info const & xtarget_type
          , std::shared_ptr<elib::any> default_value = std::shared_ptr<elib::any>()
          );
        
        basic_option(
            detail::multi_option_tag_t
          , option_type opt_type
          , option_semantics sem
          , std::string const & name
          , std::string const & desc
          , std::string const & type_name
          , std::type_info const & xtarget_type
          , std::shared_ptr<elib::any> default_value = std::shared_ptr<elib::any>()
          );
        
        virtual ~basic_option() {}
        
    public:
        option_type type() const noexcept
        {
            return m_option_type;
        }
        bool is_positional() const noexcept
        {
            return m_option_type == option_type::positional_option;
        }
        
    public:
        bool has_short_name() const noexcept
        {
            return not is_positional() 
                && not m_short_name.empty();
        }
        
        bool has_long_name() const noexcept
        {
            return not is_positional() 
                && not m_long_name.empty();
        }
        
        std::string const & short_name() const noexcept
        {
            return m_short_name;
        }
        
        std::string const & long_name() const noexcept
        {
            return is_positional() ? m_short_name : m_long_name;
        }
        
        std::string const & canonical_name() const noexcept
        {
            return is_positional() || has_long_name() 
                ? m_long_name 
                : m_short_name;
        }
        
        std::string const & description() const noexcept
        {
            return m_description;
        }
        
        std::string const & type_name() const noexcept
        {
            return m_type_name;
        }
        
        std::type_info const & target_type() const noexcept
        {
            return *m_target_type;
        }
        
        
        unsigned position_key() const noexcept
        {
            return m_position_key;
        }
        
        std::string const & string_key() const noexcept
        {
            return is_positional() ? m_short_name : canonical_name();
        }
        
    public:
        bool matches(std::string const & s) const
        {
            return ((not is_positional()) 
              || (has_short_name() && m_short_name == s)
              || (has_long_name() && m_long_name == s));
              
        }
    
        bool matches(unsigned pos_key) const
        {
            return is_positional() 
              && (m_position_key == wildcard_position_key
                 || m_position_key == pos_key);
        }
        
        bool matches(basic_option const & other) const
        {
            if (other.is_positional()) {
                return matches(other.position_key());
            }
            else if (is_positional()) {
                return false;
            } else {
                return ((has_long_name() && other.has_long_name() 
                          && m_long_name == other.m_long_name)
                        || (has_short_name() && other.has_short_name()
                            && m_short_name = other.m_short_name));
            }
        }
        
        bool matches(parsed_option const & opt) const
        {
            if (opt.key_info == key_type::positional) {
                return is_positional() 
                  && (m_position_key == wildcard_position_key
                     || m_position_key == opt.position_key)
            } 
            else if (opt.key_info == key_type::short_name) {
                return has_short_name() && m_short_name == opt.string_key;
            }
            else if (opt.key_info == key_type::long_name) {
                return has_long_name() && m_long_name == opt.string_key;
            }
        }
        
    public:
        option_semantics semantics() const noexcept
        {
            return m_semantics;
        }
        
        bool required() const noexcept
        {
            return is_set(m_semantics, option_semantics::required);
        }
        
        bool value_required() const noexcept
        {
            return is_set(m_semantics, option_semantics::value_required);
        }
        
        bool multi_token() const noexcept
        {
            return is_set(m_semantics, option_semantics::multi_token);
        }
        
        bool composing() const noexcept
        {
            return is_set(m_semantics, option_semantics::composing);
        }
        
        bool has_default_value() const noexcept
        {
            return is_set(m_semantics, option_semantics::has_default_value);
        }
        
        
    public:
        
        std::vector<unsigned> const & position_keys() const noexcept
        {
            return m_position_keys;
        }
        
        std::size_t count() const
        {
            return m_position_keys.size();
        }
        
        std::shared_ptr<elib::any> default_value_pointer() const noexcept
        {
            return m_default_val;
        }
        
    public:
        void process(parsed_option const & opt)
        {
            ELIB_ASSERT(validate(opt));
            m_position_keys.push_back(opt.position_key);
            notify(opt);
        }
        
        virtual bool validate(parsed_option const &) const = 0;
        virtual void apply(parsed_option const &) = 0;
        virtual void finalize() = 0;
        
    private:
        
        void m_validate_state(detail::basic_option_tag_t);
        void m_validate_state(detail::switch_option_tag_t);
        void m_validate_state(detail::positional_option_tag_t);
        void m_validate_state(detail::value_option_tag_t);
        void m_validate_state(detail::multi_option_tag_t);
        
        void m_validate_semantics(detail::basic_option_tag_t);
        void m_validate_semantics(detail::switch_option_tag_t);
        void m_validate_semantics(detail::positional_option_tag_t);
        void m_validate_semantics(detail::value_option_tag_t);
        void m_validate_semantics(detail::multi_option_tag_t);
        
        void m_parse_names(detail::basic_option_tag_t, std::string const & names);
        void m_parse_names(detail::positional_option_tag_t, std::string const & names);
        
        
    private:
        option_type m_opt_type;
        option_semantics m_semantics;
        
        std::string m_short_name, m_long_name;
        std::string m_type_name;
        std::string m_description;
        
        unsigned m_position_key;
        
        std::vector<unsigned> m_position_keys;
        
        std::shared_ptr<elib::any> m_default_val;
        std::type_info const * m_target_type;
    };
}}                                                          // namespace elib
#endif /* ELIB_CMD_OPTIONS_BASIC_OPTION_HPP */