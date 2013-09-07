#ifndef ELIB_FS_COPY_OPTIONS_H
#define ELIB_FS_COPY_OPTIONS_H


namespace elib {
namespace fs {
    

enum class copy_options {
    none = 0,
    skip_existing = 1,
    overwrite_existing = 2,
    update_existing = 4,
    recursive = 8,
    copy_symlinks = 16,
    skip_symlinks = 32,
    directories_only = 64,
    create_symlinks = 128,
    create_hard_links = 256
};
    

} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_COPY_OPTIONS_H */