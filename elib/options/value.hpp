#ifndef ELIB_OPTIONS_VALUE_HPP
#define ELIB_OPTIONS_VALUE_HPP

# include <elib/options/config.hpp>
# include <elib/options/fwd.hpp>
# include <elib/aux.hpp>
# include <elib/any.hpp>

# include <functional>
# include <string>
# include <vector>
# include <memory>
# include <typeinfo>

namespace elib { namespace options
{   
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
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
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
    ////////////////////////////////////////////////////////////////////////////
    //
    class untyped_value
      : public value_semantic
    {
    public:
        untyped_value(bool zero_tokens = false)
          : m_zero_tokens(zero_tokens)
        {}
        
        untyped_value(untyped_value const &) = delete;
        untyped_value(untyped_value &&) = delete;
        untyped_value & operator=(untyped_value const &) = delete;
        untyped_value & operator=(untyped_value &&) = delete;
        
        std::string name() const { return "untyped option"; }
        
        unsigned min_tokens() const { return !m_zero_tokens; }
        unsigned max_tokens() const { return !m_zero_tokens;}
        
        bool is_composing() const { return false; }
        bool is_required() const { return false; }
        
        void parse(
            elib::any & store
          , std::vector<std::string> const & new_tokens
        ) const;
        
        bool apply_default(elib::any &) const { return false; }
        
        void notify(elib::any const &) const {}

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
    template <class T, class Converter>
    class typed_value
      : public value_semantic
      , public typed_value_base
    {
    public:
        typed_value();
        typed_value(T & store_to);
        
        typed_value(typed_value const &) = delete;
        typed_value(typed_value &&) = delete;
        typed_value & operator=(typed_value const &) = delete;
        typed_value & operator=(typed_value &&) = delete;
        
        typed_value & default_value(T const & v)
        {
            m_default_value = v;
            m_default_value_str = "";
            return *this;
        }
        
        typed_value & default_value(T const & v, std::string const & textual)
        {
            m_default_value = v;
            m_default_value_str = textual;
            return *this;
        }
        
        typed_value & implicit_value(T const & v)
        {
            m_implicit_value = v;
            m_implicit_value_str = "";
            return *this;
        }
        
        typed_value & implicit_value(T const & v, std::string const & textual)
        {
            m_implicit_value = v;
            m_implicit_value_str = textual;
            return *this;
        }
        
        typed_value & value_name(std::string const & xname)
        {
            m_value_name = xname;
            return *this;
        }
        
        typed_value & notifier(std::function<void(T const &)> f)
        {
            m_notifier = f;
            return *this;
        }
        
        typed_value & composing() 
        {
            m_composing = true;
            return *this;
        }
        
        //TODO validate input
        typed_value & multitoken()
        {
            m_multitoken = true;
            return *this;
        }
        
        typed_value & zero_tokens()
        {
            m_zero_tokens = true;
            return *this;
        }
        
        typed_value & required()
        {
            m_required = true;
            return *this;
        }
        
       

    public:
        
        //TODO whats the point of this
        std::string name() const
        {
            return m_value_name;
        }
        
        bool is_composing() const noexcept 
        { 
            return m_composing; 
        }
        
        unsigned min_tokens() const
        {
            if (m_zero_tokens) return 0;
            return m_required;
        }
        
        unsigned max_tokens() const
        {
            if (m_zero_tokens) return 0;
            if (m_multitoken) return value_semantics_max_tokens;
            return 1;
        }
        
        bool is_required() const noexcept 
        { 
            return m_required; 
        }
        
        void parse(
            elib::any & store
          , std::vector<std::string> const & new_tokens
        ) const;
        
        virtual bool apply_default(elib::any & store) const
        {
            ELIB_ASSERT(m_default_value);
            store = m_default_value;
        }
        
        void notify(elib::any const & store) const
        {
            if (!m_notifier) return;
            m_notifier(any_cast<T const &>(store));
        }
        
        std::type_info const & value_type() const noexcept
        {
            return typeid(T);
        }
        
         bool validate() const;
        
    private:
        T* m_dest;
        std::shared_ptr<T> m_store;
        
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
    std::shared_ptr<typed_value<T>> value();
    
    template <class T>
    std::shared_ptr<typed_value<T>> value(T & v);
    
    std::shared_ptr<typed_value<bool>>  bool_switch();
    std::shared_ptr<typed_value<bool>>  bool_switch(bool & v);
}}                                                          // namespace elib
#endif /* ELIB_OPTIONS_VALUE_HPP */