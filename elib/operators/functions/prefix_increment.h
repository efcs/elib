#ifndef ELIB_OPERATORS_PREFIX_INCREMENT_H
#define ELIB_OPERATORS_PREFIX_INCREMENT_H


#include <elib/operators/basic_operator.h>
#include <elib/operators/operators_e.h>


namespace elib {
    namespace operators {
        
        
        template <>
        struct basic_operator<op_e::prefix_increment> {
            template <typename T>
            static inline auto
            operator()(T&& v)
            { 
                return ++v; 
            }
        };
        
        
    } /* namespace operators */
} /* namespace elib */
#endif /* ELIB_OPERATORS_PREFIX_INCREMENT_H */#ifndef ELIB_OPERATORS_name_H
#define ELIB_OPERATORS_name_H


#include <elib/operators/basic_operator.h>
#include <elib/operators/operators_e.h>


namespace elib {
    namespace operators {
        
        
        template <>
        struct basic_operator<op_e::enum> {
            template <typename T>
            static inline auto
            operator()(T&& v)
            { 
                return opv; 
            }
        };
        
        
    } /* namespace operators */
} /* namespace elib */
#endif /* ELIB_OPERATORS_name_H */