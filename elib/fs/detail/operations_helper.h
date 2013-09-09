#ifndef ELIB_FS_OPERATIONS_HELPER_H
#define ELIB_FS_OPERATIONS_HELPER_H


#include <elib/fs/config.h>
#include <elib/fs/path.h>
#include <elib/fs/file_status.h>
#include <elib/fs/perms.h>
#include <elib/fs/detail/filesystem_error_helper.h>


#include <system_error>

#include <cstdlib>
#include <climits>


#include <unistd.h>
#include <sys/stat.h>
#include <sys/statvfs.h>


namespace elib {
namespace fs {
namespace detail {
    

    
std::string
_readpath(const char* p_str, std::error_code& ec) noexcept;

void
_statvfs(const char* p_str, std::error_code& ec) noexcept;

perms
_get_perms(const struct stat& st) noexcept;

file_status
_status(const path& p, struct stat& path_stat, std::error_code& ec) noexcept;

uintmax_t
_file_size(const struct stat & st) noexcept;

file_status
_symlink_status(const path& p, struct stat& path_stat, 
                std::error_code & ec) noexcept;
    
bool
_file_status_bad(const file_status & st) noexcept;

path
_path_from_env(const char* name);

std::string
_readlink(const path& p, std::error_code& ec) noexcept;
 
} /* namespace detail */
} /* namespace fs */
} /* namespace elib */


#include <elib/fs/detail/operations_helper_def.h>


#endif /* ELIB_FS_OPERATIONS_HELPER_H */