#ifndef ELIB_MP_CONCEPTS_DETECTION_HPP
#define ELIB_MP_CONCEPTS_DETECTION_HPP

# include <elib/mp/concepts/fwd.hpp>
# include <elib/mp/concepts/concept_list.hpp>
# include <elib/mp/integral_constant.hpp>
# include <elib/mp/typedef_detector.hpp>
# include <elib/mp/pair.hpp>
# include <elib/mp/if.hpp>
# include <elib/mp/enable_if.hpp>
# include <utility>

namespace elib 
{
  namespace mp
  {
    
    template <class T>
    using detect_nested_concepts = 
      typename detail::nested_concepts_detector<T>::type;
    
    
    template <class T> 
    using has_nested_concepts = first_t<detect_nested_concepts<T>>;
      
      
    template <class T>
    using get_nested_concepts = 
      enable_if_t<
            first_t<detect_nested_concepts<T>>
          , second_t<detect_nested_concepts<T>>
      >;
      
      
    template <class T>
    using detect_inherited_concepts = 
      typename detail::inherited_concepts_detector<T>::type;
      
      
    template <class T>
    using has_inherited_concepts = first_t<detect_inherited_concepts<T>>;
      
      
    template <class T>
    using get_inherited_concepts = 
      enable_if_t< first_t<detect_inherited_concepts<T>>
                 , second_t<detect_inherited_concepts<T>>
                 >;
      
      
    template <class T>
    using detect_concepts = typename detail::concepts_detector<T>::type;
      
      
    template <class T>
    using has_concepts = first_t<detect_concepts<T>>;
    
    
    template <class T>
    using get_concepts = 
      enable_if_t< first_t<detect_concepts<T>>
                 , second_t<detect_concepts<T>>
                 >;
    
    
    namespace detail
    {
      
      template <class T>
      struct sfinae_is_concepts
      {};
      
      template <class ...Args>
      struct sfinae_is_concepts< concept_list<Args...> >
      {
        using type = concept_list<Args...>;
      };
      
      
      template <class T>
      using sfinae_is_concepts_t = typename sfinae_is_concepts<T>::type;
      
      
      template <class T>
      struct nested_concepts_detector
      {
      private:
        template <class U>
        static pair<true_, typename U::concepts> 
        test(sfinae_is_concepts_t<typename U::concepts>*);
        
        template <class U>
        static pair<false_, na> test(...);

      public:
        using type = decltype( test<T>(0) );
      };
      
      
      template <class T>
      struct inherited_concepts_detector
      {
      private:
        template <class ...Args>
        static pair<true_, concept_list<Args...>> test(concept_list<Args...>);
        
        static pair<false_, na> test(...);
        
      public:
        using type = decltype( test(std::declval<T>()) );
      };
      
      template <class T>
      struct concepts_detector
      {
      private:
        using nested_ = typename nested_concepts_detector<T>::type;
        using inherited_ = typename inherited_concepts_detector<T>::type;
        
        static_assert( !(nested_::first::value && inherited_::first::value), 
        "Ambigious concept list detection: Both nested and inherited detected");
        
      public:
        using type = 
          if_t<
              first_t<nested_>
            , nested_
            , inherited_
          >;
      };
      
    }                                                       // namespace detail
    
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_CONCEPTS_DETECTION_HPP */