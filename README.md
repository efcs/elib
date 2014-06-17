# Elib

elib is a personal C\+\+ library and an excuse to learn/practice more parts of C\+\+.
It can be found at github.com/efcs/elib. The homepage for elib is http://elib.efcs.ca

WARNING: This file is update very infrequently
LAST UPDATE: 07/06/2014

NOTE: elib has git submodules! If this is a new repo please run `git submodule update --init`.

## Platform Support
Elib currently only supports Linux and OS X as well as Cygwin. 
Although most libraries would build on Windows (See Library Summary for specifics), 
the build system has no support for MSVC. 

## Compiler Support.
Elib supports the following compiler/library configurations:
 - GCC 4.8
 - GCC 4.9
 - Clang 3.4 (with/without libc++)
 - Clang 3.5 trunk (with/without libc++)
 - GCC 4.8.3/4.9.0 (Cygwin)

NOTE: Cygwin requires a workaround to get g


## Library Summary

### Core Library

Any
: a variant container. It implementations the std::any proposal

Aux
: misc functionality that is frequently needed.
  it includes:
  * forward, move, declval
  * integral_constant, true_, false_, int_, size_type
  * not_, and_, or_, if_, enable_if
  * a type_traits implementation (C++11 Or C++14)
  * invoke
  * ELIB_ASSERT
  (Header Only)

Config
: A compiler/library/platform configuration system

Compressed Pair
: A pair class that takes advantage of the empty base class optimization.
  It is very handy for storing allocators

Fmt
: A set of tools for formatting strings and printing

Lexical Cast
: a function to convert between lexical types

Optional
: An implementation of the std::optional proposal

Params
: A let of meta-functions for working with typelists

Scope Guard
: A utility to invoke a function on scope exit.



### Extended Librarys

Container
: a header only library that contains containers not found in the standard library.
  It currently includes:
  * flat_map
  * linear_flat_map

Enumeration:
: A header-only library for dealing with C++11 scoped enumerations.
  It is a way to provide checked casting, string casting, iteration
  and non-default operators
  (Header Only)

Except:
: A header only exception library similar to boost::exception. It allows
  exceptions to store arbitrary data

Filesystem
: A posix only implementation of the C++14 filesystem library.
  (No Windows Support)

Iter
: A library for manipulating and creating iterators and views.

Logging
: Exactly what it sounds like. A basic message logging library.

Memory
: Utility functions and classes for working with memory. It currently includes:
  * allocator_destructor: for destorying allocated memory that hasn't been initialized
  * make_unique: An implementation of the proposal for std::make_unique

MP
: A meta-programming library inspired by boosts mpl. It generally
  has the same structure, files and iterface as boost::mpl
  (Header Only)

PP
: A library that provides macros for working with the preprocessor


#### Experimental

Web
: C++ Socket, HTTP parsing and other Web/Network utilities.
  stripped from a class project
  (No Windows Support)

## Building

Note: Requirements marked with (Unit Test Only) are obviously only required
  to build the unit tests. 

Requirements (General):
  * C++11 compiler (GCC >= 4.8.1)
  * Native library used by <mutex> (pthread on linux)
  * Python (Unit Test Only)
  Note: elib will compile with GCC 4.8.0 but some features have been disabled.

Requirements (Library specific):
  Filesystem:
    POSIX support

  Web:
    POSIX support
    Support for <regex>


## Build Options (CMake)
  These options are found in CMakeLists.txt. If the enviroment variable
  ELIB_CMAKE_OPTIONS is set, those options are passed to cmake when configuring.
  Not all options are documented here. 

  * CONFIG_ALL_WARNINGS 
: Turn on all warnings for the compiler
  Default: ON

  * CONFIG_ELIB_ASSERT_CONFIG
: Make the config library fail to compile if it cannot deduce the
  compiler/library/platform information.
  Default: OFF

  * CONFIG_ENABLE_EXPERIMENTAL
: Make the experimental libraries
  Default: ON

  * CONFIG_UNIT_TESTS
: Build the unit tests
  Default: ON

  * CONFIG_HEADER_TESTS
: Build the header tests
  Default: OFF

  * CONFIG_CXX1Y
: Compile using -std=c++1y
  Default: OFF
  WARNING: c++1y support is experimental
  
### Select what parts to build
  

  * ELIB_AUX_SOURCE
: build the utility library
  Default: ON

  * ELIB_CONTAINER_SOURCE
: build containers
  Default: ON

  * ELIB_ENUMERATION_SOURCE
: build enumeration library
  Default: ON

  * ELIB_EXCEPT_SOURCE
: build exception library
  Default: ON

  * ELIB_FILESYSTEM_SOURCE
: build the filesystem library
  Default: ON 

  * ELIB_FUNCTIONAL_SOURCE
: build functional source
  Default: ON

  * ELIB_ITERATOR_SOURCE
: build iterator source
  Default: ON

  * ELIB_LOGGING_SOURCE
: build logging library
  Default: ON

  * ELIB_MEMORY_SOURCE
: build memory library
  Default: ON

  * ELIB_MP_SOURCE
: build the MPL
  Default: ON

  * ELIB_PP_SOURCE
: build preprocessor library
  Default: ON

  * ELIB_WEB_SOURCE
: build web library
  Default: ON when compiling with GCC >= 4.9.0 or clang and libc++. Off otherwise. 
    
## Makefile Commands

  * configure
: Run the cmake configuration.
  This only needs to be done once.

  * redep
: Rerun partial configuration. Detects new source files.

  * all 
: build libraries and unit tests

  * clean
: Clean build files

  * distclean
: Clean all generated files.

  * install
: install using the generated Cmake command

  * everything
: A helper command. equivalent to
    make distclean
    make configure
    make 

  * check
: Run the unit tests (using LIT)

  * test
: Run the unit tests (using CTest)

  * vagrind-check
: Run unit tests with valgrind

  * scan-build
: Run clangs scan-build over the build

  * coverage
: Generate code coverage data




