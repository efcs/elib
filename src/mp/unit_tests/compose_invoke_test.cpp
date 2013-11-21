/* 
 * Test elib::mp against boost::mpl
 *
 * For the most part, these tests are nothing more
 * than running simple input against both elib and boost
 * 
 * Testing against boost may be poor style, 
 * but it is an easy way to catch obvious errors.
 * 
 * More complete testing is done in the
 * standalone versions of these tests
 */
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <elib/config.hpp>
#include <elib/mp/types.hpp>
#include <elib/mp/compose.hpp>
#include <elib/mp/invoke.hpp>
#include <elib/mp/detail/is_placeholder.hpp>


//TODO move this definition to the build system
#define ELIB_MP_BOOST_MPL_TESTS 1

#if ELIB_MP_BOOST_MPL_TESTS
  //invoke
# include <boost/mpl/apply.hpp>
# include <boost/mpl/apply_wrap.hpp>
# include <boost/mpl/unpack_args.hpp> 
  // composition & arguments
# include <boost/mpl/placeholders.hpp>
# include <boost/mpl/lambda.hpp>
# include <boost/mpl/bind.hpp>
# include <boost/mpl/quote.hpp>
# include <boost/mpl/arg.hpp>
# include <boost/mpl/protect.hpp>
# endif                                              // ELIB_MP_BOOST_MPL_TESTS

#include <type_traits>
#include <iostream>


// All elib::mp functions should be accessed through
// this namespace 
namespace e
{
  using namespace elib::mp;
  using namespace elib::mp::placeholders;
}


# if ELIB_MP_BOOST_MPL_TESTS

  namespace b
  {
    using namespace boost::mpl;
    using namespace boost::mpl::placeholders;
  }
  
#   define OPT_BOOST(...) __VA_ARGS__

# else                                               
#   define OPT_BOOST(...) 
# endif                                              // ELIB_MP_BOOST_MPL_TESTS


//--------------------------- test helper macros ----------------------------// 

#define SAME_TYPE(lhs, rhs) \
  BOOST_CHECK((std::is_same<lhs, rhs>::value))
  
#define CHECK_SAME_VALUE(lhs, rhs) \
  BOOST_CHECK( lhs::value == rhs::value )
  
#define CHECK_VALUE(lhs, val) \
  BOOST_CHECK(lhs::value == val)

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

//-------------------------------- add ---------------------------------------// 
// Binary metafunction. Takes integral_constant types. 
// Performs arithmetic addition

template <class First, class Second>
struct add_f
{
  using type = 
  std::integral_constant<
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

//-------------------------------- misc types --------------------------------// 

using true_t = std::true_type;
using false_t = std::false_type;

using zero_t = std::integral_constant<int, 0>;
using one_t = std::integral_constant<int, 1>;
using two_t = std::integral_constant<int, 2>;

////////////////////////////////////////////////////////////////////////////////
//                            Test Cases                                          
////////////////////////////////////////////////////////////////////////////////

/* 
 * apply_wrap goes first, since it has no other dependancies.
 * The general order is
 * 
 * - apply_wrap
 * ---- Composition & Args -----
 * - args / placeholders
 * - bind
 * - quote
 * - protect
 * - lambda (depends on all above)
 * ---- Invocation ------
 * - apply (depends on lambda)
 * 
 */
BOOST_AUTO_TEST_SUITE(mp_compose_invoke_test_suite)

//-------------------------------- apply_wrap -------------------------------// 

  BOOST_AUTO_TEST_CASE(apply_wrap_test)
  {
    // Check that these incorrect cases still compile.
    // Only when Type::type is accessed should the compile fail
    { 
      using E1 = e::apply_wrap<void_f>;
      using E2 = e::apply_wrap<identity_f<void>>;
      OPT_BOOST(
        using B1 = b::apply_wrap0<void_f>;
        using B2 = b::apply_wrap0<identity_f<void>>;
        using B3 = b::apply_wrap2<first_f<false_t, true_t>, void, void>;
        )
    }
    { 
      using E = typename e::apply_wrap<void_mfc>::type;
      SAME_TYPE(E, void);
      OPT_BOOST(
        using B = typename b::apply_wrap0<void_mfc>::type;
        SAME_TYPE(B, E);
        )
    }
    {
      using E = e::apply_wrap_t<identity_mfc, true_t>;
      SAME_TYPE(E, true_t);
      OPT_BOOST(
        using B = typename b::apply_wrap1<identity_mfc, true_t>::type;
        SAME_TYPE(B, E);
        )
    }
    {
      using E = e::apply_wrap_t<first_mfc, true_t, false_t>;
      SAME_TYPE(E, true_t);
      OPT_BOOST(
        using B = typename b::apply_wrap2<first_mfc, true_t, false_t>::type;
        SAME_TYPE(B, E);
        )
    }
    {
      using E = e::apply_wrap_t<add_mfc, zero_t, one_t>;
      CHECK_VALUE(E, 1);
      OPT_BOOST(
        using B = typename b::apply_wrap2<add_mfc, zero_t, one_t>::type;
        SAME_TYPE(B, E);
        )
    }
  }                                                         // apply_wrap_test
    
