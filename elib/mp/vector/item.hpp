#ifndef ELIB_MP_VECTOR_ITEM_HPP
#define ELIB_MP_VECTOR_ITEM_HPP

# include <elib/mp/vector/fwd.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/na.hpp>

namespace elib 
{
  namespace mp
  {
    namespace detail
    {
      
      
      template <class T, class Vector>
      struct vector_item<vector_front_tag, T, Vector>
        : Vector
      {
        using type = vector_item;
        
        using lower_bound_ = size_type<Vector::lower_bound_::value - 1>;
        using upper_bound_ = typename Vector::upper_bound_;
        
        using index = lower_bound_;
        using size = size_type< Vector::size::value + 1>;
        
        static T index_lookup(index);
        using Vector::index_lookup;
      };
      
      
      template <class T, class Vector>
      struct vector_item<vector_back_tag, T, Vector>
        : Vector
      {
        using type = vector_item;
        
        using lower_bound_ = typename Vector::lower_bound_;
        using upper_bound_ = size_type< Vector::upper_bound_::value + 1>;
        
        using index = typename Vector::upper_bound_;
        using size = size_type< Vector::size::value + 1>;
        
        static T index_lookup(index);
        using Vector::index_lookup;
      };
      
      
      template <class Vector>
      struct vector_mask<vector_front_tag, Vector>
        : Vector
      {
        using type = vector_mask;
        
        using lower_bound_ = size_type< Vector::lower_bound_::value + 1>;
        using upper_bound_ = typename Vector::upper_bound_;
      
        // note: not 'index' since it is not a valid entry 
        using index_ = typename Vector::lower_bound_;
        using size = size_type< Vector::size::value - 1>;
        
        static na index_lookup(index_);
        using Vector::index_lookup;
      };
    
      template <class Vector>
      struct vector_mask<vector_back_tag, Vector>
        : Vector
      {
        using type = vector_mask;
        
        using lower_bound_ = typename Vector::lower_bound_;
        using upper_bound_ = size_type<Vector::upper_bound_::value - 1>;
        
        using index_ = upper_bound_;
        using size = size_type<Vector::size::value - 1>;
        
        static na index_lookup(index_);
        using Vector::index_lookup;
      };
    
    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_VECTOR_ITEM_HPP */
