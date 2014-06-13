#ifndef TEST_HELPER_HPP
#define TEST_HELPER_HPP
# 
# include <elib/assert.hpp>
# 
namespace elib_test_detail 
{
    template <class T, class U>
    struct is_same
    {
        enum { value = 0 };
    };
    
    template <class T>
    struct is_same<T, T>
    {
        enum { value = 1 };
    };
}
# 
# define TEST_ASSERT(...) ELIB_ASSERT_ALWAYS(__VA_ARGS__)
# define TEST_CHECK(...) ELIB_ASSERT_ALWAYS(__VA_ARGS__)
# define TEST_REQUIRE(...) ELIB_ASSERT_ALWAYS(__VA_ARGS__)
# define TEST_WARN(...) ELIB_WARN_ALWAYS(__VA_ARGS__)
# define TEST_STATIC_ASSERT(...) static_assert(__VA_ARGS__, #__VA_ARGS__)
# define TEST_SAME_TYPE(...) TEST_STATIC_ASSERT(::elib_test_detail::is_same<__VA_ARGS__>::value)
# 
# define TEST_NO_THROW(...)                                                           \
    do {                                                                              \
        try {                                                                         \
            __VA_ARGS__;                                                              \
        } catch (...) {                                                               \
            ELIB_ASSERT_ALWAYS(not bool("Operation threw exception: " #__VA_ARGS__)); \
        }                                                                             \
    } while (false)
# 
# define TEST_THROWS(Op, Ex)                                                         \
    do {                                                                             \
        try {                                                                        \
            Op;                                                                      \
            ELIB_ASSERT_ALWAYS(not bool("Operation did not throw exception: " #Op)); \
        } catch (Ex const &) {                                                       \
            /* do nothing */                                                         \
        } catch (...) {                                                              \
            ELIB_ASSERT_ALWAYS(not bool("Operation threw unexpected exception"));    \
        }                                                                            \
    } while (false)
# 
# 
# define TEST_CASE(Name)                                                   \
    void Name();                                                   \
    int main() { try {                                                    \
        Name();                                                    \
    } catch (...) {                                                       \
        ELIB_ASSERT_ALWAYS(!bool("Unexpected exception thrown in test")); \
    }}                                                                    \
    void Name()
        
# 
#endif /* TEST_HELPER_HPP */