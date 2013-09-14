#ifndef ELIB_ARGP__ARG_HPP
#define ELIB_ARGP__ARG_HPP

#ifndef ELIB_ARGP_ARG_HPP
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

/* for when an implicit value is a vector */
template <typename FromT, typename DestT>
struct assigner<std::vector<FromT>, std::vector<DestT>>
{
    inline static void
    assign(const std::vector<FromT> from, std::vector<DestT> & dest)
    { dest = from; }
};


////////////////////////////////////////////////////////////////////////////////
//                      transformer_helper                                                    
////////////////////////////////////////////////////////////////////////////////

inline bool
flag_transformer(const std::string & s)
{
    /* unused */
    ((void)s);
    return true;
}


/* initalize the pointer to nullptr, in this case, it must be set
 * by the function call */
template <typename T, arg_type_e e, 
          bool is_lex, bool is_enum>
struct _transformer_helper {
    static inline typename basic_arg<T>::transformer_type
    transformer()
    {
        return nullptr;
    }
};

template <>
struct _transformer_helper<bool, arg_type_e::flag, true, false> {
    static inline typename basic_arg<bool>::transformer_type 
    transformer() 
    { 
        return flag_transformer; 
    }
};

template <typename T, arg_type_e e>
struct _transformer_helper<T, e, true, false> {
    static inline typename basic_arg<T>::transformer_type 
    transformer() 
    { 
        return lexical_cast<T, std::string>; 
    }
};

template <typename T, arg_type_e e>
struct _transformer_helper<T, e, false, true> {
    static inline typename basic_arg<T>::transformer_type
    transformer() 
    { 
        return enumeration::enum_cast_string<T>; 
    }
};


template <typename T, arg_type_e e>
struct transformer_helper {
    static inline typename basic_arg<T>::transformer_type
    transformer() 
    {
        return _transformer_helper<T, e, is_lexical<T>::value, 
                                   std::is_enum<T>::value>::transformer();
    }
};


/* turn arg_type_e into compile-time info */
template <typename T>
typename basic_arg<T>::transformer_type
get_tranformer(arg_type_e e)
{  
    switch (e) {
        case arg_type_e::flag:
            return transformer_helper<T, arg_type_e::flag>::transformer();
        case arg_type_e::option:
            return transformer_helper<T, arg_type_e::option>::transformer();
        case arg_type_e::positional:
            return transformer_helper<T, arg_type_e::positional>::transformer();
    }
    throw 1;
}


} /* namespace detail */


////////////////////////////////////////////////////////////////////////////////
//                          basic_arg<T>                                                
////////////////////////////////////////////////////////////////////////////////

template <typename T>
basic_arg<T>::basic_arg(arg_type_e arg_type,
                    const std::string name,
                    const std::string cmd_desc,
                    const std::string desc,
                    storage_type & store)
    : arg_option(arg_type, name, cmd_desc, desc),
      m_val(store)
      
{
   m_transformer = detail::get_tranformer<value_type>(arg_type);
}

template <typename T>
void
basic_arg<T>::transformer(transformer_type & t)
{
    m_transformer = t;
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
basic_arg<T>::has_implicit_value() const
{
    return ((bool)m_implicit);
}

template <typename T>
void
basic_arg<T>::apply_implicit_value()
{
    detail::assigner<storage_type, storage_type>::assign(*m_implicit, m_val);
}
    
template <typename T>
void 
basic_arg<T>::apply_value(const std::string & s)
{
    detail::assigner<value_type, storage_type>::
        assign(m_transformer(s), m_val);

}
    
/* error checking should be done in parser,
 * we assume that the token already matches the
 * option description */
template <typename T>
void
basic_arg<T>::notify(const arg_token & tk)
{
    try {
        if (arg_type() == arg_type_e::positional) {
            apply_value(tk.value());
        }
        else if (arg_type() == arg_type_e::option) {
            if (tk.has_assign())
                apply_value(tk.value());
            else
                apply_implicit_value();
        } 
        else if (arg_type() == arg_type_e::flag) {
            if (has_implicit_value())
                apply_implicit_value();
            else
                apply_value("");
        }
    /* transformation exceptions could occur, including 
     * lexical_cast_exception and enum_cast_exception,
     * rethrow as a invalid_arg_error */
    } catch (...) {
        std::string msg = "transformation failed for token '";
        msg += tk.raw_arg() + "'";
        throw invalid_arg_error(msg);
    }
        
        m_count++;
}


////////////////////////////////////////////////////////////////////////////////
//                            typed_arg                                              
////////////////////////////////////////////////////////////////////////////////
    
    
template <typename T>
typed_arg<T>::typed_arg(arg_type_e arg_type,
              const std::string & name,
              const std::string & cmd_desc,
              const std::string & desc)
    : basic_arg_type(arg_type, name, cmd_desc, desc, value), 
      value{}
{
}

template <typename T>
template <typename... Args>
typed_arg<T>::typed_arg(arg_type_e arg_type,
                const std::string & name,
                const std::string & cmd_desc,
                const std::string & desc,
                Args&&... args)
    : basic_arg_type(arg_type, name, cmd_desc, desc, value), 
      value{args...}
{
}


////////////////////////////////////////////////////////////////////////////////
//                             tagged_arg                                           
////////////////////////////////////////////////////////////////////////////////

template <typename Tag>
tagged_arg<Tag>::tagged_arg()
    : basic_arg_type(tag_type::arg_type,
                     tag_type::cmd,
                     tag_type::cmd_desc,
                     tag_type::desc,
                     tag_type::value)
    
{
}

    
    
} /* namespace argp */
} /* namespace elib */
#endif /* ELIB_ARGP__ARG_HPP */