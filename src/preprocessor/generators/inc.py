#!/usr/bin/python

from generator_config import *

file_name = 'inc.hpp'

raw_file = """
#ifndef ELIB_PREPROCESSOR_INC_HPP
#define ELIB_PREPROCESSOR_INC_HPP
#
#
# define ELIB_PP_INC(x) ELIB_PP_INC_##x
#
{enum}
# define ELIB_PP_INC_256 256
#
#
#endif /* ELIB_PREPROCESSOR_INC_HPP */
"""

def get_enum(n):
  return [ ('# define ELIB_PP_INC_' + str(x) + ' ' + str(x+1) + ' \n')
            for x in range(n)]

def enum_1():
  return (''.join(get_enum(pp_arithmetic_limit)))[:-1]

def main():
  write_header(file_name, raw_file.format(enum=enum_1()))

if __name__ == '__main__':
  main()
  