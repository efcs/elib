#ifndef ELIB_AUX_NO_DECAY_HPP
#define ELIB_AUX_NO_DECAY_HPP

namespace elib { namespace aux
{
    template <class T>
    struct no_decay { using type = T; };
}}                                                          // namespace elib
#endif /* ELIB_AUX_NO_DECAY_HPP */