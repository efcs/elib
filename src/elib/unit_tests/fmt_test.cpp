#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <elib/fmt.hpp>
#include <elib/aux.hpp>
#include <string>
#include <iostream>
#include <typeinfo>

using namespace elib;

using fmt_detail::implicit_cast_conversion_tag;
using fmt_detail::explicit_cast_conversion_tag;
using fmt_detail::stream_insertion_conversion_tag;
using fmt_detail::to_string_function_conversion_tag;
using fmt_detail::bad_conversion_tag;

using fmt_detail::conversion_tag;

struct implicit_type
{    
    implicit_type(std::string const & str)
      : m_str(str)
    {}
    
    operator std::string() const { return m_str; }

private:
    std::string m_str;
};

struct explicit_type
{
    explicit_type(std::string const & str)
      : m_str(str)
    {}
    
    explicit operator std::string() const { return m_str; }

private:
    std::string m_str;
};

struct stream_type 
{
    stream_type(std::string const & str)
      : m_str(str)
    {}
    
    friend std::ostream & operator<<(std::ostream &, stream_type const &);
private:
    std::string m_str;
};

std::ostream & operator<<(std::ostream & out, stream_type const & s)
{
    out << s.m_str;
    return out;
}

struct to_string_type 
{
    to_string_type(std::string const & s)
      : m_str(s)
    {}
    
    friend std::string to_string(to_string_type const &);
private:
    std::string m_str;
};

std::string to_string(to_string_type const & s)
{
    return s.m_str;
}

struct none_type {};


#define CHECK_ALL_TYPES(Trait, Type)        \
    BOOST_CHECK(( Trait<Type>() ));         \
    BOOST_CHECK(( Trait<Type const>() ));   \
    BOOST_CHECK(( Trait<Type &>() ));       \
    BOOST_CHECK(( Trait<Type &&>() ));      \
    BOOST_CHECK(( Trait<Type const &>() )); \
    BOOST_CHECK(( Trait<Type const &&>() ))
#

#define CHECK_ALL_PTR_TYPES(Trait, Type)           \
    BOOST_CHECK(( Trait<Type*>() ));               \
    BOOST_CHECK(( Trait<Type const*>() ));         \
    BOOST_CHECK(( Trait<Type* const>() ));         \
    BOOST_CHECK(( Trait<Type const* const>() ));   \
    BOOST_CHECK(( Trait<Type* &>() ));             \
    BOOST_CHECK(( Trait<Type* &&>() ));            \
    BOOST_CHECK(( Trait<Type const* &>() ));       \
    BOOST_CHECK(( Trait<Type const* &&>() ));      \
    BOOST_CHECK(( Trait<Type const* const &>() )); \
    BOOST_CHECK(( Trait<Type const* const &&>() ))
    

BOOST_AUTO_TEST_SUITE(fmt_test_suite)


BOOST_AUTO_TEST_CASE(implicit_conversion_test)
{
    CHECK_ALL_TYPES( has_implicit_string_cast, std::string );
    CHECK_ALL_PTR_TYPES( not has_implicit_string_cast, std::string );
    
    CHECK_ALL_PTR_TYPES(has_implicit_string_cast, char);
    
    CHECK_ALL_TYPES( has_implicit_string_cast, implicit_type );
    CHECK_ALL_TYPES( not has_implicit_string_cast, explicit_type );
    CHECK_ALL_TYPES( not has_implicit_string_cast, stream_type );
    CHECK_ALL_TYPES( not has_implicit_string_cast, to_string_type );
    CHECK_ALL_TYPES( not has_implicit_string_cast, none_type );
    
    BOOST_CHECK( not has_implicit_string_cast<void>() );
    CHECK_ALL_PTR_TYPES( not has_implicit_string_cast, void );
    BOOST_CHECK( not has_implicit_string_cast<int>() );
    BOOST_CHECK( not has_implicit_string_cast<float>() );
}

// NOTE: this should be false if the type is implicitly convertible
BOOST_AUTO_TEST_CASE(explicit_conversion_test)
{
    CHECK_ALL_TYPES( has_explicit_string_cast, explicit_type );
    
    CHECK_ALL_TYPES( not has_explicit_string_cast, std::string );
    CHECK_ALL_PTR_TYPES( not has_explicit_string_cast, char );
    
    CHECK_ALL_TYPES( not has_explicit_string_cast, implicit_type );
    CHECK_ALL_TYPES(     has_explicit_string_cast, explicit_type );
    CHECK_ALL_TYPES( not has_explicit_string_cast, stream_type );
    CHECK_ALL_TYPES( not has_explicit_string_cast, to_string_type );
    CHECK_ALL_TYPES( not has_explicit_string_cast, none_type );
    
    BOOST_CHECK( not has_explicit_string_cast<void>() );
    CHECK_ALL_PTR_TYPES( not has_explicit_string_cast, void );
    BOOST_CHECK( not has_explicit_string_cast<int>() );
    BOOST_CHECK( not has_explicit_string_cast<float>() );
}

