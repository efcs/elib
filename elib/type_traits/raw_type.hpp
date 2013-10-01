#ifndef ELIB_TYPE_TRAITS_RAW_TYPE_HPP
#define ELIB_TYPE_TRAITS_RAW_TYPE_HPP


# include <elib/type_traits/remove_cv.hpp>
# include <elib/type_traits/remove_reference.hpp>


namespace elib 
{
  namespace type_traits
  {
    
    template <typename T>
    struct raw_type
    {
      typedef remove_cv_t<remove_reference_t<T>> type;
    };                                                      // struct raw_type
    
    
    template <typename T>
    using raw_type_t = typename raw_type<T>::type;
    
    
  }                                                    // namespace type_traits
}                                                           // namespace elib
#endif /* ELIB_TYPE_TRAITS_RAW_TYPE_HPP */
