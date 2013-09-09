#ifndef ELIB_OPERATORS_MODULO_H
#define ELIB_OPERATORS_MODULO_H


#include <elib/operators/basic_operator.h>
#include <elib/operators/operators_e.h>


namespace elib {
    namespace operators {
        
        
        template <>
        struct basic_operator<op_e::modulo> {
            template <typename T, typename U>
            static inline auto
            operator()(T&& lhs, U&& rhs) -> decltype(lhs % rhs)
            { 
                return lhs % rhs; 
            }
        };
        
        
    } /* namespace operators */
} /* namespace elib */
#endif /* ELIB_OPERATORS_MODULO_H */