BOOST_AUTO_TEST_CASE(has_stream_insertion_test)
{
    CHECK_ALL_TYPES( has_stream_insertion, std::string );
    CHECK_ALL_PTR_TYPES( has_stream_insertion, char );
    CHECK_ALL_TYPES( has_stream_insertion, stream_type );
    
    CHECK_ALL_TYPES( not has_stream_insertion, implicit_type );
    CHECK_ALL_TYPES( not has_stream_insertion, explicit_type );
    CHECK_ALL_TYPES(     has_stream_insertion, stream_type );
    CHECK_ALL_TYPES( not has_stream_insertion, to_string_type );
    CHECK_ALL_TYPES( not has_stream_insertion, none_type );
    
    CHECK_ALL_TYPES( has_stream_insertion, bool );
    CHECK_ALL_TYPES( has_stream_insertion, char );
    CHECK_ALL_TYPES( has_stream_insertion, short );
    CHECK_ALL_TYPES( has_stream_insertion, unsigned short );
    CHECK_ALL_TYPES( has_stream_insertion, int );
    CHECK_ALL_TYPES( has_stream_insertion, unsigned int );
    CHECK_ALL_TYPES( has_stream_insertion, long );
    CHECK_ALL_TYPES( has_stream_insertion, unsigned long );
    CHECK_ALL_TYPES( has_stream_insertion, long long );
    CHECK_ALL_TYPES( has_stream_insertion, unsigned long long );
    CHECK_ALL_TYPES( has_stream_insertion, float );
    CHECK_ALL_TYPES( has_stream_insertion, double );
    CHECK_ALL_TYPES( has_stream_insertion, long double );
    CHECK_ALL_TYPES( has_stream_insertion, void* );
}

BOOST_AUTO_TEST_CASE( has_to_string_test )
{
    CHECK_ALL_TYPES( has_to_string, to_string_type );
    
    CHECK_ALL_TYPES( not has_to_string, std::string );
    CHECK_ALL_PTR_TYPES( not has_to_string, char );
    
    CHECK_ALL_TYPES( not has_to_string, implicit_type );
    CHECK_ALL_TYPES( not has_to_string, explicit_type );
    CHECK_ALL_TYPES( not has_to_string, stream_type );
    CHECK_ALL_TYPES(     has_to_string, to_string_type );
    CHECK_ALL_TYPES( not has_to_string, none_type );
}

BOOST_AUTO_TEST_CASE( has_string_conversion_test )
{
    CHECK_ALL_TYPES( has_string_conversion, std::string );
    CHECK_ALL_PTR_TYPES( has_string_conversion, char );
    
    CHECK_ALL_TYPES( has_string_conversion, implicit_type );
    CHECK_ALL_TYPES( has_string_conversion, explicit_type );
    CHECK_ALL_TYPES( has_string_conversion, stream_type );
    CHECK_ALL_TYPES( has_string_conversion, to_string_type );
    CHECK_ALL_TYPES( not has_string_conversion, none_type );
    
    CHECK_ALL_TYPES( has_string_conversion, bool );
    CHECK_ALL_TYPES( has_string_conversion, char );
    CHECK_ALL_TYPES( has_string_conversion, short );
    CHECK_ALL_TYPES( has_string_conversion, unsigned short );
    CHECK_ALL_TYPES( has_string_conversion, int );
    CHECK_ALL_TYPES( has_string_conversion, unsigned int );
    CHECK_ALL_TYPES( has_string_conversion, long );
    CHECK_ALL_TYPES( has_string_conversion, unsigned long );
    CHECK_ALL_TYPES( has_string_conversion, long long );
    CHECK_ALL_TYPES( has_string_conversion, unsigned long long );
    CHECK_ALL_TYPES( has_string_conversion, float );
    CHECK_ALL_TYPES( has_string_conversion, double );
    CHECK_ALL_TYPES( has_string_conversion, long double );
    CHECK_ALL_TYPES( has_string_conversion, void* );
    
    BOOST_CHECK( not has_string_conversion<void>() );
}


