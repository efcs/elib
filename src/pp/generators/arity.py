#!/usr/bin/python

from generator_config import *

file_name = "arity.hpp"

raw_file ="""
#ifndef ELIB_PP_ARITY_HPP
#define ELIB_PP_ARITY_HPP
#
#
# define ELIB_PP_ARITY(...) \\
    ELIB_PP_ARITY_(__VA_ARGS__, {enum})
#
#
# define ELIB_PP_ARITY_({enum_2}, ...) _0
#
#
#endif /* ELIB_PP_ARITY_HPP */
"""

def main():
  write_header(file_name, raw_file.format(enum=first_enum(pp_arity_limit),
                                          enum_2=second_enum(pp_arity_limit)))
  

def get_enum(n):
  return [ str(x) for x in reversed(range(0, n+1)) ]
  
  
def first_enum(n):
  return ', '.join( get_enum(n) )
  
  
def second_enum(n):
  return  '_' + ', _'.join(get_enum(n)) 


if __name__ == '__main__':
  main()