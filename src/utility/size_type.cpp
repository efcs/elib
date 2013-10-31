#include "elib/utility/size_type.hpp"

#include <elib/pragma/diagnostic_push.hpp>
#include <elib/pragma/ignore_missing_variable_declarations.hpp>

// explicitly instantiate a couple templates so the compiler checks them
elib::size_type_traits<char> _char;
elib::size_type_traits<int> _int;

#include <elib/pragma/diagnostic_pop.hpp>