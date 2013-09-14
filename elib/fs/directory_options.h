#ifndef ELIB_FS_DIRECTORY_OPTIONS_H
#define ELIB_FS_DIRECTORY_OPTIONS_H


namespace elib {
namespace fs {
    
    
enum class directory_options {
    none,
    follow_directory_symlink,
    skip_permission_denied
};
    
    
} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_DIRECTORY_OPTIONS_H */