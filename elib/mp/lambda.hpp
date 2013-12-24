#ifndef ELIB_MP_LAMBDA_HPP
#define ELIB_MP_LAMBDA_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/bind.hpp>
# include <elib/mp/arg.hpp>
# include <elib/mp/protect.hpp>
# include <elib/mp/quote.hpp>
# include <elib/mp/logical.hpp>

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
      
      template <bool isPHE, template <class...> class F, class ...Args>
      struct make_lambda;
      
      template <template <class...> class F, class ...Args>
      struct make_lambda<false, F, Args...>
      {
        using raw_type_ = F<typename Args::type...>;
        using type = raw_type_;
      };
      
      
      template <template <class...> class F, class ...Args>
      struct make_lambda<true, F, Args...>
      {
        using raw_type_ = 
          bind< quote<F>, typename Args::raw_type_...>;
        
        using type = protect<raw_type_>;
      };
      
      
    }                                                       // namespace detail
   
    //-------------------------------- lambda -------------------------------// 
    
    // base case
    template <class T>
    struct lambda
    {
      using is_le_ = false_;
      using raw_type_ = T;
      using type = raw_type_;
    };
    
    // special cases
    
    template <std::size_t N>
    struct lambda< arg<N> >
    {
      using is_le_ = true_;
      using raw_type_ = arg<N>;
      using type = raw_type_;
    };
    
    
    template <class F, class ...Args>
    struct lambda< bind<F, Args...> >
    {
      using is_le_ = false_;
      using raw_type_ = bind<F, Args...>;
      using type = raw_type_;
    };
    
    
    template <class T>
    struct lambda< protect<T> >
    {
      using is_le_ = false_;
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
      using is_le_ =  detail::lambda_or<typename lambda<Args>::is_le_...>;
      
      using lambda_result_ = 
        detail::make_lambda<
          is_le_::value
          , F
          , lambda<Args>...
        >;
        
      using raw_type_ = typename lambda_result_::raw_type_;
      using type = typename lambda_result_::type;
    };
    
    
    template <class T>
    using lambda_t = typename lambda<T>::type;
    
    
    template <class T>
    using is_lambda_expression = typename lambda<T>::is_le_;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LAMBDA_HPP */