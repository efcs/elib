#ifndef ELIB_DEBUG_EVAL_H
#define ELIB_DEBUG_EVAL_H


#   define EVAL_BEGIN() \
        { \
            bool __ret = true;
    
        
#   define EVAL_END() \
            return __ret; \
        }


#ifdef NDEBUG
    
    
#   define EVAL(op, arg1, arg2) \
    do { \
        if (! (arg1 op arg2)) { \
            __ret = false; \
        } \
    } while(false)


#else /* NDEBUG */


#include <iostream>

#   define EVAL(op, arg1, arg2) \
    do { \
        if (! (arg1 op arg2)) { \
            std::cout << "FAILED: " #arg1 " " #op " " #arg2; \
            std::cout << " : \"" << arg1 << "\" , \"" << arg2 << "\"" << std::endl; \
            __ret = false; \
        } \
    } while (false)

    
#endif /* NDEBUG */


#endif /* ELIB_DEBUG_EVAL_H */
