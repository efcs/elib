#ifndef ELIB_ENUM_TRAITS_FWD_H
#define ELIB_ENUM_TRAITS_FWD_H

#include "basic_enum_traits_fwd.h"

namespace elib {
    
class bad_enum_cast;

enum class iter_pos_e;

template <typename Enum> 
class enum_traits;

template <typename Enum>
class enum_iterator;
    
} /* namespace elib */
#endif /* ELIB_ENUM_TRAITS_FWD_H */