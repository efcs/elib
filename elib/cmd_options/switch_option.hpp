#ifndef ELIB_CMD_OPTIONS_SWITCH_OPTION_HPP
#define ELIB_CMD_OPTIONS_SWITCH_OPTION_HPP

# include <elib/cmd_options/fwd.hpp>
# include <elib/cmd_options/basic_option.hpp>

namespace elib { namespace cmd_options
{
    template <class Traits>
    class switch_option : public basic_option
    {
    public:
        using traits = Traits;
    
    public:
        switch_option(
            std::string const & name, std::string const & desc
          , bool default_val = false
          , semantics_t sem = semantics_t::none
          );
        
        bool value() const noexcept;
        bool default_value() const noexcept;
        
       
        
    private:
        std::size_t m_count;
        bool m_val;
        bool m_default;
    };
}}                                                          // namespace elib
#endif /* ELIB_CMD_OPTIONS_SWITCH_OPTION_HPP */