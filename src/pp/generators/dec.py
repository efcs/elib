#!/usr/bin/python

from generator_config import *

file_name = 'dec.hpp'

raw_file = """
#ifndef ELIB_PP_DEC_HPP
#define ELIB_PP_DEC_HPP
#
#
# define ELIB_PP_DEC(x) ELIB_PP_DEC_##x
#
# ELIB_PP_DEC_0 0
{enum}
#
#
#endif /* ELIB_PP_DEC_HPP */
"""

def get_enum(n):
  return [ ('# define ELIB_PP_DEC_' + str(x) + ' ' + str(x-1) + ' \n')
            for x in range(1, n + 1)]

def enum_1():
  return (''.join(get_enum(pp_arithmetic_limit)))[:-1]

def main():
  write_header(file_name, raw_file.format(enum=enum_1()))

if __name__ == '__main__':
  main()
  