#define CHECK_TAG(Expect, Type) \
    BOOST_CHECK(( aux::is_same<Expect, conversion_tag<Type>>() ))
#
    
#define CHECK_TAG_ALL_TYPES(Expect, Type) \
    CHECK_TAG(Expect, Type);              \
    CHECK_TAG(Expect, Type const);        \
    CHECK_TAG(Expect, Type &);            \
    CHECK_TAG(Expect, Type &&);           \
    CHECK_TAG(Expect, Type const &);      \
    CHECK_TAG(Expect, Type const &&)
#

BOOST_AUTO_TEST_CASE(conversion_tag_test)
{
    using icast_tag = implicit_cast_conversion_tag;
    using ecast_tag = explicit_cast_conversion_tag;
    using stream_tag = stream_insertion_conversion_tag;
    using tostr_tag = to_string_function_conversion_tag;
    using bad_tag = bad_conversion_tag;
    
    CHECK_TAG_ALL_TYPES(icast_tag, std::string);
    CHECK_TAG_ALL_TYPES(icast_tag, char*);
    CHECK_TAG_ALL_TYPES(icast_tag, implicit_type);
    
    CHECK_TAG_ALL_TYPES(ecast_tag, explicit_type);
    
    CHECK_TAG_ALL_TYPES(stream_tag, stream_type);
    CHECK_TAG_ALL_TYPES(stream_tag, bool);
    CHECK_TAG_ALL_TYPES(stream_tag, char);
    CHECK_TAG_ALL_TYPES(stream_tag, short);
    CHECK_TAG_ALL_TYPES(stream_tag, unsigned short);
    CHECK_TAG_ALL_TYPES(stream_tag, int);
    CHECK_TAG_ALL_TYPES(stream_tag, unsigned int);
    CHECK_TAG_ALL_TYPES(stream_tag, long);
    CHECK_TAG_ALL_TYPES(stream_tag, unsigned long);
    CHECK_TAG_ALL_TYPES(stream_tag, long long);
    CHECK_TAG_ALL_TYPES(stream_tag, unsigned long long);
    CHECK_TAG_ALL_TYPES(stream_tag, float);
    CHECK_TAG_ALL_TYPES(stream_tag, double);
    CHECK_TAG_ALL_TYPES(stream_tag, long double);
    CHECK_TAG_ALL_TYPES(stream_tag, void* );
    
    CHECK_TAG_ALL_TYPES(tostr_tag, to_string_type);
    
    CHECK_TAG_ALL_TYPES(bad_tag, none_type);
}


#define CHECK_MAKE_ALL_TYPES(Expect, Type, Value)                          \
    BOOST_CHECK(( Expect == make_str(static_cast<Type>(Value)) ));         \
    BOOST_CHECK(( Expect == make_str(static_cast<Type const>(Value)) ));   \
    BOOST_CHECK(( Expect == make_str(static_cast<Type &>(Value)) ));       \
    BOOST_CHECK(( Expect == make_str(static_cast<Type &&>(Value)) ));      \
    BOOST_CHECK(( Expect == make_str(static_cast<Type const &>(Value)) )); \
    BOOST_CHECK(( Expect == make_str(static_cast<Type const &&>(Value)) ))

BOOST_AUTO_TEST_CASE( make_str_test )
{
    // std::string test
    {
        std::string s = "string";
        CHECK_MAKE_ALL_TYPES("string", std::string, s);
    }
    // char* test
    {
        const char *s = "cstring";
        CHECK_MAKE_ALL_TYPES("cstring", const char*, s);
    }
    // implicit_type
    {
        implicit_type t("implicit_type");
        CHECK_MAKE_ALL_TYPES("implicit_type", implicit_type, t);
    }
    // explicit type
    {
        explicit_type t("explicit_type");
        CHECK_MAKE_ALL_TYPES("explicit_type", explicit_type, t);
    }
    // stream_type
    {
        stream_type t("stream_type");
        CHECK_MAKE_ALL_TYPES("stream_type", stream_type, t);
    }
    // to_string_type
    {
        to_string_type t("to_string_type");
        CHECK_MAKE_ALL_TYPES("to_string_type", to_string_type, t);
    }
    // bool type
    {
        bool b = true;
        CHECK_MAKE_ALL_TYPES("true", bool, b);
        b = false;
        CHECK_MAKE_ALL_TYPES("false", bool, b);
    }
    // char type
    {
        char ch = 'a';
        CHECK_MAKE_ALL_TYPES("a", char, ch);
        ch = '\n';
        CHECK_MAKE_ALL_TYPES("\n", char, ch);
    }
    // int type
    {
        int i = 0;
        CHECK_MAKE_ALL_TYPES("0", int, i);
        i = 1;
        CHECK_MAKE_ALL_TYPES("1", int, i);
        i = -1;
        CHECK_MAKE_ALL_TYPES("-1", int, i);
        i = 123456789;
        CHECK_MAKE_ALL_TYPES("123456789", int, i);
    }
    // unsigned type
    {
        unsigned i = 0;
        CHECK_MAKE_ALL_TYPES("0", unsigned, i);
        i = 1;
        CHECK_MAKE_ALL_TYPES("1", unsigned, i);
    }
}

