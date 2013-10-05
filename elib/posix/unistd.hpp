#ifndef ELIB_POSIX_UNISTD_HPP
# define ELIB_POSIX_UNISTD_HPP

# include <elib/config.hpp>

# include <string>
# include <vector>
# include <utility>
# include <system_error>
# include <cstddef>
# include <cerrno>

# include <unistd.h>


namespace elib 
{
  namespace posix
  {
   
   
   // For clarity, some typedefs are provided instead of using raw ints
    typedef int fd_t;
   
    
    template <typename T>
    using errc_pair = std::pair<std::error_code, T>;
    
    
    inline void _reset_errno() noexcept
    {
      errno = 0;
    }
    
    inline std::error_code _handle_errno() noexcept
    {
      return {errno, std::system_catagory()}; 
    }
    
    template <typename T>
    inline errc_pair<T> _handle_errno(T&& second)
    {
      return {_handle_errno(), std::forward<T>(second)};
    }
    
    template <typename Fn, typename... Args>
    inline std::error_code _handle_errc_fn(Fn&& fn, Args&&... args) 
    {
      auto posix_fn = 
            std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...);
            
      _reset_errno();
      posix_fn();
      return _handle_errno();
    }
   
    ////////////////////////////////////////////////////////////////////////////////
    //                        C++ Posix Functions interface                                                  
    ////////////////////////////////////////////////////////////////////////////////
    
    /* Concept: POSIX C functions commonly handle raw resources and manipulate
     * errno. for  a C++ end user this is non-optimal. 
     * ELIB POSIX attemps to provide a C++ friendly inteface in terms of
     * error and resource handling. Since the POSIX interfaces varies greatly
     * it the use of it's return type, and it's resource ownership rules, it was
     * not possible to make a consistent interface. There are a couple of common
     * patterns. 
     * 
     * ALL ELIB POSIX functions will reset errno before and after each function
     * they wrap.
     * 
     * When the POSIX function requires the user to pass in a input buffer
     * THEN the return type is errc_pair<C++ Resource Handler>
     * C++ Resource handler in an C++ class that handles an C resource type.
     * Mappings from C resource type to C++ resource handler are typically 
     * as follows
     * 
     *    C         --->      C++
     *  const char*       std::string
     *  void*             std::vector<char>
     * 
     * When the POSIX func never set's errno, the ELIB POSIX return type is 
     * typicaly the same as the POSIX type.
     * 
     * When the POSIX func returns 0 on success and -1 on failure, 
     * AND errno must be set on failure,
     * AND resource allocation has NOT been abstracted out
     * THEN the return type is an std::error_code and is contains errno on failure.
     * 
     * When a POSIX func returns 0 on success and -1 on failure, 
     * AND errno MIGHT NOT be set on failure, 
     * THEN the return type is std::pair<std::error_code, POSIX return type>
     *
     */
    
    /** determine accessibility of a file relative to directory file descriptor
     * @posix int access(const char*, int)
     * @posix_return 0 on success, -1 on failure and errno is set
     * @return value of errno
     */
    inline std::error_code access(const std::string& path,  int amode) noexcept
    {
      return _handle_errc_fn(&::access, path.c_str(), amode);
    }
    
    
    /** schedule an alarm by signal
     * @posix unsigned alarm(unsigned)
     * @posix_return 0 if no previous alarm, otherwise seconds until
     *               until previous alarm
     * @return same as @posix_return
     */
    inline unsigned alarm(unsigned seconds) noexcept
    {
      return ::alarm(seconds);
    }
    
    /** change working directory.
     * @posix int chdir(const char*);
     * @posix_return 0 on success, -1 on failure && errno is set
     * @return value of errno
     */
    inline std::error_code chdir(const std::string& path) noexcept
    {
      return _handle_errc_fn(path.c_str());
    }
    
    /** 
     * change owner and group of a file relative to directory file descriptor
     * @posix int chown(const char*, uid_t, gid_t)
     * @posix_return 0 on success, -1 on failure and errno is set
     * @return the value of errno
     */
    std::error_code chown(const std::string& path,  uid_t owner, 
                          gid_t group) noexcept
    {
      return _handle_errc_fn(&::chown, path.c_str(), owner, group);
    }
    
    /** 
     * close a file descriptor
     * @posix int close(int)
     * @posix_return 0 on success, -1 on failure and errno is set
     * @return the value of errno
     */
    std::error_code close(fd_t fd) noexcept
    {
      return _handle_errc_fn(&::close, fd);
    }
    
    /** 
     * get configurable size
     * @posix size_t confstr(int, char *buf, size_t len)
     * @posix_return unspecified
     * @return The value of errno and the string value.
     *         the string may be empty even when errno is unset.
     */
    errc_pair<std::string> confstr(int name) noexcept;
    
    errc_pair<std::string> 
    crypt(const std::string& key, const std::string& salt) noexcept;
    
    errc_pair<fd_t> dup(fd_t file_desc) noexcept;
    
    errc_pair<fd_t> dup2(fd_t file_desc, fd_t file_desc2) noexcept;
    
    [[noreturn]] void _exit(int status) noexcept
    {
      ::_exit(status);
    }
    
    std::error_code encrypt(char (&block)[64], int edflag) noexcept;
    
    // TODO execl
    // TODO execle
    // TODO execlp
    // TODO execv
    // TODO execve
    // TODO execvp
    
