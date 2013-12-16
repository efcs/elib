#ifndef ELIB_MP_SEQUENCE_INTRINSICS_HPP
#define ELIB_MP_SEQUENCE_INTRINSICS_HPP

# include <elib/mp/get_impl.hpp>
# include <elib/mp/na.hpp>
# include <elib/mp/integral_constant.hpp>

# include <cstddef>

namespace elib 
{
  namespace mp
  {
    
    template <class Seq, class N>
    using at = typename get_impl_t<Seq>::template at<Seq, N>;
    
    template <class Seq, class N>
    using at_t = typename at<Seq, N>::type;
    
    
    template <class Seq, std::size_t N>
    using at_c = typename get_impl_t<Seq>::template at<Seq, size_type<N>>;
    
    template <class Seq, std::size_t N>
    using at_c_t = typename at<Seq, size_type<N>>::type;
    
    
    template <class Seq>
    using back = typename get_impl_t<Seq>::template back<Seq>;

    template <class Seq>
    using back_t = typename back<Seq>::type;
    
    
    template <class Seq>
    using begin = typename get_impl_t<Seq>::template begin<Seq>;

    template <class Seq>
    using begin_t = typename begin<Seq>::type;
    
    
    template <class Seq>
    using clear = typename get_impl_t<Seq>::template clear<Seq>;

    template <class Seq>
    using clear_t = typename clear<Seq>::type;
    
    
    template <class Seq>
    using empty = typename get_impl_t<Seq>::template empty<Seq>;

    template <class Seq>
    using empty_t = typename empty<Seq>::type;
    
    
    template <class Seq>
    using end = typename get_impl_t<Seq>::template end<Seq>;

    template <class Seq>
    using end_t = typename end<Seq>::type;
    
    
    template <class Seq, class ...Args>
    using erase = typename get_impl_t<Seq>::template erase<Seq, Args...>;

    template <class Seq, class ...Args>
    using erase_t = typename erase<Seq, Args...>::type;
    
    
    template <class Seq, class Key>
    using erase_key = typename get_impl_t<Seq>::template erase_key<Seq, Key>;

    template <class Seq, class Key>
    using erase_key_t = typename erase_key<Seq, Key>::type;
    
    
    template <class Seq>
    using front = typename get_impl_t<Seq>::template front<Seq>;

    template <class Seq>
    using front_t = typename front<Seq>::type;
    
    
    template <class Seq, class Key>
    using has_key = typename get_impl_t<Seq>::template has_key<Seq, Key>;

    template <class Seq, class Key>
    using has_key_t = typename has_key<Seq, Key>::type;
    
    
    template <class Seq, class Pos, class T>
    using insert = typename get_impl_t<Seq>::template insert<Seq, Pos, T>;

    template <class Seq, class Pos, class T>
    using insert_t = typename insert<Seq, Pos, T>::type;
    
    
    template <class Seq, class Pos, class Range>
    using insert_range = 
      typename get_impl_t<Seq>::template insert_range<Seq, Pos, Range>;

    template <class Seq, class Pos, class Range>
    using insert_range_t = 
      typename insert_range<Seq, Pos, Range>::type;
      
    
    // TODO is_sequence
    
    
    template <class Seq, class T>
    using key_type = typename get_impl_t<Seq>::template key_type<Seq, T>;

    template <class Seq, class T>
    using key_type_t = typename key_type<Seq, T>::type;
    
    
    template <class Seq, class Key>
    using order = typename get_impl_t<Seq>::template order<Seq, Key>;

    template <class Seq, class Key>
    using order_t = typename order<Seq, Key>::type;
    
    
    template <class Seq, class T>
    using push_back = typename get_impl_t<Seq>::template push_back<Seq, T>;

    template <class Seq, class T>
    using push_back_t = typename push_back<Seq, T>::type;
    
    
    template <class Seq>
    using pop_back = typename get_impl_t<Seq>::template pop_back<Seq>;

    template <class Seq>
    using pop_back_t = typename pop_back<Seq>::type;
    
    
    template <class Seq, class T>
    using push_front = typename get_impl_t<Seq>::template push_front<Seq, T>;

    template <class Seq, class T>
    using push_front_t = typename push_front<Seq, T>::type;
    
    
    template <class Seq>
    using pop_front = typename get_impl_t<Seq>::template pop_front<Seq>;

    template <class Seq>
    using pop_front_t = typename pop_front<Seq>::type;
    
    
    // TODO Sequence tag
    
    template <class Seq>
    using size = typename get_impl_t<Seq>::template size<Seq>;

    template <class Seq>
    using size_t = typename size<Seq>::type;
    
    
    template <class Seq, class T>
    using value_type = typename get_impl_t<Seq>::template value_type<Seq, T>;

    template <class Seq, class T>
    using value_type_t = typename value_type<Seq, T>::type;
    

  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_INTRINSICS_HPP */