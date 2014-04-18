#ifndef ELIB_MP_IF_HPP
#define ELIB_MP_IF_HPP

namespace elib { namespace mp
{
    ////////////////////////////////////////////////////////////////////////////
    // aux::if_c
    template <bool Pred, class Then, class Else>
    struct if_c;

    template <class Then, class Else>
    struct if_c<true, Then, Else>
    {
        using type = Then;
    };

    template <class Then, class Else>
    struct if_c<false, Then, Else>
    {
        using type = Else;
    };

    ////////////////////////////////////////////////////////////////////////////
    // aux::if_c_t
    template <bool Pred, class Then, class Else>
    using if_c_t = typename if_c<Pred, Then, Else>::type;

    ////////////////////////////////////////////////////////////////////////////
    // aux::if_
    template <class Pred, class Then, class Else>
    struct if_ : if_c<static_cast<bool>(Pred::type::value), Then, Else> {};

    ////////////////////////////////////////////////////////////////////////////
    // aux::if_t
    template <class Pred, class Then, class Else>
    using if_t = typename if_c<static_cast<bool>(Pred::type::value), Then, Else>::type;
}}                                                          // namespace elib
#endif /* ELIB_MP_IF_HPP */