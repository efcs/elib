#ifndef ELIB_EVAL_H
#define ELIB_EVAL_H

#include <iostream>


#define EVAL_BEGIN() \
    { \
        bool __ret = true;
    
        
#define EVAL_END() \
        return __ret; \
    }
    
    
#define EVALP(op, arg1, arg2) \
do { \
    if (! (arg1 op arg2)) { \
        std::cout << "FAILED: " #arg1 " " #op " " #arg2; \
        std::cout << " : \"" << arg1 << "\" , \"" << arg2 << "\"" << std::endl; \
        __ret = false; \
    } \
} while (false)


#define EVALS(op, arg1, arg2) \
do { \
    if (! (arg1 op arg2)) { \
        __ret = false; \
    } \
} while(false)


#define EVAL(op, arg1, arg2) EVALP(op, arg1, arg2)


#endif /* ELIB_EVAL_H */
