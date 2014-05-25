#ifndef ELIB_FILESYSTEM_TEST_HELPER_HPP
#define ELIB_FILESYSTEM_TEST_HELPER_HPP

# include <elib/filesystem/config.hpp>
# include <elib/filesystem/path.hpp>
# include <elib/fmt.hpp>

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <cstdlib>

# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>

# define ELIB_ASSERT_ON
# undef NDEBUG
# include <elib/assert.hpp>

#ifndef ELIB_FILESYSTEM_UNIT_TEST_PATH
# error ELIB_FILESYSTEM_UNIT_TEST_PATH must be set to the directory of this file
# endif

#define PYTHON_RUN_STR "python " ELIB_FILESYSTEM_UNIT_TEST_PATH "/test_helper.py "

const elib::fs::path test_root = ELIB_FILESYSTEM_UNIT_TEST_PATH;
const elib::fs::path test_env_path = test_root / elib::fs::path("test_env");

using stat_t = struct stat;

inline elib::fs::path make_env_path(elib::fs::path const & p)
{
    return test_env_path / p;
}

inline void python_run(const std::string& cmd)
{
  std::string s = PYTHON_RUN_STR;
  s += "\"";
  s += cmd;
  s += "\"";
  int ret = std::system(s.c_str());
  ELIB_ASSERT(ret == 0);
  ((void)ret);
}

inline void python_init()
{
    python_run("clean()");
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



# define READ(name)            \
    in >> tmp;                 \
    ELIB_ASSERT(tmp == #name); \
    ELIB_ASSERT(in);           \
    in >> dest.name;           \
    ELIB_ASSERT(in)
#
inline stat_t read_stat(std::string filename)
{
    elib::fs::path p = make_env_path(filename);
    std::ifstream in(p.native());
    
    stat_t dest;
    std::string tmp;
    
    READ(st_mode);
    READ(st_ino);
    READ(st_dev);
    READ(st_nlink);
    READ(st_uid);
    READ(st_gid);
    READ(st_size);
    READ(st_atime);
    READ(st_mtime);
    
    return dest;
}
# undef READ

inline stat_t python_stat(std::string const & filename)
{
    static std::string to = "stat_tmp_file";
    python_run(elib::fmt("stat('%s', '%s')", filename, to));
    return read_stat(to);
}

inline stat_t python_lstat(std::string const & filename)
{
    static std::string to = "stat_tmp_file";
    python_run(elib::fmt("lstat('%s', '%s')", filename, to));
    return read_stat(to);
}

inline elib::fs::path python_cwd()
{
    static std::string to = "python_tmp_file";
    python_run(elib::fmt("cwd('%s')", to));
    
    elib::fs::path p = test_env_path / elib::fs::path(to);
    std::ifstream in(p.native());
    
    std::string in_str;
    in >> in_str;
    return {in_str};
}

inline void python_create_file(std::string const & filename)
{
    python_run(elib::fmt("create_file('%s')", filename));
}

inline void python_create_empty_file(std::string const & filename)
{
    python_run(elib::fmt("create_empty_file('%s')", filename));
}

inline void python_create_dir(std::string const & filename)
{
    python_run(elib::fmt("create_dir('%s')", filename));
}

inline void python_create_dirs(std::string const & filename)
{
    python_run(elib::fmt("create_dirs('%s')", filename));
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

inline void python_create_node(std::string const & file)
{
    python_run(elib::fmt("create_node('%s')", file));
}

inline void python_remove(std::string const & file)
{
    python_run(elib::fmt("remove('%s')", file));
}

#endif /* ELIB_FILESYSTEM_TEST_HELPER_HPP */