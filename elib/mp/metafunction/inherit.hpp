#ifndef ELIB_MP_METAFUNCTION_INHERIT_HPP
#define ELIB_MP_METAFUNCTION_INHERIT_HPP

# include <elib/mp/types/empty_base.hpp>

namespace elib 
{
  namespace mp
  {
   
  //-------------------------------- inherit2 --------------------------------// 
    
    template <class T1, class T2>
    struct inherit2 : T1, T2
    {
      using type = inherit2;
    };
    
    template <class T1>
    struct inherit2<T1, empty_base>
    {
      using type = T1;
    };
    
    template <class T2>
    struct inherit2<empty_base, T2>
    {
      using type = T2;
    };
    
    template <>
    struct inherit2<empty_base, empty_base>
    {
      using type = empty_base;
    };
    
    template <class T1, class T2>
    using inherit2_t = typename inherit2<T1, T2>::type;
  
  //////////////////////////////////////////////////////////////////////////////
  //                            Inherit                                              
  //////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
      
    //-------------------------------- inherit_impl -------------------------// 
      template <class ...Args>
      struct inherit_impl
      {
        using type = empty_base;
        
        static_assert(sizeof...(Args) == 0, "Overload resolution check");
      };
      
      template <class B1>
      struct inherit_impl<B1>
      {
        using type = B1;
      };
      
      template <class B1, class B2, class ...Bases>
      struct inherit_impl<B1, B2, Bases...> 
        : inherit_impl<
              inherit2_t<B1, B2>
            , Bases...
          >
      {};
      
    }                                                       // namespace detail
  
  //-------------------------------- inherit --------------------------------// 
    
    template <class B1, class B2, class ...Bases>
    struct inherit : detail::inherit_impl<B1, B2, Bases...>
    {};
    
    template <class B1, class B2, class ...Bases>
    using inherit_t = typename detail::inherit_impl<B1, B2, Bases...>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_METAFUNCTION_INHERIT_HPP */