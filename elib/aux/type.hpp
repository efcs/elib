#ifndef ELIB_AUX_TYPE_HPP
#define ELIB_AUX_TYPE_HPP

namespace elib 
{
    namespace aux
    {
        template <class T>
        using type_ = typename T::type;
    }                                                       // namespace aux
}                                                           // namespace elib
#endif /* ELIB_AUX_TYPE_HPP */