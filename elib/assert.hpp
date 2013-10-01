#ifndef ELIB_ASSERT_HPP
#define ELIB_ASSERT_HPP

# include <elib/config.hpp>

# define __ELIB_WARN_ON   defined(ELIB_WARN_ON) || defined(ELIB_DEBUG_ON)
# define __ELIB_ASSERT_ON defined(ELIB_ASSERT_ON) || defined(__ELIB_WARN_ON)



////////////////////////////////////////////////////////////////////////////////
//                          ELIB_ASSERT                                             
////////////////////////////////////////////////////////////////////////////////


# if __ELIB_ASSERT_ON

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

  
#   define ELIB_ASSERT(pred) \
    ::elib::elib_assert(pred, "" #pred, __FILE__, __func__,  __LINE__)

    
#   define ELIB_ASSERT_MSG(pred, msg) \
    ::elib::elib_assert(pred,  "" #pred, \
            __FILE__,  __func__, __LINE__, msg)

            
# else                                                      // __ELIB_ASSERT_ON


#   define ELIB_ASSERT(pred)          ((void)0)
#   define ELIB_ASSERT_MSG(pred, msg) ((void)0)


# endif                                                     // __ELIB_ASSERT_ON


////////////////////////////////////////////////////////////////////////////////
//                              ELIB_WARN                                       
////////////////////////////////////////////////////////////////////////////////


# if __ELIB_WARN_ON


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

  
#   define ELIB_WARN(pred) \
    ::elib::elib_warn(pred, "" #pred, __FILE__, __func__, __LINE__)
    
#   define ELIB_WARN_MSG(pred, msg) \
    ::elib::elib_warn(pred, "" #pred, __FILE__,  __func__,  __LINE__, msg)
    
    
# else                                                      // __ELIB_WARN_ON


#   define ELIB_WARN(pred)            ((void)0)
#   define ELIB_WARN_MSG(pred,  msg)  ((void)0)


# endif                                                     // __ELIB_WARN_ON



////////////////////////////////////////////////////////////////////////////////
//                            ELIB DEBUG                                                       
////////////////////////////////////////////////////////////////////////////////

# ifdef ELIB_DEBUG_ON

#   include <iostream>

#   define ELIB_DEBUG(pred)                             \
    ::elib::elib_debug(pred, "" #pred, __FILE__, __func__, __LINE__)
    
#   define ELIB_DEBUG_MSG(pred, msg) \
    ::elib::elib_debug(pred, "" #pred, __FILE__, __func__, __LINE__, msg)
    
  namespace elib
  {
      
    inline void elib_debug(bool pred, const char* pred_str, 
                           const char* filename, const char* func_name, 
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

# else                                                      // ELIB_DEBUG_ON


#   define ELIB_DEBUG(pred)          ((void)0)
#   define ELIB_DEBUG_MSG(pred, msg) ((void)0)


#  endif                                                    // ELIB_DEBUG_ON



# undef __ELIB_ASSERT_ON
# undef __ELIB_WARN_ON


#endif /* ELIB_ASSERT_HPP */