#include <elib/options/option.hpp>
#include <elib/options/error.hpp>

namespace elib { namespace options
{
    /////////////////////////////////////////////////////////////////////////////
    // option_description
    void option_description::m_set_name(std::string const & name)
    {
        std::string::size_type pos = name.find(',');
        if (pos == std::string::npos)
            m_set_long_name(name);
        else
        {
            m_set_long_name(name.substr(0, pos));
            m_set_short_name(name.substr(pos + 1));
        }
    }
    
    //TODO
    void option_description::m_set_long_name(std::string const &)
    {}
    
    //TODO
    void option_description::m_set_short_name(std::string const &)
    {}
    
    
}}                                                   // namespace elib::options