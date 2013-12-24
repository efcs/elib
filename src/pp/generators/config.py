#!/usr/bin/python

from generator_config import *

file_name = 'config.hpp'

raw_file ="""
#ifndef ELIB_PP_CONFIG_HPP
#define ELIB_PP_CONFIG_HPP
# 
# include <elib/config.hpp>
# 
#
# define ELIB_PP_ARITHMETIC_LIMIT {arith_lim}
# define ELIB_PP_ARITY_LIMIT {arity_lim}
# 
#
#endif /* ELIB_PP_CONFIG_HPP */
"""

def main():
  write_header(file_name, raw_file.
    format(arith_lim=pp_arithmetic_limit, arity_lim=pp_arity_limit)
  )
  
if __name__ == '__main__':
  main()
    