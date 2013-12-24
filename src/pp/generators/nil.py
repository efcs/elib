#!/usr/bin/python

from generator_config import *

file_name = 'nil.hpp'


raw_file = """
#ifndef ELIB_PP_NIL_HPP
#define ELIB_PP_NIL_HPP
#
#
# define ELIB_PP_NIL
#
#endif /* ELIB_PP_NIL_HPP */
"""

def main():
  write_header(file_name, raw_file)


if __name__ == '__main__':
  main()