#undef CHECK_MAKE_ALL_TYPES

BOOST_AUTO_TEST_CASE( build_str_and_cat_str_test )
{
    std::ostringstream ss;
    
    // cstr test
    {
        ss.clear();
        ss.str("");
        build_str(ss, "");
        BOOST_CHECK(ss);
        BOOST_CHECK(ss.str() == "");
        BOOST_CHECK(cat_str("") == "");
    }
    // std::string test
    {
        ss.clear();
        ss.str("");
        std::string s("hello");
        build_str(ss, s);
        BOOST_CHECK(ss);
        BOOST_CHECK(ss.str() == s);
        BOOST_CHECK(cat_str(s) == s);
    }
    // integral test
    {
        ss.clear();
        ss.str("");
        bool b = true;
        char ch = 'a';
        int i = -1;
        unsigned u = 1;
        build_str(ss, b, " ", ch, " ", i, " " , u);
        std::string cat = cat_str(b, " ", ch, " ", i, " ", u);
        BOOST_CHECK(ss);
        BOOST_CHECK( ss.str() == "true a -1 1");
        BOOST_CHECK( cat      == "true a -1 1");
    }
    {
        ss.clear();
        ss.str("");
        implicit_type i("implicit");
        explicit_type e("explicit");
        stream_type s("stream");
        to_string_type t("to_string");
        build_str(ss, i, " ", e, " ", s, " ", t);
        std::string cat = cat_str(i, " ", e, " ", s, " ", t);
        BOOST_CHECK(ss);
        BOOST_CHECK(ss.str() == "implicit explicit stream to_string");
        BOOST_CHECK(cat      == "implicit explicit stream to_string");
    }
}

BOOST_AUTO_TEST_CASE( is_cfmt_type_test )
{
    CHECK_ALL_TYPES( is_cfmt_type, bool );
    CHECK_ALL_TYPES( is_cfmt_type, char );
    CHECK_ALL_TYPES( is_cfmt_type, short );
    CHECK_ALL_TYPES( is_cfmt_type, unsigned short );
    CHECK_ALL_TYPES( is_cfmt_type, int );
    CHECK_ALL_TYPES( is_cfmt_type, unsigned int );
    CHECK_ALL_TYPES( is_cfmt_type, long );
    CHECK_ALL_TYPES( is_cfmt_type, unsigned long );
    CHECK_ALL_TYPES( is_cfmt_type, long long );
    CHECK_ALL_TYPES( is_cfmt_type, unsigned long long );
    CHECK_ALL_TYPES( is_cfmt_type, float );
    CHECK_ALL_TYPES( is_cfmt_type, double );
    CHECK_ALL_TYPES( is_cfmt_type, long double );
    CHECK_ALL_PTR_TYPES( is_cfmt_type, char );
    CHECK_ALL_PTR_TYPES( is_cfmt_type, void );
    
    BOOST_CHECK( not is_cfmt_type<void>() );
    CHECK_ALL_TYPES( not is_cfmt_type, std::string );
    CHECK_ALL_TYPES( not is_cfmt_type, implicit_type );
    CHECK_ALL_TYPES( not is_cfmt_type, explicit_type );
    CHECK_ALL_TYPES( not is_cfmt_type, stream_type );
    CHECK_ALL_TYPES( not is_cfmt_type, to_string_type );
    CHECK_ALL_TYPES( not is_cfmt_type, none_type );
}

