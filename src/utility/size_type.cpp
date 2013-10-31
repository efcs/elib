#include "elib/utility/size_type.hpp"
# include <elib/pragma.hpp>

ELIB_PRAGMA_DIAG_PUSH()
ELIB_PRAGMA_IGNORE_MISSING_VARIABLE_DECLARATIONS()

// explicitly instantiate a couple templates so the compiler checks them
elib::size_type_traits<char> _char;
elib::size_type_traits<int> _int;

ELIB_PRAGMA_DIAG_POP()