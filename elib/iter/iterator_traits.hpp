#ifndef ELIB_ITER_ITERATOR_TRAITS_HPP
#define ELIB_ITER_ITERATOR_TRAITS_HPP

# include <elib/aux.hpp>
# include <iterator>
# include <cstddef>

namespace elib { namespace iter
{
    template <class A, class B>
    using is_interoperable = aux::or_<
        aux::is_convertible<A, B>
      , aux::is_convertible<B, A>
    >;
    
    template <class A, class B>
    using enable_if_iteroperable_t = 
        aux::enable_if_t<is_interoperable<A, B>>;
        
    
    template <class I1, class I2>
    using choose_iterator_traits = 
        elib::if_t<
            aux::is_convertible<I2, I1>
          , std::iterator_traits<I1>
          , std::iterator_traits<I2>
        >;
        
    template <class I1, class I2>
    using choose_difference_type = typename 
        choose_iterator_traits<I1, I2>::difference_type;
    
}}                                                          // namespace elib
#endif /* ELIB_ITER_ITERATOR_TRAITS_HPP */