BOOST_AUTO_TEST_CASE( is_fmt_type_test )
{
    CHECK_ALL_TYPES( is_fmt_type, bool );
    CHECK_ALL_TYPES( is_fmt_type, char );
    CHECK_ALL_TYPES( is_fmt_type, short );
    CHECK_ALL_TYPES( is_fmt_type, unsigned short );
    CHECK_ALL_TYPES( is_fmt_type, int );
    CHECK_ALL_TYPES( is_fmt_type, unsigned int );
    CHECK_ALL_TYPES( is_fmt_type, long );
    CHECK_ALL_TYPES( is_fmt_type, unsigned long );
    CHECK_ALL_TYPES( is_fmt_type, long long );
    CHECK_ALL_TYPES( is_fmt_type, unsigned long long );
    CHECK_ALL_TYPES( is_fmt_type, float );
    CHECK_ALL_TYPES( is_fmt_type, double );
    CHECK_ALL_TYPES( is_fmt_type, long double );
    CHECK_ALL_PTR_TYPES( is_fmt_type, char );
    CHECK_ALL_PTR_TYPES( is_fmt_type, void );
    
    CHECK_ALL_TYPES( is_fmt_type, std::string );
    
    BOOST_CHECK( not is_fmt_type<void>() );
    CHECK_ALL_TYPES( not is_fmt_type, implicit_type );
    CHECK_ALL_TYPES( not is_fmt_type, explicit_type );
    CHECK_ALL_TYPES( not is_fmt_type, stream_type );
    CHECK_ALL_TYPES( not is_fmt_type, to_string_type );
    CHECK_ALL_TYPES( not is_fmt_type, none_type );
}

BOOST_AUTO_TEST_CASE(is_ext_fmt_test)
{
    CHECK_ALL_TYPES( is_ext_fmt_type, bool );
    CHECK_ALL_TYPES( is_ext_fmt_type, char );
    CHECK_ALL_TYPES( is_ext_fmt_type, short );
    CHECK_ALL_TYPES( is_ext_fmt_type, unsigned short );
    CHECK_ALL_TYPES( is_ext_fmt_type, int );
    CHECK_ALL_TYPES( is_ext_fmt_type, unsigned int );
    CHECK_ALL_TYPES( is_ext_fmt_type, long );
    CHECK_ALL_TYPES( is_ext_fmt_type, unsigned long );
    CHECK_ALL_TYPES( is_ext_fmt_type, long long );
    CHECK_ALL_TYPES( is_ext_fmt_type, unsigned long long );
    CHECK_ALL_TYPES( is_ext_fmt_type, float );
    CHECK_ALL_TYPES( is_ext_fmt_type, double );
    CHECK_ALL_TYPES( is_ext_fmt_type, long double );
    CHECK_ALL_PTR_TYPES( is_ext_fmt_type, char );
    CHECK_ALL_PTR_TYPES( is_ext_fmt_type, void );
    
    CHECK_ALL_TYPES( is_ext_fmt_type, std::string );
    
    CHECK_ALL_TYPES( is_ext_fmt_type, implicit_type );
    CHECK_ALL_TYPES( is_ext_fmt_type, explicit_type );
    CHECK_ALL_TYPES( is_ext_fmt_type, stream_type );
    CHECK_ALL_TYPES( is_ext_fmt_type, to_string_type );
    CHECK_ALL_TYPES( not is_ext_fmt_type, none_type );
    
    BOOST_CHECK( not is_ext_fmt_type<void>() );
}


template <class T, class U>
using check_convert_is = 
    aux::is_same<
        decltype( fmt_detail::convert_arg(elib::declval<T>()) )
      , U
      >;

#define CHECK_CONVERT(T, U) BOOST_CHECK(( check_convert_is<T, U>() ))
#define CHECK_NON_CONVERT_ALL_TYPES(T) \
    CHECK_CONVERT(T, T &&);               \
    CHECK_CONVERT(T const, T const &&);   \
    CHECK_CONVERT(T &, T &);              \
    CHECK_CONVERT(T &&, T &&);            \
    CHECK_CONVERT(T const &, T const &);  \
    CHECK_CONVERT(T const &&, T const &&)
#

#define CHECK_CONVERT_ALL_TYPES(T)         \
    CHECK_CONVERT(T, std::string);         \
    CHECK_CONVERT(T const, std::string);   \
    CHECK_CONVERT(T &, std::string);       \
    CHECK_CONVERT(T &&, std::string);      \
    CHECK_CONVERT(T const &, std::string); \
    CHECK_CONVERT(T const &&, std::string)
#

