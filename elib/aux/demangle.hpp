#ifndef ELIB_AUX_DEMANGLE_HPP
#define ELIB_AUX_DEMANGLE_HPP

/// A function to demangle type-names using implementation defined-libraries.
/// Adapted (Read: almost stolen) from:
/// boost/units/detail/utility.hpp
# include <elib/config.hpp>
# include <string>
# include <typeinfo>
# include <cstdlib>

# if defined(ELIB_CONFIG_LIBSTDCXX) 
#   define ELIB_AUX_HAS_DEMANGLE
# elif defined(ELIB_CONFIG_LIBCXX) && defined(__has_include)
#   if __has_include(<cxxabi.h>)
#       define ELIB_AUX_HAS_DEMANGLE
#   endif
# endif

# if defined(ELIB_AUX_HAS_DEMANGLE)
#   include <cxxabi.h>
# endif

namespace elib { namespace aux
{
    ////////////////////////////////////////////////////////////////////////////
# if defined(ELIB_AUX_HAS_DEMANGLE)
    inline std::string demangle(const char *name)
    {
        std::size_t len; 
        int stat;
        char* realname = abi::__cxa_demangle(name, nullptr, &len, &stat);
        if (realname != nullptr) {
            std::string out(realname);
            std::free(realname);
            return out;
        } else {
            return name;
        }
    }
    
    inline std::string demangle(std::type_info const & info)
    {
        return aux::demangle(info.name());
    }
    
    ////////////////////////////////////////////////////////////////////////////
    inline std::string demangle(std::string const & name)
    {
        return aux::demangle(name.c_str());
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class T>
    inline std::string demangle()
    {
        return aux::demangle(typeid(T).name());
    }
# else /* ELIB_AUX_HAS_DEMANGLE */
    inline std::string demangle(const char *name)
    {
        return name;
    }
    
    inline std::string demangle(std::type_info const & info)
    {
        return info.name();
    }
    
    inline std::string demangle(std::string str)
    {
        return str;
    }
    
    template <class T>
    inline std::string demangle()
    {
        return typeid(T).name();
    }
# endif
}}                                                          // namespace elib
#endif /* ELIB_AUX_DEMANGLE_HPP */