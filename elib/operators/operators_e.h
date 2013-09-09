#ifndef ELIB_OPERATORS_OPERATORS_E_H
#define ELIB_OPERATORS_OPERATORS_E_H


namespace elib {
namespace operators {
    
    
enum class op_e {
    assignment, // NOT IMPLEMENTED
    
    //arithmetic
    addition,
    subtraction,
    unary_plus,
    unary_minus,
    multiplication,
    division,
    modulo,
    prefix_increment,
    postfix_increment,
    prefix_decrement,
    postfix_decrement,
    
    //arithmetic assign
    addition_assign,
    subtraction_assign,
    multiplication_assign,
    division_assign,
    modulo_assign,
    
    //comparision
    equal,
    not_equal,
    greater,
    less,
    greater_equal,
    less_equal,
    
    // logical operators
    logical_not,
    logical_and,
    logical_or,
    
    //bitwise operators
    bitwise_not,
    bitwise_and,
    bitwise_or,
    bitwise_xor,
    bitwise_left_shift,
    bitwise_right_shift,
    
    //bitwise assign
    bitwise_and_assign,
    bitwise_or_assign,
    bitwise_xor_assign,
    bitwise_left_shift_assign,
    bitwise_right_shift_assign,
    
    //member & pointer
    array_subscript,
    indirection,
    reference,
    
//
// ALL BELOW ARE NOT IMPLEMENTED
//
    structure_dereference,
    structure_dereference_indirection
    
    // others
    function_call,
    comma,
    c_cast
};

    
} /* namespace operators */
} /* namespace elib */
#endif /* ELIB_OPERATORS_OPERATORS_E_H */