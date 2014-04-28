#ifndef ELIB_AUX_DEMANGLE_HPP
#define ELIB_AUX_DEMANGLE_HPP

# include <elib/config.hpp>
/** 
 * Adapted (Read: almost stolen) from:
 * boost/units/detail/utility.hpp
 */
# include <string>
# include <cstdlib>

# if defined(ELIB_CONFIG_LIBSTDCXX) && defined(__GNUC__)
#   if __GNUC__ >= 3
#       define ELIB_AUX_HAS_DEMANGLE
#   endif
# endif

# if defined(ELIB_AUX_HAS_DEMANGLE)
#   include <cxxabi.h>
# endif

namespace elib { namespace aux
{
    inline std::string demangle(const char *name)
    {
# if defined(ELIB_AUX_HAS_DEMANGLE)
        // need to demangle C++ symbols
        char*       realname;
        std::size_t len; 
        int         stat;
        
        realname = abi::__cxa_demangle(name, nullptr, &len, &stat);
        
        if (realname != nullptr)
        {
            std::string out(realname);
            std::free(realname);
            return out;
        }
        else
        {
            return std::string(name);
        }
# else  /* no demangle */
        return std::string(name);
# endif
    }
}}                                                          // namespace elib
#endif /* ELIB_AUX_DEMANGLE_HPP */