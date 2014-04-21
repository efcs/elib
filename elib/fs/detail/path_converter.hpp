#ifndef ELIB_FS_CONVERSION_HPP
#define ELIB_FS_CONVERSION_HPP

#include <locale>
#include <string>
#include <cwchar>
#include <vector>
#include <list>
#include <type_traits>


namespace elib 
{
  namespace fs 
  {
    
    class directory_entry;    

    namespace detail 
    {
      template <typename T>
      struct is_pathable : public std::false_type { };

      template <>
      struct is_pathable<char*> : public std::true_type { };

      template <>
      struct is_pathable<const char*> : public std::true_type { };

      template <>
      struct is_pathable<std::string> : public std::true_type { };

      template <>
      struct is_pathable<std::vector<char>> : public std::true_type { };

      template <>
      struct is_pathable<std::list<char>> : public std::true_type { };

      template <>
      struct is_pathable<directory_entry> : public std::true_type { };

      template <typename Ret>
      Ret
      convert(const std::string& s);

      template <>
      inline std::string
      convert(const std::string& s)
      { return s; }

      template <typename Ret>
      inline Ret
      dispatch(const char* from)
      {
          return convert<Ret>(std::string{from});
      }

      template <typename Ret>
      inline Ret
      dispatch(const std::string& from)
      {
          return convert<Ret>(from);
      }

      template <typename Ret>
      inline Ret
      dispatch(const std::vector<char>& from)
      {
          return convert<Ret>(std::string{from.begin(), from.end()});
      }

      template <typename Ret>
      inline Ret
      dispatch(const std::list<char>& from)
      {
          return convert<Ret>(std::string{from.begin(), from.end()});
      }

      template <typename Ret>
      Ret
      dispatch(const directory_entry& from);

      template <>
      std::string
      dispatch(const directory_entry& from);


    
    } /* namespace detail */
  } /* namespace fs */
} /* namespace elib */
#endif /* ELIB_FS_CONVERSION_HPP */