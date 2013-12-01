#ifndef ELIB_MP_VECTOR_HPP
#define ELIB_MP_VECTOR_HPP

# include <elib/mp/vector_fwd.hpp>
# include <elib/mp/intrinsic/intrinsic_fwd.hpp>
# include <elib/mp/iterator_fwd.hpp>
# include <elib/mp/iterator_tags.hpp>
# include <elib/mp/next_prior.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/type_wrapper.hpp>
# include <elib/mp/void.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
    ////////////////////////////////////////////////////////////////////////////////
    //                            Item                                              
    ////////////////////////////////////////////////////////////////////////////////
      
      
      template <class T, class Base, class=vector_front_tag>
      struct vector_insert_item;
      
      template <class Base, class=vector_front_tag>
      struct vector_erase_item;
    
    //-------------------------------- insert -------------------------------// 
      
      template <class T, class Base>
      struct vector_insert_item<T, Base, vector_front_tag> : Base
      {
        using type = vector_insert_item;
        using size = next_t<typename Base::size>;
        
        using lower_bound_ = prior_t<typename Base::lower_bound_>;
        using upper_bound_ = typename Base::upper_bound_;
        using index_ = lower_bound_;
        
        static type_<T> get_(index_);
        using Base::get_;
      };
      
      
      template <class T, class Base>
      struct vector_insert_item<T, Base, vector_back_tag> : Base
      {
        using type = vector_insert_item;
        using size = next_t<typename Base::size>;
        
        using index_ = typename Base::upper_bound_;
        using lower_bound_ = typename Base::lower_bound_;
        using upper_bound_ = typename Base::upper_bound_;
        
        static type_<T> get_(index_);
        using Base::get_;
      };
      
    //-------------------------------- erase --------------------------------// 
      
      template <class Base>
      struct vector_erase_item<Base, vector_front_tag> : Base
      {
        using type = vector_erase_item;
        using size = prior_t<typename Base::size>;
        
        using index_ = typename Base::lower_bound_;
        using upper_bound_ = typename Base::upper_bound_;
        using lower_bound_ = next_t<typename Base::lower_bound_>;
        
        static type_<void_> get_(index_);
        using Base::get_;
      };
      
      
      template <class Base> 
      struct vector_erase_item<Base, vector_back_tag> : Base
      {
        using type = vector_erase_item;
        using size = prior_t<typename Base::size>;
        
        using upper_bound_ = prior_t<typename Base::upper_bound_>;
        using lower_bound_ = typename Base::lower_bound_;
        using index_ = upper_bound_;
        
        static type_<void_> get_(index_);
        using Base::get_;
      };
      
    ////////////////////////////////////////////////////////////////////////////////
    //                            Vector At                                              
    ////////////////////////////////////////////////////////////////////////////////
    
      template <class Vect, long Index>
      struct vector_at
      {
        using index_ = long_<Index>;
        using result_ = decltype( Vect::get_(index_()) );
        using type = unwrap_t<result_>;
      };
      
      template <class Vect, long Index>
      using vector_at_t = typename vector_at<Vect, Index>::type;
      
    ////////////////////////////////////////////////////////////////////////////////
    //                            Vector Iterator                                              
    ////////////////////////////////////////////////////////////////////////////////
    
      template <class Vect, long Pos>
      struct vector_iter
      {
        using tag = vector_iter_tag;
        using category = random_access_iterator_tag;
        
        using type = vector_at_t<Vect, Pos>;
      };
      
    }                                                       // namespace detail
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            Iterator Metafunctions                                            
  ////////////////////////////////////////////////////////////////////////////////
    
    
  //-------------------------------- next --------------------------------// 
  
    template <class Vect, long Pos>
    struct next< detail::vector_iter<Vect, Pos> >
    {
      using type = detail::vector_iter< Vect, Pos + 1>;
    };
    
  //-------------------------------- prior --------------------------------// 
    
    template <class Vect, long Pos>
    struct prior< detail::vector_iter<Vect, Pos> >
    {
      using type = detail::vector_iter< Vect, Pos-1 >;
    };
    
  //-------------------------------- advance --------------------------------// 

    template <class Vect, long Pos, class N>
    struct advance< detail::vector_iter<Vect, Pos>,  N>
    {
      using type = detail::vector_iter<Vect, Pos + N::type::value>;
    };
    
  //-------------------------------- distance --------------------------------// 
  
    template <class Vect1, long Pos1, class Vect2, long Pos2>
    struct distance< 
              detail::vector_iter<Vect1, Pos1>
            , detail::vector_iter<Vect2, Pos2>
          >
      : long_<Pos2 - Pos1>
    {};
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                            Vector                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    
    /* Empty specialization */
    template <class ...Args>
    struct vector
    {
      using type = vector;
      using tag = detail::vector_tag;
      
      using size = size_type<0>;
      
      using lower_bound_ = long_<32768>;
      using upper_bound_ = lower_bound_;
      
      static type_<void_> get_(...);
      
      static_assert(sizeof...(Args) == 0, 
              "Overload resolution check");
    };
    
    template <class First, class ...Rest>
    struct vector<First, Rest...> 
      : detail::vector_insert_item<
            First
          , vector<Rest...>
          , detail::vector_front_tag
        >
    {
      using type = vector;
    };
    
    //-------------------------------- Vector_C --------------------------------// 
    
    template <class T, T ...Values>
    using vector_c = vector< integral_c<T, Values>... >;
    
  ////////////////////////////////////////////////////////////////////////////////
  //                           Intrinsic Metafunctions                                              
  ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
        
    //-------------------------------- begin --------------------------------// 
    
      template <>
      struct begin_impl< detail::vector_tag >
      {
        template <class Vect>
        struct apply
        {
          using type = vector_iter<Vect, Vect::lower_bound_::value>;
        };
      };
    
    //-------------------------------- end ----------------------------------// 
    
      template <>
      struct end_impl< detail::vector_tag >
      {
        template <class Vect>
        struct apply
        {
          using type = vector_iter<Vect, Vect::upper_bound_::value>;
        };
      };
      
      //-------------------------------- nested_size --------------------------// 
    
      template <>
      struct nested_size_impl< detail::vector_tag >
      {
        template <class Vect>
        struct apply : Vect::size
        {};
      };
    
    //-------------------------------- size ---------------------------------// 
      
      template <>
      struct size_impl< detail::vector_tag >
      {
        template <class Vect>
        struct apply : Vect::size
        {};
      };
   
    
    //-------------------------------- empty --------------------------------//
    
      template <>
      struct empty_impl< detail::vector_tag >
      {
        template <class Vect>
        struct apply : bool_< Vect::size::value == 0 >
        {};
      };
      
    //-------------------------------- front --------------------------------// 
      
      template <>
      struct front_impl< detail::vector_tag >
      {
        template <class Vect>
        struct apply : vector_at<Vect, Vect::lower_bound_::value>
        {};
      };
    
    //-------------------------------- back ---------------------------------// 
      
      template <>
      struct back_impl< detail::vector_tag >
      {
        template <class Vect>
        struct apply : vector_at<Vect, Vect::upper_bound_::value - 1>
        {};
      };
    
    //-------------------------------- at -----------------------------------// 
    
      template <>
      struct at_impl< detail::vector_tag >
      {
        template <class Vect, class N>
        struct apply 
          : vector_at< Vect, Vect::lower_bound_::value + N::type::value >
        {};
      };
      
    //-------------------------------- clear --------------------------------// 
      
      template <>
      struct clear_impl< detail::vector_tag >
      {
        template <class Seq>
        struct apply
        {
          using type = vector<>;
        };
      };
      
    //-------------------------------- push_back ----------------------------//
    
      template <>
      struct push_back_impl< detail::vector_tag >
      {
        template <class Vect, class T>
        struct apply
        {
          using type = vector_insert_item<T, Vect, vector_back_tag>;
        };
      };
    
    //-------------------------------- pop_back -----------------------------// 
    
      template <>
      struct pop_back_impl< detail::vector_tag >
      {
        template <class Vect>
        struct apply
        {
          using type = vector_erase_item<Vect, vector_back_tag>;
        };
      };
    
    //-------------------------------- push_front ---------------------------// 
      
      template <>
      struct push_front_impl< detail::vector_tag >
      {
        template <class Vect, class T>
        struct apply
        {
          using type = vector_insert_item<T, Vect, vector_front_tag>;
        };
      };
    
    //-------------------------------- pop_front ----------------------------// 
      
      template <>
      struct pop_front_impl< detail::vector_tag >
      {
        template <class Vect>
        struct apply
        {
          using type = vector_erase_item<Vect, vector_back_tag>;
        };
      };
    
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VECTOR_HPP */
