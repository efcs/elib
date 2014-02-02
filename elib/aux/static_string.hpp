#ifndef ELIB_AUX_STATIC_STRING_HPP
#define ELIB_AUX_STATIC_STRING_HPP

# include <cstddef>

namespace elib { namespace aux
{
    template <char ...Ch>
    struct static_string
    {
        static constexpr const std::size_t size = sizeof...(Ch);
        static constexpr const char value[] = {Ch...};
    };
}}                                                          // namespace elib
#endif /* ELIB_AUX_STATIC_STRING_HPP */