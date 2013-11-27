#ifndef ELIB_MP_SEQUENCE_LIST_HPP
#define ELIB_MP_SEQUENCE_LIST_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>
# include <elib/mp/types/size_type.hpp>
# include <elib/mp/iterator.hpp>

# include <elib/CXX14/type_traits.hpp>


namespace elib 
{
  namespace mp
  {
    
    namespace detail
    {
    //-------------------------------- list tags ----------------------------// 
      
      struct list_tag {};
      struct list_iter_tag {};
      
    //-------------------------------- list_item ----------------------------// 
      template <class Item, class Next, class Size>
      struct list_item
      {
        using tag = list_tag;
        using type = list_item;
        using item = Item;
        using next = Next;
        using size = Size;
      };
      
    //-------------------------------- list_end -----------------------------// 
      class list_end
      {
        using tag = list_tag;
        using type = list_end;
        using size = size_type<0>;
      };
      
      template <class ListNode>
      struct list_iter
      {
        using tag = list_iter_tag;
        using category = forward_iterator_tag;
      };                                                    
    }                                                       // namespace detail
    
  //-------------------------------- list --------------------------------// 
    
    template <class ...Args>
    struct list
      : detail::list_end
    {
      using type = list;
      
      static_assert(sizeof...(Args) == 0, "Args must be empty");
    };
    
    
    template <class First, class ...Rest>
    struct list<First, Rest...> 
      : detail::list_item<
          First
          , list<Rest...>
          , size_type<sizeof...(Rest) + 1>
      >
    {
      using type = list;
    };
    
    
  //-------------------------------- list_c --------------------------------// 
    
    template <class T, T ...Values>
    struct list_c
      : detail::list_end
    {
      using value_type = T;
      using type = list_c;
    };
    
    template <class T, T First, T ...Rest>
    struct list_c<T, First, Rest...>
      : detail::list_item<
          std::integral_constant<T, First>
          , list_c<T, Rest...>
          , size_type<sizeof...(Rest) + 1>
        >
    {
      using value_type = T;
      using type = list_c;
    };
  
    
    ////////////////////////////////////////////////////////////////////////////
    //                            Iterator Metafunctions                                              
    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
      
    //-------------------------------- advance ------------------------------//
      //TODO
      template <>
      struct advance_impl<detail::list_iter_tag>
      {
        template <class Iter, class N>
        struct apply;
      };
      
    //-------------------------------- distance -----------------------------//
      //TODO
      template <>
      struct distance_impl<detail::list_iter_tag>
      {
        template <class First, class Last>
        struct apply;
      };
      
    }                                                       // namespace detail
    
  //-------------------------------- next --------------------------------// 
    template <class Node>
    struct next< detail::list_iter<Node> >
    {
      using type = detail::list_iter< typename Node::next >;
    };
    
  //-------------------------------- deref --------------------------------// 
    template <class Node>
    struct deref< detail::list_iter<Node> >
    {
      using type = typename Node::item;
    };
    
    
    ////////////////////////////////////////////////////////////////////////////
    //                            Intrinsic Metafunctions                                              
    ////////////////////////////////////////////////////////////////////////////
    namespace detail
    {
    //-------------------------------- begin --------------------------------//
    
      template <>
      struct begin_impl<list_tag>
      {
        template <class Seq>
        struct apply
        {
          using type = list_iter<typename Seq::type>;
        };
      };
    
    //-------------------------------- end ----------------------------------//
      
      template <>
      struct end_impl<list_tag>
      {
        template <class Seq>
        struct apply
        {
          using type = list_iter<list_end>;
        };
      };
      
    //-------------------------------- size ---------------------------------//
    
      template <>
      struct size_impl<list_tag>
      {
        template <class Seq>
        struct apply : Seq::size
        {};
      };
    
    //-------------------------------- empty --------------------------------//
      template <>
      struct empty_impl<list_tag>
      {
        template <class Seq>
        struct apply : bool_< Seq::size::value == 0 >
        {};
      };
    
    //-------------------------------- front --------------------------------//
      
      template <>
      struct front_impl<list_tag>
      {
        template <class Seq>
        struct apply
        {
          using type = typename Seq::item;
        };
      };
    
    //-------------------------------- insert -------------------------------//
      //TODO
      template <>
      struct insert_impl<list_tag>
      {
        template <class Seq, class Pos, class T>
        struct apply;
      };
      
    //-------------------------------- insert_range -------------------------//
      //TODO
      template <>
      struct insert_range_impl<list_tag>
      {
        template <class Seq, class Pos, class Range>
        struct apply;
      };
    
    //-------------------------------- erase --------------------------------//
      //TODO
      template <>
      struct erase_impl<list_tag>
      {
        template <class Seq, class First, class Last>
        struct apply;
      };
    
    //-------------------------------- clear --------------------------------//
      
      template <>
      struct clear_impl<list_tag>
      {
        template <class Seq>
        struct apply
        {
          using type = list_end;
        };
      };
    
    //-------------------------------- push_front ---------------------------//
      
      template <>
      struct push_front_impl<list_tag>
      {
        template <class Seq, class T>
        struct apply
        {
          using type = list_item<T, Seq, size_type<Seq::size::value + 1> >;
        };
      };
    
    //-------------------------------- pop_front ----------------------------// 
      
      template <>
      struct pop_front_impl<list_tag>
      {
        template <class Seq>
        struct apply
        {
          using type = typename Seq::next;
          
          static_assert(empty_t<Seq>::value == false, "cannot pop empty list");
        };
      };
      
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_LIST_HPP */