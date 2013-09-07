#ifndef ELIB_ARGP_ARG_H
#define ELIB_ARGP_ARG_H

#include <elib/argp/detail/_arg_option.h>
#include <elib/argp/arg_token.h>
#include <elib/argp/arg_errors.h>


#include <elib/enumeration/enum_traits.h>
#include <elib/enumeration/enum_cast.h>
#include <elib/utility/lexical_cast.h>
#include <elib/utility/fmt.h>

#include <vector>
#include <string>
#include <functional>
#include <type_traits>
#include <memory>
#include <stdexcept>

namespace elib {
namespace argp {
    
    
typedef std::function<void(const arg_token&)> option_callback;


/* the type of arg,
 * flags: [-c|--STRING]
 * option: [-cArg|--STRING=ARG] (flag syntax is allowed 
 *                               when there is an implicit value)
 * positional: an non-option argument */
enum class arg_type_e {
    positional,
    flag,
    option,
};


bool prefix_is_long_name(const std::string & s);
bool prefix_is_short_name(const std::string & s);


bool is_valid_arg_name(const std::string &s);
bool is_valid_short_name(const std::string & s);
bool is_valid_long_name(const std::string & s);
    

/* arg_value_traits deduces if an argument is a list, or another type */
template <typename T>
struct arg_value_traits {
    /* value_type is the actual type of value that should be stored */
    typedef T value_type;
    /* storage_type is how we store that value */
    typedef T storage_type;
};

/* specialization for when we have a list */
template <typename T>
struct arg_value_traits<std::vector<T>> {
    typedef T value_type;
    /* we are storing a vector on items */
    typedef std::vector<T> storage_type;
};



/* user-front end: create arguments and add them to a parser
 * to generate rules to parse the options, create a help message,
 * and link the options to their storage */
template <typename ArgT>
class basic_arg : public detail::arg_option {
public:
    /* use traits to seperate value_type and containor
     * information */
    typedef arg_value_traits<ArgT> traits;
    
    /* the type that the string arguement is going to be 
     * transformed into */
    typedef typename traits::value_type value_type;
    
    /* the type that actually stores the value,
     * possible values: 
     *    value_type
     *    std::vector<value_type> */
    typedef typename traits::storage_type storage_type;
    
    /* this is called to transform s -> value_type */
    typedef std::function<value_type(const std::string&)> transformer_type;
    
    /*
     * [arg_type] an enumeration for the type of flag to be parsed 
     *            it is used by the parser to determine how to parse the arg
     *            and if an error has occured
     * 
     *      flag: takes NO value
     *      option: takes a value
     *      option_list: takes a comma seperated list of values
     *      positional: not an command line option
     * 
     * [name] a raw formated name for the option.
     *        it contains either a long-name, a short-name, or both.
     *        if both, they are seperated by a comma.
     *      short-name:
     *          -[a-Z] a '-' sign followed by one alphabetic character
     *      long-name:
     *          --[a-Z][a-Z0-9_\-] two '--' signs followed by an identifier,
     *          the identifier must start with a digit 
     *      raw formatted name:
     *          a raw formatted can be "" if and only if arg_type is positional
     *          examples "-c,--C", "--warning,-W", "-v", "--help"
     * 
     * [cmd_desc] used in the summary of the invokation of the program 
     *            examples "[-c,--C]", "[--warning=warn]", "--level=l"
     * 
     * [desc]     the long description of the flag
     * 
     * [store]  when an option is parsed, it will be written to store 
     * 
     * [transformer_type] a function std::string -> value_type 
     *        when not specified it can either be:
     *           std::forward<value_type> when std::string
     *           lexical_cast<value_type> otherwise
     *        suggested use with enum_cast(std::string) if you want
     *        to parse an enumeration value 
     *                     
     */
    basic_arg(arg_type_e arg_type,
              const std::string name,
              const std::string cmd_desc,
              const std::string desc,
              storage_type & store);
    
    virtual ~basic_arg() { }
    
    /* change the transformer */
    void
    transformer(transformer_type & t);
    
    /* give the arguement an implicit value,
     * arg_type cannot be positional,
     * if arg_type is flag then the implicit value will
     * be applied every time the flag is found */
    void
    implicit_value(const storage_type & v);
    
    bool
    has_implicit_value() const;
    
    /* apply implicit_value to the variable */
    void
    apply_implicit_value();
    
    /* apply a string to the variable */
    void 
    apply_value(const std::string & s);
    
    /* entry point to apply value,
     * determine how to apply value,
     * and increment count */
    void notify(const arg_token & tk);
    
private:
    /* pointer to value storage */
    storage_type & m_val;
    /* the number of times a value has been applied */
    unsigned m_count{0};
    /* storage for implicit value, no implicit value if nullptr */
    std::shared_ptr<storage_type> m_implicit{nullptr};
    /* a function to tranform a string, into the value that we are storing,
     * when not specified it defaults to a 
     * special flag tranformer when we are a flag, and storing a bool.
     * enum_cast_string<value_type> when e is type is an enum 
     * otherwise it is a lexical_cast to value_type */
    transformer_type m_transformer;
};


////////////////////////////////////////////////////////////////////////////////
//                           typed arg                                               
////////////////////////////////////////////////////////////////////////////////


template <typename T>
class typed_arg : public basic_arg<T> {
public:
    typedef basic_arg<T> basic_arg_type;
    typedef typename basic_arg_type::value_type value_type;
    typedef typename basic_arg_type::storage_type storage_type;
    
    typed_arg(arg_type_e arg_type,
              const std::string & name,
              const std::string & cmd_desc,
              const std::string & desc);

    template <typename... Args>
    typed_arg(arg_type_e arg_type,
              const std::string & name,
              const std::string & cmd_desc,
              const std::string & desc,
              Args&&... args);
    
    ~typed_arg() { }
    
    storage_type value;
};


////////////////////////////////////////////////////////////////////////////////
//                           tagged arg                                                
////////////////////////////////////////////////////////////////////////////////


/* don't polute namespace with example */
namespace detail {
    
    
/* this is an example template for an arg tag
 * the type of value may be anything */
struct arg_tag {    
    static decltype(nullptr) value;
    
    /* can be const, or constexpr */
    static constexpr arg_type_e arg_type = arg_type_e::flag;
    static constexpr char cmd[] = "";
    static constexpr char cmd_desc[] = "";
    static constexpr char desc[] = "";
};

} /* namespace detail */


/* this is what uses struct tags */
template <typename Tag>
class tagged_arg : public basic_arg<decltype(Tag::value)> {
public:
    typedef Tag tag_type;
    typedef basic_arg<decltype(tag_type::value)> basic_arg_type;
    
    tagged_arg();
    ~tagged_arg() { }
};

    
} /* namespace argp */
} /* namespace elib */


#include "detail/_arg.h"


#endif /* ELIB_ARGP_ARG_H */