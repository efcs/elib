# Elib
elib is a personal C\+\+ library and an excuse to learn/practice more parts of
C\+\+.  It can be found at <http://github.com/efcs/elib>. The homepage for elib
is <http://elib.efcs.ca/>.

**Warning**: This file is updated very infrequently. Last updated on 2014-06-17.

**Note**: elib uses git submodules! If this is a new working directory, please
run `git submodule update --init`.

## Getting Started
The get and build Elib run the following commands:

    git clone https://github.com/efcs/elib.git
    cd elib
    git submodule update --init
    make configure
    make elib

After building Elib it is recommended that you run the testsuite. You can
do so using:

    make check

If do not have python or would rather use the CTest testsuite you can use:

    make check-ctest

## Platform Support
Elib currently only supports Linux, OS X, and Cygwin.

Most libraries will build on Windows (See Library Summary for specifics);
however, the build system has no support for MSVC. 

## Compiler Support.
Elib supports the following compiler/library configurations:
 - GCC 4.8
 - GCC 4.9
 - Clang 3.4 (with/without libc++)
 - Clang 3.5 trunk (with/without libc++)
 - GCC 4.8.3 (Cygwin)

Note: A non-trivial but easy to make workaround is required to compile elib
in Cygwin. It requires editing `<cstdio>` so that it provides `std::vsnprintf` 
in C++11 mode.

## Library Summary
### Core Library
* *Any*: A variant container. It provides an implementation of the `std::any`
    proposal.

* *Aux*: (Header only) Miscellaneous functionality that is frequently needed.
    It includes:
    * `forward`, `move`, `declval`
    * `integral_constant`, `true_`, `false_`, `int_`, `size_type`
    * `not_`, `and_`, `or_`, `if_`, `enable_if`
    * a `type_traits` implementation (C++11 or C++14)
    * `invoke`
    * `ELIB_ASSERT`

* *Config*: A compiler/library/platform configuration system.

* *Compressed Pair*: A pair class that utilizes the empty base class
    optimization. It is very handy for storing allocators.

* *Fmt*: A set of tools for formatting strings and printing.

* *Lexical Cast*: Provides a lexical type-conversion function.

* *Optional*: An implementation of the `std::optional` proposal.

* *Params*: A set of meta-functions for working with C\+\+ typelists.

* *Scope Guard*: A utility library that provides the ability to invoke a
    function on scope exit.

### Extended Libraries

* *Container*: (Header only) Provides containers not found in the standard
    library. It currently includes:
    * `flat_map`
    * `linear_flat_map`

* *Enumeration*: (Header only) Provides tools to deal with C++11 scoped
    enumerations, including checked casting, string casting, iteration, and
    non-default operators.

* *Except*: (Header only) Similar to `boost::exception`; allows exceptions to
    store arbitrary data.

* *Filesystem*: (No Windows support) An implementation of the C++14 filesystem
    library.

* *Iter*: Utility library that provides creation and manipulation of iterators
    and views.

* *Logging*: A basic message logging and formatting library, intended for use
    with log files.

* *Memory*: Utility functions and classes for working with memory and allocators.
    It currently includes:
    * `allocator_destructor`: for destroying allocated memory that hasn't been
        initialized
    * `make_unique`: An implementation of the proposal for `std::make_unique`

* *MP*: (Header only) A meta-programming library, generally using the same
    structure, file names, and interface as `boost::mpl`, which it draws
    inspiration from.

*PP*: Library of macros for working with the C\+\+ preprocessor.

#### Experimental
*Web*: (No windows support) Various network utilities, including a C++ socket
    class and HTTP parsing.

## Building
**Note**: Requirements marked with (Unit Testing Only) are only required to
build the unit tests. 

General requirements:
* C++11 compiler (GCC >= 4.8.1)
* Native library used by `<mutex>` header (pthread on Linux)
* Python 3.x (Unit Testing Only)
* CMake >= 2.8.8

**Note**: elib will compile with GCC 4.8.0 but some features have been
disabled.

Requirements (library specific):
* Filesystem:
    * POSIX-compatible compiler and execution environment

* Web:
    * POSIX-compatible compiler and execution environment
    * Support for the `<regex>` header

## Makefile Targets
* configure: Run the CMake configuration. This only needs to be done once.

* redep: Re-run partial configuration. Detects new source files.

* all: Build libraries and unit tests.

* clean: Clean build files.

* distclean: Clean all generated files.

* install: Install using the generated CMake buildsystem's target directory.

* everything: A helper command. Equivalent to

    make distclean
    make configure
    make 

* check: Run the unit tests (using LIT).

* test: Run the unit tests (using CTest).

* valgrind-check: Run unit tests with valgrind.

* scan-build: Run clang's scan-build over the build.

* coverage: Generate code coverage data.

## Makefile Options
These are the options currently supported by `make configure`. For example
`make BUILD=RELEASE configure`.

* `ELIB_CMAKE_OPTIONS`: This is a list of CMake build options. It is passed
    directly to CMake. This is useful when selecting what libraries to build.

* `BUILD`: Configure the build type.
    * Values: `DEBUG`, `RELEASE`
    * Default: `DEBUG`

* `CXX1Y`: Compile using the `-std=c++1y` flag.
    * Default: `OFF`
    * **Note**: c++1y support is experimental

* `PYTHON3`: Use Python3 as the python interpreter.
    * Default: `OFF`

* `ALL_WARNINGS`: Turn on all warnings for the compiler.
    * Default: `ON`

* `ASSERT_CONFIG`: Make the config library fail to compile if it
    cannot deduce the compiler/library/platform information.
    * Default: `OFF`

* `ENABLE_EXPERIMENTAL`: Build the experimental libraries.
    * Default: `ON`

* `UNIT_TESTS`: Build the unit tests.
    * Default: `ON`

  
### Select what parts to build (CMake Options)
  
* `ELIB_AUX`: Build the utility library.
    * Default: ON

* `ELIB_CONFIG`: Build configuration library.
    * Default: ON

* `ELIB_CONTAINER`: Build containers library.
    * Default: ON

* `ELIB_ENUMERATION`: Build enumeration library.
    * Default: ON

* `ELIB_EXCEPT`: Build exception library.
    * Default: ON

* `ELIB_FILESYSTEM`: Build the filesystem library.
    * Default: ON 

* `ELIB_FUNCTIONAL`: Build functional source.
    * Default: ON

* `ELIB_ITERATOR`: Build iterator source.
    * Default: ON

* `ELIB_LOGGING`: Build logging library.
    * Default: ON

* `ELIB_MEMORY`: Build memory library.
    * Default: ON

* `ELIB_MP`: Build the MPL.
    * Default: ON

* `ELIB_PREPROCESSOR`: Build preprocessor library.
    * Default: ON

* `ELIB_WEB`: Build web library.
    * Default: ON when compiling with GCC >= 4.8.3 or clang and libc++.
        Off otherwise. 
    

## Author

Elib was written by Eric Fiselier.
