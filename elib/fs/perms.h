#ifndef ELIB_FS_PERMS_H
#define ELIB_FS_PERMS_H


#include <elib/fs/config.h>


namespace elib {
namespace fs {
    

enum class perms : unsigned {
    none = 0,
    owner_read = 0400,
    owner_write = 0200,
    owner_exec = 0100,
    owner_all = 0700,
    group_read = 040,
    group_write = 020,
    group_exec = 010,
    group_all = 070,
    others_read = 04,
    others_write = 02,
    others_exec = 01,
    others_all = 07,
    all = 0777,
    set_uid = 04000,
    set_gid = 02000,
    sticky_bit = 01000,
    mask = 07777,
    unknown = 0xFFFF,
    symlink_perms = 0x4000
};


} /* namespace fs */
} /* namespace elib */


#include <elib/fs/detail/perms_bitwise_operators.h>

#endif /* ELIB_FS_PERMS_H */