#ifndef ELIB_MP_METAFUNCTION_LAMBDA_HPP
#define ELIB_MP_METAFUNCTION_LAMBDA_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>
# include <elib/mp/metafunction/bind.hpp>
# include <elib/mp/metafunction/arg.hpp>
# include <elib/mp/metafunction/protect.hpp>
# include <elib/mp/metafunction/quote.hpp>
# include <elib/mp/metafunction/logical.hpp>

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class> struct lambda;
    
    namespace detail
    {
      /* mp::or_ only accepts 2 or more params,
       * lambda needs 0 or more and false on 0.
       * detail::or_impl provides this. */
      template <class ...Args>
      using lambda_or = detail::or_impl<false, Args...>;
      
      //-------------------------------- make_lambda ------------------------// 
      
      template <
        bool IsPHE
        , template <class...> class F
        , class ...Args
      >
      struct make_lambda
      {
        using raw_type_ = F<typename Args::type...>;
        using type = raw_type_;
        
        // Implementation check: this overload should only
        // be selected when isPHE is false
        static_assert(IsPHE == false,
          "Incorrect overload selected for make_lambda");
      };
      
      
      template < 
        template <class...> class F
        , class ...Args
      >
      struct make_lambda<true, F, Args...>
      {
        using raw_type_ = 
          bind< 
            quote<F>
            , typename Args::raw_type_...
          >;
        
        using type = protect<raw_type_>;
      };
      
      
    }                                                       // namespace detail
   
    //-------------------------------- lambda -------------------------------// 
    
    // base case
    template <class T>
    struct lambda
    {
      using is_phe_ = false_;
      using raw_type_ = T;
      using type = raw_type_;
    };
    
    // special cases
    
    template <std::size_t N>
    struct lambda< arg<N> >
    {
      using is_phe_ = true_;
      using raw_type_ = arg<N>;
      using type = raw_type_;
    };
    
    
    template <class F, class ...Args>
    struct lambda< bind<F, Args...> >
    {
      using is_phe_ = false_;
      using raw_type_ = bind<F, Args...>;
      using type = raw_type_;
    };
    
    
    template <class T>
    struct lambda< protect<T> >
    {
      using is_phe_ = false_;
      using raw_type_ = protect<T>;
      using type = raw_type_;
    };
    
    
    // recursive case
    
    template <
      template <class...> class F
      , class ...Args
    >
    struct lambda< F<Args...> >
    {
      // detail::or_impl is used since it accepts 0 or more parameters.
      // mp::or_ requires at least 2
      using is_phe_ =  detail::lambda_or<typename lambda<Args>::is_phe_...>;
      
      using lambda_result_ = 
        detail::make_lambda<
          is_phe_::value
          , F
          , lambda<Args>...
        >;
        
      using raw_type_ = typename lambda_result_::raw_type_;
      using type = typename lambda_result_::type;
    };
    
    
    template <class T>
    using lambda_t = typename lambda<T>::type;
    
    
    template <class T>
    using is_placeholder_expression = typename lambda<T>::is_phe_;
    
    
# if ELIB_MP_BOOST_COMPATIBLE_NAMES    
    template <class T>
    using is_lambda_expression = is_placeholder_expression<T>;
# endif
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_LAMBDA_HPP */