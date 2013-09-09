#ifndef ELIB_OPERATORS_BASIC_OPERATOR_H
#define ELIB_OPERATORS_BASIC_OPERATOR_H

#include <elib/operators/operators_e.h>

namespace elib {
namespace operators {

    
template <op_e oper>
struct op_func {
    template <typename T>
    inline auto
    operator()(T operand) -> decltype(+operand) = delete;
    
    template <typename T, typename U>
    inline auto
    operator()(T&& lhs, U&& rhs) -> decltype(lhs + rhs) = delete;
};


} /* namespace operators */
} /* namespace elib */
#endif /* ELIB_OPERATORS_BASIC_OPERATOR_H */