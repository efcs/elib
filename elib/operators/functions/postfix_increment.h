#ifndef ELIB_OPERATORS_POSTFIX_INCREMENT_H
#define ELIB_OPERATORS_POSTFIX_INCREMENT_H


#include <elib/operators/basic_operator.h>
#include <elib/operators/operators_e.h>


namespace elib {
    namespace operators {
        
        
        template <>
        struct basic_operator<op_e::postfix_increment> {
            template <typename T>
            static inline auto
            operator()(T&& v) -> decltype(v++)
            { 
                return v++; 
            }
        };
        
        
    } /* namespace operators */
} /* namespace elib */
#endif /* ELIB_OPERATORS_POSTFIX_INCREMENT_H */
