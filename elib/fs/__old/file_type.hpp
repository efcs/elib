#ifndef ELIB_FS_FILE_TYPE_HPP
#define ELIB_FS_FILE_TYPE_HPP


namespace elib {
namespace fs {
    

enum class file_type {
    none = 0,
    not_found = -1,
    regular = 1,
    directory = 2,
    symlink = 3,
    block = 4,
    character = 5,
    fifo = 6,
    socket = 7,
    unknown = 8
};
  

} /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_FILE_TYPE_HPP */