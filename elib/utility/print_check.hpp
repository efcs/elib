#ifndef ELIB_PRINT_CHECK_HPP
#define ELIB_PRINT_CHECK_HPP

# include <iostream>

# ifndef ELIB_PCHECK_OFF

#   define ELIB_PCHECK(lhs, op, rhs) \
      _ELIB_PCHECK(lhs, op,  rhs, __LINE__, __FILE__,  __func__)

#   define _ELIB_PCHECK(lhs, op, rhs, line, file, func) \
      ::elib::elib_pcheck(lhs op rhs                    \
        , "" # lhs,  "" # op, "" # rhs                  \
        , lhs, rhs, line, file, func)
  
namespace elib
{
  
  template <typename T, typename U>
  bool elib_pcheck(bool pred, const char* lhs, const char* op, const char* rhs,
                   T&& lhs_val, U&& rhs_val, 
                   int line, const char* file,  const char* func)
  {
    if (pred) return true;
    
    std::cout <<  file << "::" << line  
              << ": In function " << func 
              << ": PCHECK FAILED" <<  std::endl;
              
    std::cout << "\t" 
              << lhs << " " << op << " " << rhs 
              << std::endl;
    
    std::cout <<  "\t" 
              <<  "With " << lhs << " = " << "\"" << lhs_val << "\""
              << std::endl;
              
    std::cout <<  "\t" 
              << "With " <<  rhs << " = " << "\"" << rhs_val << "\""
              << std::endl;
              
    return pred;
  }
}                                                           // namespace elib
      
#   else                                                // ifdef ELIB_NO_PCHECK

#   define ELIB_PCHECK(...) ((void)0)
   
#   endif                                              // ifndef ELIB_NO_PCHECK 
# endif                                                // ELIB_PRINT_CHECK_HPP