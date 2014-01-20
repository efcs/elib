#ifndef ELIB_UTILITY_NO_DECAY_HPP
#define ELIB_UTILITY_NO_DECAY_HPP

namespace elib 
{
    namespace utility
    {
        template <class T>
        struct no_decay
        {
            using type = T;
        };
    }                                                       // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_NO_DECAY_HPP */