    std::error_code faccessat(fd_t fd, const std::string& path,  
                              int amode,  int flag) noexcept;
                              
    std::error_code fchdir(fd_t fd) noexcept;
    
    std::error_code fchown(fd_t, uid_t, gid_t) noexcept;
    
    std::error_code fchownat(fd_t, const std::string& path, uid_t, gid_t, int) noexcept;
    
    std::error_code fdatasync(fd_t) noexcept;
    
    //TODO fexecve
    
    errc_pair<pid_t> fork() noexcept;
    
    errc_pair<long> fpathconf(fd_t fd, int name) noexcept;
    
    std::error_code fsync(fd_t fd) noexcept;
    
    std::error_code ftruncate(fd_t fd, off_t len) noexcept;
    
    errc_pair<std::string> getcwd() noexcept;
    
    gid_t getegid() noexcept;
    
    uid_t geteuid() noexcept;
    
    gid_t getget() noexcept;
    
    template <std::size_t N>
    errc_pair<int> getgroups(gid_t (&grouplist)[N]) noexcept;
                                            
    long gethostid() noexcept;
    
    // gethostname can fail, but it doesn't set errno. Should
    // the return type be std::pair<error_code, string>
    std::string gethostname() noexcept;
    
    errc_pair<std::string> getlogin() noexcept;
    
    errc_pair<std::string> getlogin_r() noexcept;
    
    //TODO getopt? 
    
    errc_pair<pid_t> getpgid(pid_t pid) noexcept;
    
    pid_t getpgrp() noexcept;
    
    pid_t getpid() noexcept;
    
    pid_t getppid() noexcept;
    
    errc_pair<pid_t> getsid(pid_t pid) noexcept;
    
    uid_t getuid() noexcept;
    
    errc_pair<bool> isatty(fd_t fd) noexcept;
    
    std::error_code lchown(const std::string& path, uid_t owner, 
                           gid_t group) noexcept;
    
    std::error_code link(const std::string& path1, 
                         const std::string& path2) noexcept;
                         
    
    std::error_code linkat(fd_t fd1,  const std::string& path1, 
                           fd_t fd2, const std::string& path2) noexcept;
                           
                           
    std::error_code lockf(fd_t fd, int func, off_t size) noexcept;
                           
                          
    errc_pair<off_t> lseek(fd_t fd, off_t offset, 
                                            int whence) noexcept;
                                            
    errc_pair<int> nice(int incr) noexcept;
    
    errc_pair<long> pathconf(const std::string& path, 
                                              int name) noexcept;
                                              
    std::error_code pause() noexcept;
    
    std::error_code pipe(fd_t (&filedes)[2]) noexcept;
    
    template <typename T>
    errc_pair<std::unique_ptr<T[]>>
    pread(fd_t fd, size_t nbytes, off_t offset) noexcept;
    
    template <typename T>
    errc_pair<ssize_t>
    pwrite(fd_t fd, const T* buff, size_t nbytes, off_t offset) noexcept;
    
    template <typename T>
    errc_pair< std::unique_ptr<T[]>> 
    read(fd_t fd, size_t nbytes) noexcept;
    
    template <typename T>
    errc_pair<std::string>
    readlink(const std::string& path) noexcept;
    
    template <typename T>
    errc_pair<std::string>
    readlinkat(const std::string& path) noexcept;
    
    std::error_code rmdir(const std::string& path) noexcept;
    
    std::error_code setegid(gid_t gid) noexcept;
    
    std::error_code seteuid(uid_t uid) noexcept;
    
    std::error_code setgid(gid_t gid) noexcept;
    
    std::error_code setpgid(pid_t pid, pid_t gpid) noexcept;
    
    pid_t setpgrp() noexcept;
    
    std::error_code setregid(gid_t rgid, gid_t egid) noexcept;
    
    std::error_code setreuid(uid_t ruid, uid_t euid) noexcept;
    
    errc_pair<pid_t> setsid() noexcept;
    
    std::error_code setuid(uid_t uid) noexcept;
    
    unsigned sleep(unsigned seconds) noexcept;
    
    //TODO swab
    
    std::error_code symlink(const std::string& path1, 
                            const std::string& path2) noexcept;
    
    std::error_code symlinkat(const std::string& path1, fd_t fd, 
                              const std::string& path2) noexcept;
                              
    void sync() noexcept
    {
      ::sync();
    }
    
    errc_pair<long>  sysconf(int name) noexcept;
    
    errc_pair<pid_t> tcgetpgrp(fd_d fd) noexcept;
    
    std::error_code tcsetpgrp(fd_t fd, pid_t pgid_id) noexcept;
    
    std::error_code truncate(const std::string& path,  off_t length) noexcept;
    
    errc_pair<std::string> ttyname(fd_t fd) noexcept;
    
    errc_pair<std::string> ttyname_r(fd_t fd, 
                                                std::size_t namesize) noexcept;
                                                
    std::error_code unlink(const std::string& path) noexcept;
    
    std::error_code unlinkat(fd_t fd, const std::string& path, int flag) noexcept;
    
    template <typename T>
    errc_pair<ssize_t> write(fd_t fd, const T* buf, size_t nbytes) noexcept;
    
    
  
  }                                                         // namespace posix
}                                                           // namespace elib
#endif /* ELIB_POSIX_UNISTD_HPP */