#ifndef ELIB_ASSERT_HPP
#define ELIB_ASSERT_HPP

# include <elib/config.hpp>

# if !defined(NDEBUG) || defined(ELIB_ASSERT_ON)

#   define _ELIB_ASSERT_ON 1

#   if defined(ELIB_DEBUG_ON)
#     define _ELIB_DEBUG_ON 1
#   endif

#   if defined(ELIB_WARN_ON) || defined(_ELIB_DEBUG_ON)
#     define _ELIB_WARN_ON 1
#   endif

# endif

////////////////////////////////////////////////////////////////////////////////
//                          ELIB_ASSERT                                             
////////////////////////////////////////////////////////////////////////////////


# ifdef _ELIB_ASSERT_ON

#   include <iostream>

#   ifndef ELIB_ASSERT_NO_EXIT
#     include <cstdlib> /* for std::abort */
#   endif /* ELIB_ASSERT_NO_EXIT */

  namespace elib 
  {
    
    
    // [noreturn] if !pred && ! defined(ELIB_ASSERT_NO_EXIT)
    inline void elib_assert(bool pred,  const char* pred_str,  
            const char* filename, const char* func, int line,  
            const char* opt_msg=nullptr)
    {
      if (pred) return;
      std::cerr <<  "ELIB_ASSERT::" <<  filename << line <<  std::endl
                << "  in  " << func << ":" 
                << "  (" << pred_str << ")  FAILED" << std::endl;
      if (opt_msg)
        std::cerr <<  "  " << opt_msg << std::endl;
#   ifndef ELIB_ASSERT_NO_EXIT
      std::abort();
#   endif /* ELIB_ASSERT_NO_EXIT */
    }
    
  }                                                           // namespace elib

  
#   define ELIB_ASSERT_1(pred) \
    ::elib::elib_assert(pred, "" #pred, __FILE__, __func__,  __LINE__)

    
#   define ELIB_ASSERT_2(pred, msg) \
    ::elib::elib_assert(pred,  "" #pred, \
            __FILE__,  __func__, __LINE__, msg)
            

#   define ELIB_ASSERT(...) ELIB_OVERLOAD(ELIB_ASSERT_,  __VA_ARGS__)(__VA_ARGS__)

            
# else                                                      // __ELIB_ASSERT_ON


#   define ELIB_ASSERT(...)          ((void)0)


# endif                                                     // __ELIB_ASSERT_ON


////////////////////////////////////////////////////////////////////////////////
//                              ELIB_WARN                                       
////////////////////////////////////////////////////////////////////////////////


# if _ELIB_WARN_ON


#   include <iostream> 

  namespace elib
  {
    
    inline void elib_warn(bool pred, const char* pred_str, const char* filename, 
                    const char* func,  int line, const char* opt_msg=nullptr)
    {
      if (pred) return;
      std::cout << "ELIB_WARNING::" <<  filename << "::" << line << std::endl
                << "  in  " << func <<  ":" 
                << "  (" <<  pred_str << ")  FAILED" << std::endl;
      if (opt_msg)
        std::cout << "  " << opt_msg << std::endl;
    }
                     
  }                                                         // namespace elib

  
#   define ELIB_WARN_1(pred) \
    ::elib::elib_warn(pred, "" #pred, __FILE__, __func__, __LINE__)
    
#   define ELIB_WARN_2(pred, msg) \
    ::elib::elib_warn(pred, "" #pred, __FILE__,  __func__,  __LINE__, msg)
    
    
#   define ELIB_WARN(...) ELIB_OVERLOAD(ELIB_WARN_, __VA_ARGS__)(__VA_ARGS__)
    
# else                                                      // __ELIB_WARN_ON


#   define ELIB_WARN(...)            ((void)0)


# endif                                                     // __ELIB_WARN_ON



////////////////////////////////////////////////////////////////////////////////
//                            ELIB DEBUG                                                       
////////////////////////////////////////////////////////////////////////////////

# ifdef _ELIB_DEBUG_ON

#   include <iostream>
    
  namespace elib
  {
      
    inline void elib_debug(bool pred, const char* pred_str, 
                           const char* filename, const char* func, 
                           int line, const char* opt_msg=nullptr) 
    {
      if (pred) return;
      std::cout << "ELIB_DEBUG::" <<  filename << "::" << line << std::endl
                << "  in  " << func <<  ":" 
                << "  (" <<  pred_str << ")  FAILED" << std::endl;
      if (opt_msg)
        std::cout << "  " << opt_msg << std::endl;
        
    }
    
      
  }                                                         // namespace elib

  
#   define ELIB_DEBUG(...) ELIB_OVERLOAD(ELIB_DEBUG_, __VA_ARGS__)(__VA_ARGS__)

#   define ELIB_DEBUG_1(pred) ELIB_DEBUG_2(pred, nullptr)
  
#   define ELIB_DEBUG_2(pred, msg) \
  ::elib::elib_debug(pred, "" # pred, __FILE__, __func__, __LINE__, msg)
  
  
# else                                                      // ELIB_DEBUG_ON


#   define ELIB_DEBUG(...)          ((void)0)



#  endif                                                    // ELIB_DEBUG_ON



# undef _ELIB_ASSERT_ON
# undef _ELIB_WARN_ON
# undef _ELIB_DEBUG_ON

#endif /* ELIB_ASSERT_HPP */