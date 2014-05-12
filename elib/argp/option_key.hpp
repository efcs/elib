#ifndef ELIB_ARGP_OPTION_KEY_HPP
# define ELIB_ARGP_OPTION_KEY_HPP

# include <elib/argp/fwd.hpp>
# include <string>
# includi <

namespace elib { namespace argp
{
    enum class key_type
    {
        none, 
        positional, 
        string, 
    };
    
    namespace detail
    {
        ////////////////////////////////////////////////////////////////////////
        union key_store
        {
            using positional_key = unsigned;
            using string_key = std::pair<std::string const*, std::string const*>;
            
            positional_key pos_key;
            string_key str_key;
            
            constexpr key_store() noexcept
              : pos_key(0)
            {}
            
            constexpr explicit key_store(position_key pk) noexcept
              : pos_key(pk)
            {}
            
            constexpr explicit key_store(string_key sk) noexcept
              : str_key(sk)
            {}
            
            // defaulted dtor in union will guarentee all dtors are trivially
            ~key_store() = default;
        };
    }                                                       // namespace detail
    
    ////////////////////////////////////////////////////////////////////////////
    class option_key
    {
    public:
        using position_key = key_store::positional_key;
        using string_key = key_store::string_key;
        
        constexpr explicit option_key(position_key pk) noexcept
          : m_type(key_type::positional)
          , m_store(pk)
        {}
        
        constexpr explicit option_key(string_key sk) noexcept
          : m_type(key_type::string)
          , m_store(sk)
        {}
        
        option_key(option_key const & other) noexcept
          : m_type(other.m_type)
        {
            if (other.m_type == key_type::positional) {
                m_store.pos_key = other.m_store.pos_key;
            } else {
                m_store.str_key = other.m_store.str_key;
            }
        }
        
        option_key & operator=(option_key const & other) noexcept
        {
            m_type = other.m_type;
            if (m_type == key_type::positional) {
                m_store.pos_key = other.m_store.pos_key;
            } else {
                m_store.str_key = other.m_store.str_key;
            }
        }
        
        constexpr key_type type() const noexcept
        { 
            return m_type; 
        }
        
        void swap(option_key const & other) noexcept
        {
            const option_key tmp(other);
            other = *this;
            *this = tmp;
        }
        
    private:
        key_type m_type;
        detail::key_store m_store;
    };
    
}}                                                          // namespace elib
#endif /* ELIB_ARGP_OPTION_KEY_HPP */