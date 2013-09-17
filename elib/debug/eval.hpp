#ifndef ELIB_DEBUG_EVAL_HPP
#define ELIB_DEBUG_EVAL_HPP


#   define ELIB_EVAL_BEGIN() \
        { \
            bool __ret = true;
    
        
#   define ELIB_EVAL_END() \
            return __ret; \
        }


#ifdef ELIB_DEBUG_EVAL_PRINT
    

#include <iostream>

#   define ELIB_EVAL(op, arg1, arg2)                                      \
do {                                                                      \
  if (! (arg1 op arg2)) {                                                 \
    __ret = false;                                                        \
    std::cout <<  "FAILED: ";                                             \
  } else std::cout << "success: ";                                        \
  std::cout << "" #arg1 " " #op " " #arg2;                        \
  std::cout << " : \"" << arg1 << "\" , \"" << arg2 << "\"" << std::endl; \
} while (false)
    
    
#elif defined ELIB_DEBUG_EVAL_FAILED


#   include <iostream>

#   define ELIB_EVAL(op, arg1, arg2)                                          \
do {                                                                          \
if (! (arg1 op arg2)) {                                                       \
      std::cout << "FAILED: " #arg1 " " #op " " #arg2;                        \
      std::cout << " : \"" << arg1 << "\" , \"" << arg2 << "\"" << std::endl; \
      __ret = false;                                                          \
    }                                                                         \
} while (false)


#else                                                   //ELIB_DEBUG_EVAL_PRINT


#   define ELIB_EVAL(op, arg1, arg2) \
    do { \
      if (! (arg1 op arg2)) { \
        __ret = false; \
      } \
    } while(false)
    
    
#endif                                                  //ELIB_DEBUG_EVAL_PRINT


#endif /* ELIB_DEBUG_EVAL_HPP */