BOOST_AUTO_TEST_CASE(convert_arg_test)
{
    CHECK_NON_CONVERT_ALL_TYPES(bool);
    CHECK_NON_CONVERT_ALL_TYPES(char);
    CHECK_NON_CONVERT_ALL_TYPES(int);
    CHECK_NON_CONVERT_ALL_TYPES(float);
    CHECK_NON_CONVERT_ALL_TYPES(double);
    CHECK_NON_CONVERT_ALL_TYPES(void*);
    CHECK_NON_CONVERT_ALL_TYPES(char*);
    CHECK_NON_CONVERT_ALL_TYPES(std::string);
    
    CHECK_CONVERT_ALL_TYPES(explicit_type);
    CHECK_CONVERT_ALL_TYPES(stream_type);
    CHECK_CONVERT_ALL_TYPES(to_string_type);
}
#undef CHECK_CONVERT
#undef CHECK_CONVERT_ALL_TYPES
#undef CHECK_NON_CONVERT_ALL_TYPES

template <class T, class U>
using check_normalize_is =
    aux::is_same<
        decltype( fmt_detail::normalize_arg(elib::declval<T>()) )
      , U
      >;

#define CHECK_NORMALIZE(...) BOOST_CHECK(( check_normalize_is<__VA_ARGS__>() ))
BOOST_AUTO_TEST_CASE(normalize_arg_test)
{
    CHECK_NORMALIZE(bool, long);
    CHECK_NORMALIZE(char, long);
    CHECK_NORMALIZE(unsigned char, long);
    CHECK_NORMALIZE(signed char, long);
    CHECK_NORMALIZE(short, long);
    CHECK_NORMALIZE(unsigned short, long);
    CHECK_NORMALIZE(int, long);
    CHECK_NORMALIZE(unsigned, long);
    CHECK_NORMALIZE(long, long);
    CHECK_NORMALIZE(unsigned long, long);
    
    CHECK_NORMALIZE(float, double);
    CHECK_NORMALIZE(double, double);
    
    CHECK_NORMALIZE(void*, void*);
    CHECK_NORMALIZE(const char*, const char*);
    
    CHECK_NORMALIZE(std::string, const char*);
    CHECK_NORMALIZE(std::string const, const char*);
    CHECK_NORMALIZE(std::string &, const char*);
    CHECK_NORMALIZE(std::string &&, const char*);
    CHECK_NORMALIZE(std::string const &, const char*);
    CHECK_NORMALIZE(std::string const &&, const char*);
    
    CHECK_NORMALIZE(std::string*, std::string*);
}

#define CHECK_SPEC(...) \
    BOOST_CHECK_NO_THROW(( check_fmt(__VA_ARGS__) ))
    
#define CHECK_THROW(...) \
    BOOST_CHECK_THROW( (check_fmt(__VA_ARGS__)), std::logic_error )

BOOST_AUTO_TEST_CASE(check_fmt_literal_specifier_test)
{
    CHECK_SPEC("%%");
    CHECK_SPEC("%%%%");
    CHECK_SPEC("%% %% %%%% ");
    
    CHECK_THROW("%");
    CHECK_THROW("% %");
    CHECK_THROW("%%", long());
    CHECK_THROW("%%", double());
    CHECK_THROW("%%", (const char*)nullptr);
    CHECK_THROW("%%", (void*)nullptr);
    CHECK_THROW("%%", (none_type*)nullptr);
}
    
BOOST_AUTO_TEST_CASE(check_fmt_integral_test)
{
    CHECK_SPEC("%d", long());
    CHECK_SPEC("%i", long());
    CHECK_SPEC("%u", long());
    CHECK_SPEC("%o", long());
    CHECK_SPEC("%x", long());
    CHECK_SPEC("%X", long());
    CHECK_SPEC("%c", long());
    
    CHECK_THROW("%d", float());
    CHECK_THROW("%i", double());
    CHECK_THROW("%u", (const char*)nullptr);
    CHECK_THROW("%o", (void*)nullptr);
    CHECK_THROW("%x", (long*)nullptr);
    CHECK_THROW("%X", (none_type*)nullptr);
}

BOOST_AUTO_TEST_CASE(check_fmt_float_test)
{
    CHECK_SPEC("%f", double());
    CHECK_SPEC("%F", double());
    CHECK_SPEC("%e", double());
    CHECK_SPEC("%E", double());
    CHECK_SPEC("%g", double());
    CHECK_SPEC("%G", double());
    CHECK_SPEC("%a", double());
    CHECK_SPEC("%A", double());
    
    CHECK_THROW("%f", long());
    CHECK_THROW("%F", (const char*)nullptr);
    CHECK_THROW("%e", (void*)nullptr);
    CHECK_THROW("%E", (long*)nullptr);
    CHECK_THROW("%g", (none_type*)nullptr);
}

