#ifndef ELIB_MP_MODEL_OF_HPP
#define ELIB_MP_MODEL_OF_HPP

# include <elib/mp/member_type_detector.hpp>
# include <type_traits>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    using has_model_of = has_model_type_member_type<T>;
    
    
    template <class T>
    using has_model_of_t = typename has_model_type_member_type<T>::type;
    
    
    template <class T, class Tag>
    struct is_model_of :
      std::is_base_of<Tag, typename T::model_type>::type
    {};
    
    
    template <class T, class Tag>
    using is_model_of_t = typename 
      std::is_base_of<Tag, typename T::model_type>::type;
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_MODEL_OF_HPP */