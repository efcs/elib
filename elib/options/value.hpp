#ifndef ELIB_OPTIONS_VALUE_HPP
#define ELIB_OPTIONS_VALUE_HPP

# include <elib/options/config.hpp>
# include <elib/options/fwd.hpp>
# include <elib/options/detail/opt_lexical_cast.hpp>
# include <elib/aux.hpp>
# include <elib/any.hpp>
# include <elib/lexical_cast.hpp>
# include <elib/optional.hpp>

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
        ELIB_DEFAULT_CLASS(value_semantic);
        
        virtual ~value_semantic() noexcept {}
        
        virtual std::string const & name() const = 0;
        
        virtual unsigned min_tokens() const = 0;
        virtual unsigned max_tokens() const = 0;
        
        virtual bool is_composing() const = 0;
        virtual bool is_required() const = 0;
        
        virtual void parse(
            elib::any & dest
          , std::vector<std::string> const & new_tokens
        ) const = 0;
        
        virtual bool apply_default(elib::any &) const = 0;
        virtual bool apply_implicit(elib::any &) const = 0;
        
        virtual void notify(elib::any const &) const = 0;
        
        
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wexit-time-destructors"
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
        
        untyped_value(untyped_value const &) = default;
        untyped_value(untyped_value &&) = default;
        untyped_value & operator=(untyped_value const &) = default;
        untyped_value & operator=(untyped_value &&) = default;
        
        std::string const & name() const 
        {
            static const std::string m_name("untyped value");
            return m_name;
        }
        
        unsigned min_tokens() const { return !m_zero_tokens; }
        unsigned max_tokens() const { return !m_zero_tokens;}
        
        bool is_composing() const { return false; }
        bool is_required() const { return false; }
        
        void parse( 
            elib::any & dest
          , std::vector<std::string> const & new_tokens
        ) const;
        
        bool apply_default(elib::any &)  const { return false; }
        bool apply_implicit(elib::any &) const { return false; }
        
        void notify(elib::any const &) const {}

    private:
        bool m_zero_tokens;
    };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif
    
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
        typed_value()
          : m_dest(nullptr)
        {}
        
        typed_value(T & store_to)
          : m_dest(elib::addressof(store_to))
        {}
        
        typed_value(typed_value const &) = default;
        typed_value(typed_value &&) = default;
        typed_value & operator=(typed_value const &) = default;
        typed_value & operator=(typed_value &&) = default;
        
        typed_value & default_value(T const & v)
        {
            m_default_value = v;
            m_default_value_str = detail::opt_lexical_cast(v, "Default Value");
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
            m_implicit_value_str = detail::opt_lexical_cast(v, "Implicit Value");
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
        std::string const & name() const
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
            elib::any & dest
          , std::vector<std::string> const & new_tokens 
        ) const
        {
            Converter c;
            dest = c(new_tokens);
        }
        
        virtual bool apply_default(elib::any & dest)
        {
            if (!m_default_value) return false;
            dest = m_default_value;
            return true;
        }
        
        virtual bool apply_implicit(elib::any & dest) const
        {
            if (!m_implicit_value) return false;
            dest = m_implicit_value;
            return true;
        }
        
        void notify(elib::any const & val) const
        {
            if (m_notifier) m_notifier(any_cast<T const &>(val));
            if (m_dest) *m_dest = any_cast<T const &>(val);
        }
        
        std::type_info const & value_type() const noexcept
        {
            return typeid(T);
        }
        
        bool validate() const;
        
    private:
        bool m_multitoken{false}, m_zero_tokens{false}, m_composing{false};
        bool m_implicit{false}, m_required{false};
        
        T* m_dest{nullptr};
        
        std::string m_value_name{"Typed Value"};
        
        elib::any m_default_value;
        std::string m_default_value_str;
        
        elib::any m_implicit_value;
        std::string m_implicit_value_str;
        
        std::function<void(T const &)> m_notifier;
    };
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T>
    typed_value<T> value();
    
    template <class T>
    typed_value<T> value(T & v);
    
    typed_value<bool>  bool_switch();
    typed_value<bool>  bool_switch(bool & v);
}}                                                          // namespace elib
#endif /* ELIB_OPTIONS_VALUE_HPP */
