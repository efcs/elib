#ifndef ELIB_ITER_TRAITS_HPP
#define ELIB_ITER_TRAITS_HPP

# include <elib/aux/meta.hpp>
# include <elib/aux/traits/is_convertible.hpp>
# include <iterator>

namespace elib { namespace iter
{
    ////////////////////////////////////////////////////////////////////////////
    template <class Iter>
    using iterator_category_t = typename 
    std::iterator_traits<Iter>::iterator_category;
    
    template <class Iter>
    using iterator_difference_t = typename
    std::iterator_traits<Iter>::difference_type;
    
    template <class Iter>
    using iterator_value_t = typename
    std::iterator_traits<Iter>::value_type;
    
    template <class Iter>
    using iterator_reference_t = typename
    std::iterator_traits<Iter>::reference;
    
    template <class Iter>
    using iterator_pointer_t = typename
    std::iterator_traits<Iter>::pointer;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class Category>
    using is_input_tag = aux::is_convertible<Category, std::input_iterator_tag>;
    
    template <class Category>
    using is_output_tag = aux::is_convertible<Category, std::output_iterator_tag>;
    
    template <class Category>
    using is_forward_tag = aux::is_convertible<Category, std::forward_iterator_tag>;
    
    template <class Category>
    using is_bidirectional_tag = aux::is_convertible<Category, std::bidirectional_iterator_tag>;
    
    template <class Category>
    using is_random_access_tag = aux::is_convertible<Category, std::random_access_iterator_tag>;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class Iter>
    using is_input_iterator = is_input_tag<iterator_category_t<Iter>>;
    
    template <class Iter>
    using is_output_iterator = is_output_tag<iterator_category_t<Iter>>;
    
    template <class Iter>
    using is_forward_iterator = is_forward_tag<iterator_category_t<Iter>>;
    
    template <class Iter>
    using is_bidirectional_iterator = is_bidirectional_tag<iterator_category_t<Iter>>;
    
    template <class Iter>
    using is_random_access_iterator = is_random_access_tag<iterator_category_t<Iter>>;
    
    template <class Iter>
    using is_iterator = elib::or_<
        is_input_iterator<Iter>
      , is_output_iterator<Iter>
      >;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class A, class B>
    using is_interoperable = aux::or_<
        aux::is_convertible<A, B>
      , aux::is_convertible<B, A>
    >;
    
    ////////////////////////////////////////////////////////////////////////////
    template <class A, class B>
    using enable_if_iteroperable_t = 
        aux::enable_if_t<is_interoperable<A, B>>;
        
    ////////////////////////////////////////////////////////////////////////////
    template <class I1, class I2>
    using choose_iterator_traits = 
        elib::if_t<
            aux::is_convertible<I2, I1>
          , std::iterator_traits<I1>
          , std::iterator_traits<I2>
        >;
                
    ////////////////////////////////////////////////////////////////////////////
    template <class I1, class I2>
    using choose_difference_type = typename 
        choose_iterator_traits<I1, I2>::difference_type;

}}                                                          // namespace elib
#endif /* ELIB_ITER_TRAITS_HPP */