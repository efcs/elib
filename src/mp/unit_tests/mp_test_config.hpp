#ifndef ELIB_MP_MP_TEST_CONFIG_HPP
#define ELIB_MP_MP_TEST_CONFIG_HPP

// needed for the macros & std::integral_constant
# include <type_traits>
# include <limits>

# include <elib/mp/config.hpp>

// include args so we get elib::mp and mp::placeholders
# include <elib/mp/metafunctions/arg.hpp>

namespace e
{
  using namespace elib::mp;
  using namespace elib::mp::placeholders;
}

# if ELIB_MP_BOOST_MPL_TESTS
#   include <boost/mpl/placeholders.hpp>

  namespace b
  {
    using namespace boost::mpl;
    using namespace boost::mpl::placeholders;
  }
  
/* This is a hack to conditionally compile the boost unit tests.
 * Not sure if this is legal C++, but it works in both GCC 4.8 and Clang 3.4.
 * Usage:
 *  OPT_BOOST(
 *    statement 1;
 *    statement 2;
 *    ...
 *    statement n;
 *  )
 * WARNING: Template barf as processed through the preprocessor is UGLY */
#   define OPT_BOOST(...) __VA_ARGS__

# else
#   define OPT_BOOST(...) 
# endif                                              // ELIB_MP_BOOST_MPL_TESTS

//-------------------------------- helper macros ----------------------------// 



#define SAME_TYPE(lhs, rhs) \
  BOOST_CHECK((std::is_same<lhs, rhs>::value))
  
#define NOT_SAME_TYPE(lhs, rhs) \
  BOOST_CHECK((!std::is_same<lhs, rhs>::value))
  
#define SAME_VALUE(lhs, rhs) \
  BOOST_CHECK( lhs::value == rhs::value )
  
#define CHECK_VALUE(lhs, val) \
  BOOST_CHECK(lhs::value == val)
  
# define SAME_INTC(lhs, rhs)                                     \
do {                                                             \
  SAME_TYPE(typename lhs::value_type, typename rhs::value_type); \
  SAME_VALUE(lhs, rhs);                                          \
} while (false)
  
# define CHECK_INTC(c, val_t, val)          \
do {                                        \
  SAME_TYPE(typename c::value_type, val_t); \
  CHECK_VALUE(c, val);                      \
} while (false)

# define GOOD_TYPE(t) SAME_TYPE(t, good)

//-------------------------------- helper types -----------------------------// 


/* boost does not play nice with std::integral_constant so we only use it
 * if we are not testing against boost. 
 * also, boost::mpl::integral_c poops itself at numeric limits, 
 * so min_x_ and max_x_ must be std::integral_constant
 */
# if ELIB_MP_BOOST_MPL_TESTS
#   include <boost/mpl/integral_c.hpp>
  template <class T, T Val> 
  using integral_constant = ::boost::mpl::integral_c<T, Val>;
# else
  template <class T, T Val>
  using integral_constant = std::integral_constant<T, Val>;
# endif

template <class T, T Val>
using intc_ = integral_constant<T, Val>;

template <bool N>
using bool_ = integral_constant<bool, N>;

using true_ = bool_<true>;
using false_ = bool_<false>;

template <char N>
using char_ = integral_constant<char, N>;

using max_char_ = std::integral_constant<char, std::numeric_limits<char>::max()>;
using min_char_ = std::integral_constant<char, std::numeric_limits<char>::min()>;
  

template <int N>
using int_ = integral_constant<int, N>;

using max_int_ = std::integral_constant<int, std::numeric_limits<int>::max()>;
using min_int_ = std::integral_constant<int, std::numeric_limits<int>::min()>;
  

template <unsigned N>
using uint_ = integral_constant<unsigned, N>;

using max_uint_ = std::integral_constant<unsigned, std::numeric_limits<unsigned>::max()>;
using min_uint_ = std::integral_constant<unsigned, std::numeric_limits<unsigned>::min()>;
  

template <long N>
using long_ = integral_constant<long, N>;

using max_long_ = std::integral_constant<long, std::numeric_limits<long>::max()>;
using min_long_ = std::integral_constant<long, std::numeric_limits<long>::min()>;
  
// good & bad types that are separate from integral_constant

struct good
{
  using type = good;
  using value_type = bool;
  static constexpr value_type value = true;
};

struct bad
{
  using type = bad;
  using value_type = bool;
  static constexpr value_type value = false;
};

//-------------------------------- helper intc macros------------------------// 

# define INTC(x) integral_constant<decltype(x), (x)>
# define BOOL(x)  bool_<x>
# define CHAR(x)  char_<x>
# define INT(x)   int_<x>
# define UINT(x)  uint_<x>
# define LONG(x)  long_<x>

////////////////////////////////////////////////////////////////////////////////
//                          Sample input types                                                
////////////////////////////////////////////////////////////////////////////////

// _f -> metafunction 
// _mfc -> metafunction class
 
//-------------------------------- void --------------------------------------// 
// non-templated metafunction (class)

struct void_f
{
  typedef void type;
};


struct void_mfc
{
  struct apply
  {
    typedef void type;
  };
};

//-------------------------------- identity --------------------------------// 
// unary metafunction,  standard typedef style

template <class T>
struct identity_f
{ typedef T type; };

  
struct identity_mfc
{
  template <class T>
  struct apply
  { typedef T type; };
};

//-------------------------------- first --------------------------------// 
// binary metafunction, returns First.

template <class First, class Second>
struct first_f
{ typedef First type; };


// using matching metafunction
struct first_mfc
{
  template <class First, class Second>
  struct apply 
  {
    typedef typename first_f<First, Second>::type type;
  };
};

//-------------------------------- second --------------------------------// 

template <class, class Second>
struct second_f
{
  using type = Second;
};


struct second_mfc
{
  template <class First, class Second>
  struct apply : second_f<First, Second>
  {};
};

//---------------------------- third -----------------------------------------//

template<class, class, class Third>
struct third_f
{
  using type = Third;
};

struct third_mfc
{
  template <class, class, class Third>
  struct apply
  {
    using type = Third;
  };
};

//-------------------------------- add ---------------------------------------// 
// Binary metafunction. Takes integral_constant types. 
// Performs arithmetic addition

template <class First, class Second>
struct add_f
{
  using type = 
  integral_constant<
    decltype(First::value + Second::value)
    , First::value + Second::value
  >; 
};

// Use inheritince to supply apply
struct add_mfc
{
  template <class First, class Second>
  struct apply 
    : add_f<First, Second>
  {};
};

//------------------------------- nested/non-nested ::type -------------------//

template <class, class, class Three>
struct nested_type
{
  using type = Three;
};

template <class, class, class Three>
struct non_nested_type
{};


#endif /* ELIB_MP_MP_TEST_CONFIG_HPP */