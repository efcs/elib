#ifndef DYNAMIC_TEST_HELPER_HPP
#define DYNAMIC_TEST_HELPER_HPP

# include "test_helper.hpp"

# include <elib/fmt.hpp>

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <cstdlib>


# include <elib/assert.hpp>

# ifndef BOOST_REQUIRE
#   error boost unit test must be included before this file
# endif


#define PYTHON_RUN_STR "python " ELIB_FILESYSTEM_UNIT_TEST_PATH "/test_helper.py "


const elib::fs::path test_env_path = test_root / elib::fs::path("test_env");

inline elib::fs::path make_env_path(elib::fs::path const & p)
{
    static const elib::fs::path root_p = ELIB_FILESYSTEM_UNIT_TEST_PATH / elib::fs::path("test_env");
    return root_p / p;
}

inline void python_run(const std::string& cmd)
{
  std::string s = PYTHON_RUN_STR;
  s += "\"";
  s += cmd;
  s += "\"";
  int ret = std::system(s.c_str());
  ELIB_ASSERT_ALWAYS(ret == 0);
}

inline void python_init()
{
    python_run("init()");
}

inline void python_clean()
{
    python_run("clean()");
}

struct scoped_test_env
{
    scoped_test_env() 
    {
        python_init();
    }
    
    scoped_test_env(scoped_test_env const &) = delete;
    scoped_test_env & operator=(scoped_test_env const &) = delete;
    
    ~scoped_test_env()
    {
        python_clean();
    }
};


inline void python_create_file(std::string const & filename, std::size_t size = 0)
{
    python_run(elib::fmt("create_file('%s', %u)", filename, size));
}

inline void python_create_dir(std::string const & filename)
{
    python_run(elib::fmt("create_dir('%s')", filename));
}

inline void python_create_symlink(std::string const & source, std::string const & to)
{
    python_run(elib::fmt("create_symlink('%s', '%s')", source, to));
}

inline void python_create_hardlink(std::string const & source, std::string const & to)
{
    python_run(elib::fmt("create_hardlink('%s', '%s')", source, to));
}

inline void python_create_fifo(std::string const & file)
{
    python_run(elib::fmt("create_fifo('%s')", file));
}

inline void python_create_socket(std::string const & file)
{
    python_run(elib::fmt("create_socket('%s')", file));
}


#endif /* DYNAMIC_TEST_HELPER_HPP */