  //-------------------------------- arg test --------------------------------// 
  
  BOOST_AUTO_TEST_CASE(arg_test)
  {
    {
      using T1 = e::arg<1>::template apply<true_t>::type;
      SAME_TYPE(T1, true_t);
      
      using T2 = e::arg<1>::template apply<true_t, false_t, false_t>::type;
      SAME_TYPE(T2, true_t);
      
      using T3 = e::arg<2>::template apply<false_t, true_t>::type;
      SAME_TYPE(T3, true_t);
      
      using T4 = e::arg<2>::template apply<false_t, true_t, false_t>::type;
      SAME_TYPE(T4, true_t);
      
      using T1 = e::_1::template apply<true_t>::type;
      SAME_TYPE(T1, true_t);
      
      using T2 = e::_1::template apply<true_t, false_t, false_t>::type;
      SAME_TYPE(T2, true_t);
      
      using T3 = e::_2::template apply<false_t, true_t>::type;
      SAME_TYPE(T3, true_t);
      
      using T4 = e::_2::template apply<false_t, true_t, false_t>::type;
      SAME_TYPE(T4, true_t);
    }
    {
      using E = e::apply_wrap_t<e::arg<1>, true_t, false_t>;
      SAME_TYPE(E, true_t);
      OPT_BOOST(
        using B = typename b::apply_wrap2<b::arg<1>, true_t, false_t>::type;
        SAME_TYPE(B, E);
        )
    }
    {
      using E = e::apply_wrap_t<e::_2, false_t, true_t, false_t>;
      SAME_TYPE(E, true_t);
      OPT_BOOST(
        using B = typename b::apply_wrap3<b::_2, false_t, true_t, false_t>::type;
        SAME_TYPE(B, E);
        )
    }
    // is_placeholder
    {
      BOOST_CHECK(e::is_placeholder<e::_1>::value);
      BOOST_CHECK(e::is_placeholder<e::_9>::value);
      BOOST_CHECK(e::is_placeholder<void>::value == false);
      BOOST_CHECK(e::is_placeholder<int>::value == false);
    }
  }                                                     // arg_test
  
  //-------------------------------- bind --------------------------------// 
  
  BOOST_AUTO_TEST_CASE(bind_test)
  {
    {
      using E = e::apply_wrap_t<e::quote<identity_f>, true_t>;
      SAME_TYPE(E, true_t);
      OPT_BOOST(
        using B = typename b::apply_wrap1<b::quote1<identity_f>, true_t>::type;
        SAME_TYPE(B, E);
        )
    }
    {
      using E = e::apply_wrap_t<e::quote<first_f>, true_t, false_t>;
      SAME_TYPE(E, true_t);
      OPT_BOOST(
        using B = 
          typename b::apply_wrap2<b::quote2<first_f>, true_t, false_t>::type;
        SAME_TYPE(B, E);
        )
    }
    //TODO test nested vs non-nested ::type
  }                                                         // bind_test

  //-------------------------------- quote --------------------------------// 
  
  //TODO
  BOOST_AUTO_TEST_CASE(quote_test)
  {
    BOOST_CHECK(true);
  }                                                         // quote_test
  
  //-------------------------------- protect --------------------------------// 
  
  //TODO
  BOOST_AUTO_TEST_CASE(protect_test)
  {
    BOOST_CHECK(true);
  }                                                         // protect_test
  
  //-------------------------------- lambda --------------------------------// 
  
  //TODO
  BOOST_AUTO_TEST_CASE(lambda_test)
  {
    BOOST_CHECK(true);
  }                                                         // lambda_test
  
  //-------------------------------- apply --------------------------------// 

  //TODO
  BOOST_AUTO_TEST_CASE(apply_test)
  {
    BOOST_CHECK(true);
  }                                                         // apply_test

BOOST_AUTO_TEST_SUITE_END()