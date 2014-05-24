#ifndef ELIB_FILESYSTEM_DETAIL_PATH_CONVERTER_HPP
#define ELIB_FILESYSTEM_DETAIL_PATH_CONVERTER_HPP

# include <elib/aux/convert.hpp>
# include <elib/aux/traits/decay.hpp>
#include <locale>
#include <string>
#include <cwchar>
#include <vector>
#include <list>
#include <type_traits>


namespace elib { namespace fs { inline namespace v1
{
    
    class directory_entry;    

    namespace detail 
    {
        template <typename T>
        struct is_pathable_impl : public std::false_type { };

        template <>
        struct is_pathable_impl<char*> : public std::true_type { };

        template <>
        struct is_pathable_impl<const char*> : public std::true_type { };

        template <>
        struct is_pathable_impl<std::string> : public std::true_type { };

        template <>
        struct is_pathable_impl<std::vector<char>> : public std::true_type { };

        template <>
        struct is_pathable_impl<std::list<char>> : public std::true_type { };

        template <>
        struct is_pathable_impl<directory_entry> : public std::true_type { };
        
        template <class T>
        using is_pathable = is_pathable_impl<aux::decay_t<T>>;

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
    
    }                                                       // namespace detail
}}}                                                       // namespace elib::fs
#endif /* ELIB_FILESYSTEM_DETAIL_PATH_CONVERTER_HPP */