BOOST_AUTO_TEST_CASE(check_fmt_string_test)
{
    const char* s1 = "hello";
    const char* const s2 = "hello";
    char s3[10];
    char s4[] = "hello";
    
    CHECK_SPEC("%s", s1);
    CHECK_SPEC("%s", s2);
    CHECK_SPEC("%s", s3);
    CHECK_SPEC("%s", s4);
    
    CHECK_THROW("%s", long());
    CHECK_THROW("%s", double());
    CHECK_THROW("%s", (void*)nullptr);
    CHECK_THROW("%s", (long*)nullptr);
    CHECK_THROW("%s", (none_type*)nullptr);
}

BOOST_AUTO_TEST_CASE(check_fmt_pointer_test)
{
    CHECK_SPEC("%p", (void*)nullptr);
    CHECK_SPEC("%p", (const char*)nullptr);
    CHECK_SPEC("%p", (long*)nullptr);
    CHECK_SPEC("%p", (none_type*)nullptr);
    
    CHECK_THROW("%p", long());
    CHECK_THROW("%p", double());
}
    
BOOST_AUTO_TEST_CASE(check_fmt_count_test)
{
    CHECK_SPEC("%n", (int*)nullptr);
    CHECK_SPEC("%n", (unsigned*)nullptr);
    CHECK_SPEC("%n", (long*)nullptr);
    CHECK_SPEC("%n", (unsigned long*)nullptr);
    
    CHECK_THROW("%n", long());
    CHECK_THROW("%n", double());
    CHECK_THROW("%n", (void*)nullptr);
    CHECK_THROW("%n", (none_type*)nullptr);
}

BOOST_AUTO_TEST_CASE(check_fmt_arg_count_mismatch)
{
    const char *s = "hello";
    long i = 0;
    
    CHECK_THROW("%s");
    CHECK_THROW("%i");
    CHECK_THROW("%f");
    CHECK_THROW("%p");
    CHECK_THROW("%n");
    
    CHECK_THROW("%% %s %i", s);
    CHECK_THROW("%s %s", s);
    CHECK_THROW("%i %f", i);
    CHECK_THROW("%i %n", i);
    
    CHECK_THROW("", s);
    CHECK_THROW("%%", i);
    CHECK_THROW("%s", s, s);
    CHECK_THROW("%i %% %i", i, i, i);
}


BOOST_AUTO_TEST_CASE( check_fmt_general_test )
{
    const char *s = "hello";
    long i = 0;
    double f = 0.0;
    void *p = nullptr;
    int *n = nullptr;
    
    CHECK_SPEC("%s %i %f %p %n", s, i, f, p, n);
    CHECK_SPEC("%s%s%s%s", s, s, s, s);
    CHECK_SPEC("%% %s %% %i %% %f %% %p %% %n", s, i, f, p, n);
}

#undef CHECK_SPEC
#undef CHECK_THROW



#define CHECK_FMT(...)                                             \
    do {                                                           \
        std::string m_str__;                                       \
        char m_buff__[10024];                                      \
        BOOST_REQUIRE_NO_THROW(( m_str__ = FMT_FN(__VA_ARGS__) )); \
        std::snprintf(m_buff__, sizeof(m_buff__), __VA_ARGS__);    \
        BOOST_CHECK(m_buff__ == m_str__);                          \
    } while (false)
    
#define CHECK_THROW(...) \
    BOOST_CHECK_THROW( (FMT_FN(__VA_ARGS__)), std::logic_error )

