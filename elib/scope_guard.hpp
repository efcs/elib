#ifndef ELIB_SCOPE_GUARD_HPP
#define ELIB_SCOPE_GUARD_HPP

# include <elib/aux.hpp>
# include <cstddef>

# define ELIB_SCOPE_GUARD(...)          \
    auto _elib_scope_guard_##__LINE__ = \
      ::elib::make_scope_guard(__VA_ARGS__)
      
# define ELIB_SCOPE_GUARD_LAMBDA(...)   \
    auto _elib_scope_guard_##__LINE__ = \
      ::elib::make_scope_guard([&]() { __VA_ARGS__ } )

namespace elib 
{
    ////////////////////////////////////////////////////////////////////////
    // scope_guard
    template <class Fn>
    class scope_guard
    {
    public:
        explicit scope_guard(Fn const & f) 
          : m_dismissed{false}, m_fn(f) 
        {}
        
        explicit scope_guard(Fn && f) 
          : m_dismissed{false}, m_fn(elib::move(f)) 
        {}
        
        scope_guard(scope_guard && other)
          : m_dismissed(other.m_dismissed)
          , m_fn(elib::move(other.m_fn))
        {
            other.m_dismissed = true;
        }
        
        void dismiss() 
        { 
            m_dismissed = true; 
        }
        
        ~scope_guard()
        {
            if (!m_dismissed) m_fn();
        }
        
    private:
        void* operator new(std::size_t) = delete;
        bool m_dismissed;
        Fn m_fn;
    };
    
    template <class Fn>
    scope_guard<aux::decay_t<Fn>>
    make_scope_guard( Fn && fn )
    {
        return scope_guard<aux::decay_t<Fn>>(
            elib::forward<Fn>(fn)
        );
    }
}                                                           // namespace elib
#endif /* ELIB_SCOPED_GUARD_HPP */