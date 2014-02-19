#ifndef ELIB_OPTIONS_OPTION_HPP
#define ELIB_OPTIONS_OPTION_HPP

# include <elib/options/fwd.hpp>

# include <string>
# include <map>
# include <memory>
# include <vector>

namespace elib { namespace options
{
    ////////////////////////////////////////////////////////////////////////////
    //
    class option
    {
    public:
        option();
        
        option(
            std::string const & xstring_key
          , std::vector< std::string > const & xvalue
        );
        
        std::string string_key;
        int position_key;
        
        std::vector< std::string > value;
        std::vector< std::string > original_tokens;
        
        bool unregistered;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class option_description
    {
    public:
        option_description();
        option_description(const char* name, const value_semantic* s);
        option_description(const char* name, const value_semantic* s, const char* desc);
        
        virtual ~option_description();
        
        match_result match(std::string const & opt, bool aprox);
        
        std::string const & key(std::string const & opt) const;
        
        std::string canonical_name() const;
        
        std::string const & long_name() const;
        std::string const & description() const;
        
        std::shared_ptr<const value_semantic> semantics() const;
        
        std::string format_name() const;
        std::string format_parameter() const;
        
    private:
        option_description & set_name(const char *name);
        
        std::string m_short_name, m_long_name, m_desc;
        std::shared_ptr<const value_semantic> m_semantics;
    };  

    ////////////////////////////////////////////////////////////////////////////
    //
    class option_description_init
    {
    public:
        option_description_init(option_description *owner);
        
        option_description_init &
        operator()(const char* name, const char* desc);
        
        option_description_init &
        operator()(const char* name, value_semantic const* s);
        
        option_description_init &
        operator()(const char* name, value_semantic const* s, const char* desc);

    private:
        option_description* m_owner;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class options_description
    {
    public:
        options_description();
        options_description(std::string const & caption);
        
        void add(std::shared_ptr<option_description> opt);
        
        options_description & add(options_description const &);
        
        option_description_init add_options();
        
        bool has_option(std::string const & name) const;
        
        option_description const & find(std::string const & name) const;
        option_description const * find_nothrow(std::string const & name) const;
        
        std::vector< std::shared_ptr<option_description> > const &
        options() const;
        
    private:
        std::map<std::string, int> m_map_to_index;
        std::vector< std::shared_ptr<option_description> > m_options;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class positional_options_description
    {
    public:
        positional_options_description();
        
        positional_options_description &
        add(std::string const & name, int max_count);
        
        unsigned max_total_count() const;
        
        std::string const & name_for_position(unsigned pos) const;

    private:
        std::vector< std::string > m_names;
        std::string m_trailing;
    };
}}                                                          // namespace elib
#endif /* ELIB_OPTIONS_OPTION_HPP */