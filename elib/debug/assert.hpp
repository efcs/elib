#ifndef ELIB_DEBUG_ASSERT_HPP
#define ELIB_DEBUG_ASSERT_HPP


////////////////////////////////////////////////////////////////////////////////
//                          ELIB_ASSERT and ELIB_ASSERT_MSG                                                
////////////////////////////////////////////////////////////////////////////////

# ifdef ELIB_DEBUG_ASSERT

#   include <cstdlib> /* for std::abort */
#   include <iostream>

  namespace elib 
  {
    namespace debug
    {
    
      // [noreturn] if !pred
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
        std::abort();
      }
    
    
    }                                                         // namespace debug
  }                                                           // namespace elib

#   define ELIB_ASSERT(pred) \
    ::elib::debug::elib_assert(pred, "" #pred, __FILE__, __func__,  __LINE__)

    
#   define ELIB_ASSERT_MSG(pred, msg) \
    ::elib::debug::elib_assert(pred,  "" #pred, \
            __FILE__,  __func__, __LINE__, msg)

            
# else                                                      // ELIB_DEBUG_ASSERT


#   define ELIB_ASSERT(pred) ((void)0)

#   define ELIB_ASSERT_MSG(pred, msg) ((void)0)


# endif                                                     // ELIB_DEBUG_ASSERT


////////////////////////////////////////////////////////////////////////////////
//                ELIB_WARN and ELIB_WARN_MSG                                                          
////////////////////////////////////////////////////////////////////////////////


# if ELIB_DEBUG_ASSERT || ELIB_DEBUG_WARN


#   include <iostream> 

  namespace elib
  {
    namespace debug
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
                     
    }                                                       // namespace debug
  }                                                         // namespace elib

  
#   define ELIB_WARN(pred) \
    ::elib::debug::elib_warn(pred, "" #pred, __FILE__, __func__, __LINE__)
    
#   define ELIB_WARN_MSG(pred, msg) \
    ::elib::debug::elib_warn(pred, "" #pred, __FILE__,  __func__,  __LINE__, msg)
    
    
# else                                  // ELIB_DEBUG_ASSERT || ELIB_DEBUG_WARN


#   define ELIB_WARN(pred) ((void)0)
#   define ELIB_WARN_MSG(pred,  msg) ((void)0)


# endif                                 // ELIB_DEBUG_ASSERT || ELIB_DEBUG_WARN


#endif /* ELIB_DEBUG_ASSERT_HPP */