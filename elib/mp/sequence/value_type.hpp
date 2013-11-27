#ifndef ELIB_MP_SEQUENCE_VALUE_TYPE_HPP
#define ELIB_MP_SEQUENCE_VALUE_TYPE_HPP

# include <elib/mp/sequence/sequence_fwd.hpp>
# include <elib/mp/sequence/sequence_tag.hpp>

namespace elib
{
  namespace mp
  {
  //-------------------------------- value_type -----------------------------// 
  
    template <class Seq, class T>
    struct value_type
      : detail::value_type_impl<sequence_tag_t<Seq>> 
          ::template apply<Seq, T>
    {};
    
    
    template <class Seq, class T>
    using value_type_t = typename value_type<Seq, T>::type;
    
    
    namespace detail
    {
    //-------------------------------- value_type_impl ----------------------// 
    
      // No default impl
      template <class Tag>
      struct value_type_impl
      {
        template <class Seq, class T>
        struct apply;
      };

    }                                                       // namespace detail
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_SEQUENCE_VALUE_TYPE_HPP */