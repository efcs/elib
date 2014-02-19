# Elib

elib is a personal C\+\+ library and an excuse to learn/practice more parts of C\+\+.

WARNING: This file is update very infrequently
LAST UPDATE: 9/12/2014

## Platform Support
Elib currently only supports Linux and OS X. Although most libraries would
build on Windows (See Library Summary for specifics), the build system has
no support for MSVC. With enough trouble it should build in Cygwin and MinGW.

## Library Summary

Enumeration:
: A header-only library for dealing with C++11 scoped enumerations.
  It is a way to provide checked casting, string casting, iteration
  and non-default operators
  (Header Only)

Log
: Exactly what it sounds like. A basic message logging library.

MP
: A meta-programming library inspired by boosts mpl. It generally
  has the same structure, files and iterface as boost::mpl
  (Header Only)

Filesystem
: A posix only implementation of the C++14 filesystem library.
  This library will not compile on windows. (No Windows Support)

Web
: C++ Socket, HTTP parsing and other Web/Network utilities.
  stripped from a class project (No Windows Support)

Aux
: misc functionality that is frequently needed.
  it includes:

  * fmt: used to format varargs strings 
  * lexical_cast: For casting between strings and integral types
  * scoped_exit: uses lambdas to provide scoped exit functionality
  * size_type: A helper for using a "size_type" and its npos value
  (Header Only)


## Building

Note: Requirements marked with (Unit Test Only) are obviously only required
  to build the unit tests. 

Requirements (General):
  * C++11 compiler (GCC >= 4.7 is usualy suffient)
  * Boost Unit Test Framework (Unit Test Only)

Requirements (Library specific):
  Log:
    Native library used by <mutex> (pthread on linux)

  Filesystem:
    Posix filesystem headers
    Boost System (Unit Test Only)
    Boost Filesystem (Unit Test Only)

  Web:
    Posix thread headers
    Support for <regex> (I'm looking at you GCC)


## Build Options (CMake)
  These options are found in CMakeLists.txt. 
  Not all options are documented here. 

  * CONFIG_USE_CLANG 
: use /bin/clang and /bin/clang++ to compile
  Default: OFF

  * CONFIG_ALL_WARNINGS 
: Turn on all warnings for the compiler
  Default: ON

  * CONFIG_UNIT_TESTS
: Build the unit tests
  Default: ON
  
### Select what parts to build
  
  * CONFIG_LIB_ENUMERATION
: build enumeration library
  Default: ON

  * CONFIG_LIB_LOG
: build logging library
  Default: ON

  * CONFIG_LIB_MP
: build the MPL (header-only, only builds unit_tests and dummy file)
  Default: ON

  * CONFIG_LIB_FILESYSTEM
: build the filesystem library
  Default: ON (Except on windows)

  * CONFIG_LIB_AUX
: build the utility library
  Default: ON

  * CONFIG_LIB_WEB
: build web library
  Default: OFF (until more support for <regex>)
    
## Makefile Commands

  * all 
: build libraries and unit tests

  * clean
: Clean build files

  * distclean
: Clean all generated files.

  * redep
: execute Cmake

  * install
: install using the generated Cmake command

  * e
: A helper command. equivalent to
    make distclean
    make redep
    make 

  * ej
: A helper command. It is the same as 'e' except it runs
  make -j2 as the last command

  * check
: Run the unit tests