BOOST_AUTO_TEST_CASE( check_cfmt_throw_test )
{
#define FMT_FN elib::checked_cfmt
  {
    CHECK_FMT("");
    
    CHECK_FMT("%%");
    
    CHECK_FMT("%d", 0);
    CHECK_FMT("%i", -100);
    CHECK_FMT("%u", 100);
    CHECK_FMT("%o", 9);
    CHECK_FMT("%x", 56);
    CHECK_FMT("%X", 75);
    CHECK_FMT("%c", 'a');
    
    CHECK_FMT("%f", 0.0);
    CHECK_FMT("%F", -1.0);
    CHECK_FMT("%e", 1.0);
    CHECK_FMT("%E", -1.23);
    CHECK_FMT("%g", 10.001);
    CHECK_FMT("%G", 111.1);
    CHECK_FMT("%a", 50.5);
    CHECK_FMT("%A", -110.531);
    
    CHECK_FMT("%s", "Hello World!\n");
    
    CHECK_FMT("%p", (void*)nullptr);
    
    char buff[10024];
    std::string str;
    int n1 = -1;
    int n2 = -1;
    
    BOOST_CHECK_NO_THROW((str = FMT_FN("%s %i %n %p", "Hello", 0, &n1, (void*)nullptr) ));
    std::snprintf(buff, sizeof(buff), "%s %i %n %p", "Hello", 0, &n2, (void*)nullptr);
    
    BOOST_CHECK(buff == str);
    BOOST_CHECK(n1 != -1);
    BOOST_CHECK(n1 == n2);
  }
#undef FMT_FN
#define FMT_FN elib::checked_fmt
  {
    CHECK_FMT("");
    
    CHECK_FMT("%%");
    
    CHECK_FMT("%d", 0);
    CHECK_FMT("%i", -100);
    CHECK_FMT("%u", 100);
    CHECK_FMT("%o", 9);
    CHECK_FMT("%x", 56);
    CHECK_FMT("%X", 75);
    CHECK_FMT("%c", 'a');
    
    CHECK_FMT("%f", 0.0);
    CHECK_FMT("%F", -1.0);
    CHECK_FMT("%e", 1.0);
    CHECK_FMT("%E", -1.23);
    CHECK_FMT("%g", 10.001);
    CHECK_FMT("%G", 111.1);
    CHECK_FMT("%a", 50.5);
    CHECK_FMT("%A", -110.531);
    
    CHECK_FMT("%s", "Hello World!\n");
    
    CHECK_FMT("%p", (void*)nullptr);
    
    char buff[10024];
    std::string str;
    int n1 = -1;
    int n2 = -1;
    
    BOOST_CHECK_NO_THROW((str = FMT_FN("%s %i %n %p", "Hello", 0, &n1, (void*)nullptr) ));
    std::snprintf(buff, sizeof(buff), "%s %i %n %p", "Hello", 0, &n2, (void*)nullptr);
    
    BOOST_CHECK(buff == str);
    BOOST_CHECK(n1 != -1);
    BOOST_CHECK(n1 == n2);
    
    BOOST_CHECK_NO_THROW(str = FMT_FN("%s", std::string("Hello")));
    std::snprintf(buff, sizeof(buff), "%s", "Hello");
    BOOST_CHECK(str == buff);
  }
#undef FMT_FN
#define FMT_FN elib::checked_ext_fmt
  {
    CHECK_FMT("");
    
    CHECK_FMT("%%");
    
    CHECK_FMT("%d", 0);
    CHECK_FMT("%i", -100);
    CHECK_FMT("%u", 100);
    CHECK_FMT("%o", 9);
    CHECK_FMT("%x", 56);
    CHECK_FMT("%X", 75);
    CHECK_FMT("%c", 'a');
    
    CHECK_FMT("%f", 0.0);
    CHECK_FMT("%F", -1.0);
    CHECK_FMT("%e", 1.0);
    CHECK_FMT("%E", -1.23);
    CHECK_FMT("%g", 10.001);
    CHECK_FMT("%G", 111.1);
    CHECK_FMT("%a", 50.5);
    CHECK_FMT("%A", -110.531);
    
    CHECK_FMT("%s", "Hello World!\n");
    
    CHECK_FMT("%p", (void*)nullptr);
    
    char buff[10024];
    std::string str;
    int n1 = -1;
    int n2 = -1;
    
    BOOST_CHECK_NO_THROW((str = FMT_FN("%s %i %n %p", "Hello", 0, &n1, (void*)nullptr) ));
    std::snprintf(buff, sizeof(buff), "%s %i %n %p", "Hello", 0, &n2, (void*)nullptr);
    
    BOOST_CHECK(buff == str);
    BOOST_CHECK(n1 != -1);
    BOOST_CHECK(n1 == n2);
    
    BOOST_CHECK_NO_THROW(str = FMT_FN("%s", std::string("Hello")));
    std::snprintf(buff, sizeof(buff), "%s", "Hello");
    BOOST_CHECK(str == buff);
  }
#undef FMT_FN
}


BOOST_AUTO_TEST_CASE(ext_fmt_test)
{
    std::string dest;
    char buff[10024];
    
    std::string s1 = "S1";
    implicit_type s2("S2");
    explicit_type s3("S3");
    stream_type s4("S4");
    to_string_type s5("S5");
    
    BOOST_CHECK_NO_THROW(( 
       dest = elib::checked_ext_fmt("%s %s %s %s %s", s1, s2, s3, s4, s5) 
    ));
    
    std::snprintf(buff, sizeof(buff), "%s %s %s %s %s", "S1", "S2", "S3", "S4", "S5");
    
    BOOST_CHECK(buff == dest);
}
BOOST_AUTO_TEST_SUITE_END()