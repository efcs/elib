#!/usr/bin/python

from generator_config import *

file_name = 'str.hpp'

raw_file = """
#ifndef ELIB_PP_STR_HPP
#define ELIB_PP_STR_HPP
#
# 
# define ELIB_PP_STR(s) ELIB_PP_STR_(s)
#
# define ELIB_PP_STR_(s) #s
#
#endif /* ELIB_PP_STR_HPP */
"""


def main():
  write_header(file_name, raw_file)



if __name__ == '__main__':
  main()
