#!/usr/bin/python

from generator_config import *

file_name = 'if.hpp'

raw_file = """
#ifndef ELIB_PP_IF_HPP
#define ELIB_PP_IF_HPP
#
# include <elib/pp/bool.hpp>
#
# define ELIB_PP_IF(v, then, else) \\
    ELIB_PP_IF_C(ELIB_PP_BOOL(v), then, else)
#
#
# define ELIB_PP_IF_C(b, then, else) ELIB_PP_IF_C_##b(then, else)
#
# define ELIB_PP_IF_C_1(then, else) then
# define ELIB_PP_IF_C_0(then, else) else
#
#endif ELIB_PP_IF_HPP
"""

def main():
  write_header(file_name, raw_file)
  

if __name__ == '__main__':
  main()