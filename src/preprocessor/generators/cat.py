#!/usr/bin/python

from generator_config import *

file_name = 'cat.hpp'

raw_file = """
#ifndef ELIB_PREPROCESSOR_CAT_HPP
#define ELIB_PREPROCESSOR_CAT_HPP
#
# define ELIB_PP_CAT(x, y) ELIB_PP_CAT_(x, y)
#
# define ELIB_PP_CAT_(x, y) x##y
#
#endif /* ELIB_PREPROCESSOR_CAT_HPP */
"""

def main():
  write_header(file_name, raw_file)

if __name__ == '__main__':
  main()