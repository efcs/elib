#ifndef DYNAMIC_TEST_HELPER_HPP
#define DYNAMIC_TEST_HELPER_HPP

# include "test_helper.hpp"
# include <elib/filesystem/operations.hpp>

# include <elib/fmt.hpp>

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <random>
# include <cstdlib>


# include <elib/assert.hpp>


#define PYTHON_RUN_STR "python " ELIB_FILESYSTEM_UNIT_TEST_PATH "/test_helper.py "


const elib::fs::path test_env_path = test_root / elib::fs::path("dynamic_test_env");

inline elib::fs::path random_env_path()
{
    static const elib::fs::path root_p = ELIB_FILESYSTEM_UNIT_TEST_PATH / elib::fs::path("dynamic_test_env");
    return root_p / elib::fs::unique_path();
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

inline void python_init(std::string const & s)
{
    python_run(elib::fmt("init('%s')", s));
}

inline void python_clean(std::string const & s)
{
    python_run(elib::fmt("clean('%s')", s));
}

struct scoped_test_env
{
    scoped_test_env() 
      : test_root(random_env_path())
    {
        python_init(test_root);
    }
    
    scoped_test_env(scoped_test_env const &) = delete;
    scoped_test_env & operator=(scoped_test_env const &) = delete;
    
    ~scoped_test_env()
    {
        python_clean(test_root);
    }
    
    elib::fs::path make_env_path(elib::fs::path const & p)
    {
        return test_root / p;
    }
    
    std::string sanitize_path(std::string const & raw)
    {
        if (raw.substr(0, test_root.native().size()) == test_root) {
            return raw;
        } else {
            return test_root / elib::fs::path(raw);
        }
    }
    
    void create_file(std::string filename, std::size_t size = 0)
    {
        filename = sanitize_path(filename);
        python_run(elib::fmt("create_file('%s', %u)", filename, size));
    }

    void create_dir(std::string filename)
    {
        filename = sanitize_path(filename);
        python_run(elib::fmt("create_dir('%s')", filename));
    }

    void create_symlink(std::string source, std::string to)
    {
        source = sanitize_path(source);
        to = sanitize_path(to);
        python_run(elib::fmt("create_symlink('%s', '%s')", source, to));
    }

    void create_hardlink(std::string source, std::string to)
    {
        source = sanitize_path(source);
        to = sanitize_path(to);
        python_run(elib::fmt("create_hardlink('%s', '%s')", source, to));
    }

    void create_fifo(std::string file)
    {
        file = sanitize_path(file);
        python_run(elib::fmt("create_fifo('%s')", file));
    }

    void create_socket(std::string file)
    {
        file = sanitize_path(file);
        python_run(elib::fmt("create_socket('%s')", file));
    }

    elib::fs::path const test_root;
};



#endif /* DYNAMIC_TEST_HELPER_HPP */