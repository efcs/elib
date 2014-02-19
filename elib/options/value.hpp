#ifndef ELIB_OPTIONS_VALUE_HPP
#define ELIB_OPTIONS_VALUE_HPP

# include <elib/options/fwd.hpp>
# include <elib/any.hpp>

# include <functional>
# include <string>
# include <vector>
# include <typeinfo>

namespace elib { namespace options
{   
    ////////////////////////////////////////////////////////////////////////////
    //
    class value_semantic
    {
    public:
        virtual std::string name() const = 0;
        
        virtual unsigned min_tokens() const = 0;
        virtual unsigned max_tokens() const = 0;
        
        virtual bool is_composing() const = 0;
        virtual bool is_required() const = 0;
        
        virtual void parse(
            elib::any & store, 
            std::vector<std::string> const & new_tokens
          ) const = 0;
        
        virtual bool apply_default(elib::any & store) const = 0;
        
        virtual void notify(elib::any const & store) const = 0;
        
        virtual ~value_semantic() noexcept {}
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class untyped_value
      : public value_semantic
    {
    public:
        untyped_value(bool zero_tokens = false)
          : m_zero_tokens(zero_tokens)
        {}
        
        std::string name() const;
        
        unsigned min_tokens() const;
        unsigned max_tokens() const;
        
        bool is_composing() const;
        bool is_required() const;
        
        void parse(
            elib::any & store
          , std::vector<std::string> const & new_tokens
        ) const;
        
        bool apply_default(elib::any & store) const;
        
        void notify(elib::any const &) const;

    private:
        bool m_zero_tokens;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class typed_value_base
    {
    public:
        virtual std::type_info const & value_type() const = 0;
        virtual ~typed_value_base() noexcept {}
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T>
    class typed_value
      : public value_semantic
      , public typed_value_base
    {
    public:
        typed_value(T *store_to);
        
        typed_value* default_value(T const & v);
        typed_value* default_value(T const & v, std::string const & textual);
        
        typed_value* implicit_value(T const & v);
        typed_value* implicit_value(T const & v, std::string const & textual);
        
        typed_value* value_name(std::string const & name);
        
        typed_value* notifier(std::function<void(T const &)> f);
        
        typed_value* composing();
        typed_value* multitoken();
        typed_value* zero_tokens();
        typed_value* required();

    public:
        
        std::string name() const;
        
        bool is_composing() const;
        unsigned min_tokens() const;
        unsigned max_tokens() const;
        
        bool is_required() const;
        
        void parse(
            elib::any & store
          , std::vector<std::string> const & new_tokens
        ) const;
        
        virtual bool apply_default(elib::any & store) const;
        void notify(elib::any const & store) const;
        
        std::type_info const & value_type() const;
        
    private:
        std::string m_value_name;
        
        elib::any m_default_value;
        std::string m_default_value_str;
        
        elib::any m_implicit_value;
        std::string m_implicit_value_str;
        
        bool m_composing, m_implicit, m_multitoken, m_zero_tokens, m_required;
        
        std::function<void(T const &)> m_notifier;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T>
    typed_value<T>* value();
    
    template <class T>
    typed_value<T>* value(T* v);
    
    typed_value<bool>* bool_switch();
    typed_value<bool>* bool_switch(bool * v);
}}                                                          // namespace elib
#endif /* ELIB_OPTIONS_VALUE_HPP */