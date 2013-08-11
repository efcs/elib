#ifndef ELIB_ARGP__ARG_H
#define ELIB_ARGP__ARG_H

#ifndef ELIB_ARGP_ARG_H
#   error do not include this file directly
#endif 

namespace elib {
namespace argp {
    
    
namespace detail {
    
////////////////////////////////////////////////////////////////////////////////
//                           assigners                                             
////////////////////////////////////////////////////////////////////////////////
    
/* assign a value to its storage,  
 * FromT must be implicitly convertable to DestT */
template <typename FromT, typename DestT>
struct assigner {
    inline static void
    assign(FromT from, DestT& dest)
    { dest = from; }
};

/* assign to a vector, it pushes the value to the back */
template <typename FromT, typename DestT>
struct assigner <FromT, std::vector<DestT>> { 
    inline static void
    assign(FromT from, std::vector<DestT> & dest)
    { dest.push_back(std::forward<FromT>(from)); }
}; 

} /* namespace detail */

template <typename T>
basic_arg<T>::basic_arg(arg_type_e arg_type,
                    const std::string & name,
                    const std::string & cmd_desc,
                    const std::string & desc,
                    storage_type & store)
    : arg_option(arg_type, name, cmd_desc, desc),
      m_val(store)
      
{
    m_transformer = lexical_cast<value_type, std::string>;
}

template <typename T>
basic_arg<T>::basic_arg(arg_type_e arg_type,
              const std::string & name,
              const std::string & cmd_desc,
              const std::string & desc,
              storage_type & store,
              transformer_type & transformer)
    : arg_option(arg_type, name, cmd_desc, desc),
      m_val(store), m_transformer(transformer)
{
}

    
template <typename T>
void
basic_arg<T>::implicit_value(const storage_type & v)
{
    m_implicit = std::make_shared<storage_type>(
                    std::forward<storage_type>(v));
}

template <typename T>
bool
basic_arg<T>::has_implicit_value()
{
    return ((bool)m_implicit);
}

template <typename T>
void
basic_arg<T>::apply_implicit_value()
{
    detail::assigner<value_type, storage_type>::assign(*m_implicit, m_val);
}
    
template <typename T>
void 
basic_arg<T>::apply_value(const std::string & s)
{
    detail::assigner<value_type, storage_type>::assign(m_transformer(s), m_val);
}
    
/* error checking should be done in parser,
 * we assume that the token already matches the
 * option description */
template <typename T>
void
basic_arg<T>::notify(const arg_token & tk)
{
    if (arg_type() == arg_type_e::positional) {
        apply_value(tk.value());
    }
    else if (arg_type() == arg_type_e::option) {
        if (tk.has_value())
            apply_value(tk.value());
        else
            apply_implicit_value();
    } else if (arg_type() == arg_type_e::flag && has_implicit_value()) {
        apply_implicit_value();
    }
    
    m_count++;
}


    
    
} /* namespace argp */
} /* namespace elib */
#endif /* ELIB_ARGP__ARG_H */