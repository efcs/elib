#ifndef ELIB_AUX_TRAITS_CONDITIONAL_HPP
#define ELIB_AUX_TRAITS_CONDITIONAL_HPP

# include <type_traits>

namespace elib { namespace aux
{
    namespace traits
    {
        using std::conditional;
        
        template <bool Pred, class Then, class Else>
        using conditional_t = typename conditional<Pred, Then, Else>::type;
    }                                                       // namespace traits
    
    using namespace traits;
    
}}                                                          // namespace elib
#endif /* ELIB_AUX_TRAITS_CONDITIONAL_HPP */