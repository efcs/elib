#!/usr/bin/python

from generator_config import *

file_name = 'bool.hpp'

raw_file = """
#ifndef ELIB_PREPROCESSOR_BOOL_HPP
#define ELIB_PREPROCESSOR_BOOL_HPP
#
# define ELIB_PP_BOOL(v) ELIB_PP_BOOL_##v
#
# define ELIB_PP_BOOL_0 0
# {enum}
#
#
#endif /* ELIB_PREPROCESSOR_BOOL_HPP */
"""

def main():
  write_header(file_name, raw_file.format(enum=enum_1()))

def get_enum(n):
  return [ ('# define ELIB_PP_BOOL_' + str(x) + ' 1 \n') for x in range(1, n+1) ]

def enum_1():
  s = ''.join( get_enum(pp_arithmetic_limit) )
  return s[:-1]

if __name__ == '__main__':
  main()