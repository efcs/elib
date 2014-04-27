#ifndef ELIB_OPTIONS_VARIABLE_MAP_HPP
#define ELIB_OPTIONS_VARIABLE_MAP_HPP

# include <elib/options/fwd.hpp>
# include <elib/any.hpp>

# include <memory>
# include <string>

namespace elib { namespace options
{
    ////////////////////////////////////////////////////////////////////////////
    class variable_value
    {
    public:
        variable_value();
        variable_value(elib::any const &, bool is_default);
        
        template <class T>
        T const & as() const;
        
        template <class T>
        T & as();
        
        bool empty() const;
        bool defaulted() const;
        
        elib::any const & value() const;
        elib::any & value();

    private:
        elib::any m_value;
        bool m_defaulted;
        
        std::shared_ptr<const value_semantic> m_semantics;
        
        friend void store(parsed_options const &, variable_map &);
        friend class variable_map;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class variable_map;
    
    ////////////////////////////////////////////////////////////////////////////
    //
    void store(parsed_options const &, variable_map &);
    
    ////////////////////////////////////////////////////////////////////////////
    //
    void notify(variable_map &);
}}                                                          // namespace elib
#endif /* ELIB_OPTIONS_VARIABLE_MAP_HPP */
