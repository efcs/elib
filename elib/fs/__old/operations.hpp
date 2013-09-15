#ifndef ELIB_FS_OPERATIONS_HPP
#define ELIB_FS_OPERATIONS_HPP


#include <elib/fs/config.hpp>
#include <elib/fs/path.hpp>
#include <elib/fs/copy_options.hpp>
#include <elib/fs/space_info.hpp>
#include <elib/fs/file_status.hpp>
#include <elib/fs/file_time_type.hpp>


#include <system_error>


namespace elib {
namespace fs {
    
// forward declare
path
current_path();

    
// absolute
path 
absolute(const path& p, const path& base=current_path());


// canonical
path 
canonical(const path& p, const path& base = current_path());

path 
canonical(const path& p, std::error_code& ec);

path 
canonical(const path& p, const path& base, std::error_code& ec);


// copy
void 
copy(const path& from, const path& to);

void 
copy(const path& from, const path& to, std::error_code& ec) noexcept;

void
copy(const path& from, const path& to, copy_options options);

void
copy(const path& from, const path& to, 
     copy_options options, std::error_code& ec) noexcept;


//copy_file
void 
copy_file(const path& from, const path& to);

void 
copy_file(const path& from, const path& to, std::error_code& ec) noexcept;

void 
copy_file(const path& from, const path& to, copy_options option);

void 
copy_file(const path& from, const path& to, copy_options option,
          std::error_code& ec) noexcept;

          
//copy_symlink
void 
copy_symlink(const path& existing_symlink, const path& new_symlink);

void 
copy_symlink(const path& existing_symlink, const path& new_symlink,
             std::error_code& ec) noexcept;

             
//create_directories
bool 
create_directories(const path& p);

bool 
create_directories(const path& p, std::error_code& ec) noexcept;


// create_directory
bool 
create_directory(const path& p);

bool 
create_directory(const path& p, std::error_code& ec) noexcept;

void 
create_directory(const path& p, const path& attributes);

void 
create_directory(const path& p, const path& attributes, std::error_code& ec) noexcept;


//create_directory_symlink
void 
create_directory_symlink(const path& to, const path& new_symlink);

void 
create_directory_symlink(const path& to, const path& new_symlink,
                         std::error_code& ec) noexcept;


//create_hard_link
void 
create_hard_link(const path& to, const path& new_hard_link);

void 
create_hard_link(const path& to, const path& new_hard_link,
                 std::error_code& ec) noexcept;

                
// create_symlink
void 
create_symlink(const path& to, const path& new_symlink);

void 
create_symlink(const path& to, const path& new_symlink,
               std::error_code& ec) noexcept;

               
// current_path
path 
current_path();

path 
current_path(std::error_code& ec);

void 
current_path(const path& p);

void 
current_path(const path& p, std::error_code& ec) noexcept;


//exists
bool 
exists(file_status s) noexcept;

bool 
exists(const path& p);

bool 
exists(const path& p, std::error_code& ec) noexcept;


//equivalent
bool 
equivalent(const path& p1, const path& p2);

bool 
equivalent(const path& p1, const path& p2, std::error_code& ec) noexcept;


//file_size
uintmax_t 
file_size(const path& p);

uintmax_t 
file_size(const path& p, std::error_code& ec) noexcept;


//hard_link_count
uintmax_t 
hard_link_count(const path& p);

uintmax_t 
hard_link_count(const path& p, std::error_code& ec) noexcept;


//is_block_file
bool 
is_block_file(file_status s) noexcept;

bool 
is_block_file(const path& p);

bool 
is_block_file(const path& p, std::error_code& ec) noexcept;


//is_character_file
bool 
is_character_file(file_status s) noexcept;

bool 
is_character_file(const path& p);

bool 
is_character_file(const path& p, std::error_code& ec) noexcept;


//is_directory
bool 
is_directory(file_status s) noexcept;

bool 
is_directory(const path& p);

bool 
is_directory(const path& p, std::error_code& ec) noexcept;


//is_empty
bool 
is_empty(const path& p);

bool 
is_empty(const path& p, std::error_code& ec) noexcept;


//is_fifo
bool 
is_fifo(file_status s) noexcept;

bool 
is_fifo(const path& p);

bool 
is_fifo(const path& p, std::error_code& ec) noexcept;


//is_other
bool
is_other(file_status s) noexcept;

bool
is_other(const path& p);

bool
is_other(const path& p, std::error_code& ec) noexcept;


//is_regular_file
bool
is_regular_file(file_status s) noexcept; 

bool
is_regular_file(const path& p);

bool
is_regular_file(const path& p, std::error_code& ec) noexcept;


//is_socket
bool
is_socket(file_status s) noexcept;

bool
is_socket(const path& p);

bool
is_socket(const path& p, std::error_code& ec) noexcept;


//is_symlink
bool
is_symlink(file_status s) noexcept;

bool
is_symlink(const path& p);

bool
is_symlink(const path& p, std::error_code& ec) noexcept;


//last_write_time
file_time_type  
last_write_time(const path& p);

file_time_type  
last_write_time(const path& p, std::error_code& ec) noexcept;

void
last_write_time(const path& p, file_time_type new_time);

void
last_write_time(const path& p, file_time_type new_time,
                std::error_code& ec) noexcept;
      

// permissions
void 
permissions(const path& p, perms prms);

void 
permissions(const path& p, perms prms, std::error_code& ec) noexcept;

                
// read_symlink
path 
read_symlink(const path& p);

path 
read_symlink(const path& p, std::error_code& ec);


//remove
bool
remove(const path& p);

bool
remove(const path& p, std::error_code& ec) noexcept;


//remove_all
uintmax_t 
remove_all(const path& p);

uintmax_t 
remove_all(const path& p, std::error_code& ec) noexcept;

//rename
void
rename(const path& from, const path& to);

void
rename(const path& from, const path& to, std::error_code& ec) noexcept;


//resize_file
void
resize_file(const path& p, uintmax_t size);

void
resize_file(const path& p, uintmax_t size, std::error_code& ec) noexcept;


//space
space_info   
space(const path& p);

space_info   
space(const path& p, std::error_code& ec) noexcept;


//file_status
file_status  
status(const path& p);

file_status  
status(const path& p, std::error_code& ec) noexcept;


//status_known
bool
status_known(file_status s) noexcept;

file_status  
symlink_status(const path& p);

file_status  
symlink_status(const path& p, std::error_code& ec) noexcept;

path 
system_complete(const path& p);

path 
system_complete(const path& p, std::error_code& ec);

path 
temp_directory_path();

path 
temp_directory_path(std::error_code& ec);


path 
unique_path(const path& model="%%%%-%%%%-%%%%-%%%%");

path 
unique_path(const path& model, std::error_code& ec);


} /* namespace fs */
} /* namespace elib */


#ifdef ELIB_FS_DEFINITIONS_INLINE
#include <elib/fs/detail/operations_def.hpp>
#endif

#endif /* ELIB_FS_OPERATIONS_HPP */