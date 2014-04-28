#ifndef ELIB_AUX_DEMANGLE_HPP
#define ELIB_AUX_DEMANGLE_HPP

/// A function to demangle type-names using implementation defined-libraries.
/// Currently the only supported compiler is GCC.
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

        // need to demangle C++ symbols
        char*       realname;
        std::size_t len; 
        int         stat;
        
        realname = abi::__cxa_demangle(name, nullptr, &len, &stat);
        
        if (realname != nullptr) {
            std::string out(realname);
            std::free(realname);
            return out;
        }
        else {
            return std::string(name);
        }
    }
# else /* ELIB_AUX_HAS_DEMANGLE */
    inline std::string demangle(const char *name)
    {
        return name;
    }
# endif


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
    
}}                                                          // namespace elib
#endif /* ELIB_AUX_DEMANGLE_HPP */