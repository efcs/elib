#include <elib/posix/unistd.hpp>

#include <elib/CXX14/memory.hpp>

namespace elib
{
  namespace posix
  {
    
    errc_pair<std::string> confstr(int name) noexcept
    {
      errno = 0;
      // Try and guess a good size
      const size_t len = 128;
      auto buff = std::make_unique<char[]>(len);
      size_t size = ::confstr(name, buff.get());
      if (errno || size == 0) 
        return {_handle_errno(), "" };
      if (size <= len)
        return { buff.get() };
      // now we have the size we need
      buff = std::make_unique<char[]>(size);
      ::confstr(name, buff.get());
      if (errno)
        return {_handle_errno(), ""};
      return {_handle_errno(), buff.get()};
    }
    
    
  }                                                          // namespace posix
}                                                           // namespace elib