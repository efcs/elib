#!/usr/bin/python

from generator_config import *

file_name = 'not_equal.hpp'

raw_file ="""
#ifndef ELIB_PP_NOT_EQUAL_HPP
#define ELIB_PP_NOT_EQUAL_HPP
#
# include <elib/pp/cat.hpp>
# include <elib/pp/if.hpp>
# include <elib/pp/nil.hpp>
#
#
# define ELIB_PP_NOT_EQUAL(x, y) \\
    ELIB_PP_CAT(ELIB_PP_NOT_EQUAL_TEST_, \\
      ELIB_PP_NOT_EQUAL_##x(0, ELIB_PP_NOT_EQUAL_##y))
#
# 
# define ELIB_PP_NOT_EQUAL_TEST_ELIB_PP_NIL 1
#
#
{enum}
#
#
{sec_enum}
#
#
#endif /* ELIB_PP_NOT_EQUAL_HPP */
"""

def get_enum(n):
  l = '# ELIB_PP_NOT_EQUAL_TEST_ELIB_PP_NOT_EQUAL_%i(c, y) 0 \n'
  ll = [ l % (x,) for x in range(0, n+1) ]
  return ''.join(ll)[:-1]

def get_sec_enum(n):
  l = '# define ELIB_PP_NOT_EQUAL_{i}(c, y) ELIB_PP_IF_C(c, ELIB_PP_NIL, y(1, ELIB_PP_NIL)) \n'
  ll = [ l.format(i=x) for x in range(0, n+1) ]
  ll = ''.join(ll)[:-1]
  return ll


def main():
  write_header(file_name, raw_file.format(
    enum=get_enum(pp_arithmetic_limit),
    sec_enum=get_sec_enum(pp_arithmetic_limit)
  ))


if __name__ == '__main__':
  main()

  