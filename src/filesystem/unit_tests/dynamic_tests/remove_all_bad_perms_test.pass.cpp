// REQUIRES: ELIB_FILESYSTEM_SOURCE
#include <elib/config.hpp>
#include <elib/filesystem.hpp>
#include <system_error>
#include "../dynamic_test_helper.hpp"
#undef NDEBUG
#include <cassert>
using namespace elib::fs;

constexpr const std::uintmax_t bad_count = static_cast<std::uintmax_t>(-1);

int main()
{
#if !defined(ELIB_CONFIG_CYGWIN)
    scoped_test_env env;
    path const dir1 = env.make_env_path("dir1");
    path const dir2 = dir1 / "dir2";
    env.create_dir(dir1);
    
    permissions(dir1, perms::none);
    
    {
        std::error_code ec;
        auto ret = remove_all(dir2, ec);
        assert(ec);
        assert(ret == bad_count);
    }{
        try {
            remove_all(dir2);
            assert(false);
        } catch (filesystem_error const &) {
          
        } catch (...) {
            assert(false);
        }
    }
    
    permissions(dir1, perms::all);
#endif
}