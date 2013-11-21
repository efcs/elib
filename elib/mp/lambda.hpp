#ifndef ELIB_MP_LAMBDA_HPP
# define ELIB_MP_LAMBDA_HPP

# include <elib/mp/config.hpp>
# include <elib/mp/types.hpp>
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
    
    namespace detail
    {
      
      template <
        class IsPHE
        , template <class...> class F
        , class ...Args
      >
      struct make_lambda
      {
        using raw_type_ = F<typename Args::type...>;
        using type = raw_type_;
      };
      
      
      template < 
        template <class...> class F
        , class ...Args
      >
      struct make_lambda<true_, F, Args...>
      {
        using raw_type_ = 
          bind<
            quote<F>
            , typename Args::raw_type_...
          >;
        
        using type = protect<raw_type_>;
      };
      
      
    }                                                       // namespace detail
    
    
    template <class T>
    struct lambda
    {
      using is_phe_ = false_;
      using raw_type_ = T;
      using type = raw_type_;
    };
    
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
    
    template <template <class...> class F, class ...Args>
    struct lambda< F<Args...> >
    {
      using is_phe_ = or_<typename lambda<Args>::is_phe_...>;
      using lambda_result_ = 
        detail::make_lambda<
          is_phe_
          , F
          , lambda<Args>...
        >;
        
      using raw_type_ = typename lambda_result_::raw_type_;
      using type = typename lambda_result_::type;
    };
    
    
    template <class T>
    using lambda_t = typename lambda<T>::type;
    
    
    template <class T>
    struct is_placeholder_expression
      : lambda<T>::is_phe_
    {};
    
    // For boost compadibility
    template <class T>
    struct is_lambda_expression
      : lambda<T>::is_phe_
    {};
    
    
    
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_LAMBDA_HPP */