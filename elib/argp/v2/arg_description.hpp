#ifndef ELIB_ARGP_ARG_DESCRIPTION_HPP
# define ELIB_ARGP_ARG_DESCRIPTION_HPP

# include <elib/config.hpp>

# include <elib/argp/v2/argp_error.hpp>

# include <string>
# include <memory>
# include <utility>


namespace elib 
{
  namespace argp
  {
    
    class option_description_parse_error : public logic_error
    {
    public:
      
      option_description_parse_error()
        : option_description_parse_error("option description parse error")
      { }
      
      explicit option_description_parse_error(const char* what_arg)
        : logic_error{what_arg}
        , m_input{std::make_shared<std::string>()}
      { }
      
      explicit option_description_parse_error(std::string what_arg)
        : logic_error{what_arg}
        , m_input{std::make_shared<std::string>()}
      { }
      
      option_description_parse_error(const char* what_arg, std::string xinput)
        : logic_error{what_arg}
        , m_input{std::make_shared<std::string>(std::move(xinput))}
      { }
      
      option_description_parse_error(std::string what_arg, std::string xinput)
        : logic_error{what_arg}
        , m_input{std::make_shared<std::string>(std::move(xinput))}
      { }
      
      
    private:
      
      std::shared_ptr<std::string> m_input{};
      
      
    };                                  // class option_description_parse_error
    
    
    
    
    class option_description
    {
    public:
      
      // short_desc specifies the description for the option
      // see the option-description specification for information on format
      // long_desc is a plain-english description of the option
      // The constructor will throw exceptions, but
      // the class has a trivial destructor so constructor delegation
      // is not needed
      option_description(const std::string& short_desc, 
                         std::string long_desc)
        : m_desc{std::move(long_desc)}
      {
        m_parse_short_desc(short_desc);
      }
      
      // Same as other constructor, but it allows
      // for the option to be given an alternate name
      // ie. if short_desc specifies a short-name, then
      // alt_name may specify a long name
      option_description(const std::string& short_desc, 
                         const std::string& alt_name, 
                         std::string long_desc,
                         option_traits traits = option_traits::none)
        : option_description(short_desc, long_desc, traits)
      {
        m_parse_alt_name(alt_name);
      }
      
      bool positional() const noexcept { return canonical_name().empty(); }
      
      bool required() const noexcept { return !m_optional; }
      bool multiple() const noexcept { return m_multiple; }
      bool has_argument() const noexcept { return m_has_arg; }
      
      bool has_optional_argument() const noexcept
      {
        // when m_optional_arg is true, then m_has_arg must be as well
        ELIB_ASSERT(!m_optional_arg || (m_has_arg && m_optional_arg));
        return m_optional_arg;
      }
      
      bool has_long_name() const noexcept { return !m_long_name.empty(); }
      bool has_short_name() const noexcept { return !m_short_name.empty(); }
      bool has_argument_name() const noexcept { return !m_arg_name.empty(); }

      const std::string& long_name() const noexcept { return m_long_name; }
      const std::string& short_name() const noexcept { return m_short_name; }
      const std::string& argument_name() const noexcept { return m_arg_name; }
      const std::string& description() const noexcept { return m_desc; }
      
      // the canonical name is selected in the following order, 
      // picking the first non-empty value.
      // canonical_name:
      //    long-name
      //    short-name
      //    "" (positional option)
      // NOTE: canonical_name().empty() == is_positional()
      const std::string& canonical_name() const noexcept
      {
        if (has_long_name())
          return long_name();
        
        // either has_short_name() or positional() is true.
        // when has_short_name() is true, then we want to return
        // the short name. When positional is true, m_short_name == "".
        // so in either case we get the proper return value
        return short_name();
      }
      
      //
    private:
      //
      
      // parse the short description and translate it into
      // it's name, and semantic values (ie required, optional, ect)
      void m_parse_short_desc(const std::string& sdesc);
      
      // parse an alternate name. This function throws if
      // the option is positional, OR the alt_name is not a valid
      // short on long name, OR the alt_name specifies a name that is
      // already given (ie a long-name when has_long_name())
      void m_parse_alt_name(const std::string& alt);
      
      
      // m_desc must be declared first because it is a 
      // value that can be initalized in initalization lists
      // it stores the plain-english description of the option
      std::string m_desc{};
      
      // options can have long and short names
      // short names are: -char
      // long names are: --string
      // an option may have none, either, or both.
      // none denotes a positional arg
      std::string m_long_name{}, m_short_name{};
      
      // a descriptive name provided to describe the argument
      // if an option takes one
      std::string m_arg_name{};
      
      // m_optional represents weither a option is 
      // an non-required option.
      // m_multiple represents weither an option
      // can be given multiple times
      bool m_optional{false}, m_multiple{false};
      
      // m_has_arg represents weither an option accepts
      // a arguement.
      // m_optional_arg specifies weither that argument
      // is optional
      bool m_has_arg{false}, m_optional_arg{false};
      
    };                                              // class option_description
    
    
    /*
     * option_description:
     *   [ <option> ]{...}
     *   <option>{...}
     * 
     * note: case <name> is a positional option
     * option:
     *   <name>
     *   --<name>{<long-option-value>}
     *   -<char>{<short-option-value>}
     * 
     * long-option-value:
     *   [=<name>]
     *   =<name>
     * 
     * short-option-value:
     *  [ <name> ]
     *  <name>
     * 
     * name:
     *  <alpha-char>{<name-rest>}
     * 
     * name_rest:
     *  <name-rest-char>
     *  <name-rest><name-rest-char>
     *  
     * name-rest-char:
     *  <alpha-char>
     *  <digit-char>
     *  "-"
     *  "_"
     * 
     */
    
  }                                                           // namespace argp
}                                                           // namespace elib
#endif /* ELIB_ARGP_ARG_DESCRIPTION_HPP */