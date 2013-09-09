#ifndef ELIB_OPERATORS_INDIRECTION_H
#define ELIB_OPERATORS_INDIRECTION_H


#include <elib/operators/basic_operator.h>
#include <elib/operators/operators_e.h>


namespace elib {
    namespace operators {
        
        
        template <>
        struct basic_operator<op_e::indirection> {
            template <typename T>
            static inline auto
            operator()(T&& v) -> decltype(*v)
            { 
                return *v; 
            }
        };
        
        
    } /* namespace operators */
} /* namespace elib */
#endif /* ELIB_OPERATORS_INDIRECTION_H */