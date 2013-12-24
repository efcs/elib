#!/usr/bin/python

from generator_config import *

file_name = 'overload.hpp'

raw_file = """
#ifndef ELIB_PP_OVERLOAD_HPP
#define ELIB_PP_OVERLOAD_HPP
#
# include <elib/pp/arity.hpp>
# include <elib/pp/cat.hpp>
#
#
# define ELIB_PP_OVERLOAD(name, ...) \\
    ELIB_PP_CAT(name, ELIB_PP_ARITY(__VA_ARGS__))
#
#
#endif /* ELIB_PP_OVERLOAD_HPP */
"""


def main():
    write_header(file_name, raw_file)


if __name__ == '__main__':
  main()
