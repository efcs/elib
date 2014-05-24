#ifndef ELIB_LEXICAL_CAST_HPP
#define ELIB_LEXICAL_CAST_HPP

# include <elib/aux.hpp>
# include <stdexcept>
# include <string>
# include <sstream>

namespace elib 
{
    
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    /* bad_cast error for lexical casts */
    class bad_lexical_cast : public std::runtime_error 
    {
    public:
        explicit bad_lexical_cast(const char *what_arg)
          : std::runtime_error(what_arg)
        {}
      
        explicit bad_lexical_cast(std::string const & what_arg)
          : std::runtime_error(what_arg)
        {}
        
        bad_lexical_cast(bad_lexical_cast const &) = default;
        bad_lexical_cast(bad_lexical_cast &&) = default;
        bad_lexical_cast & operator=(bad_lexical_cast const &) = default;
        bad_lexical_cast & operator=(bad_lexical_cast &&) = default;
        
        virtual ~bad_lexical_cast() noexcept {}
  };
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

    
    namespace lexical_cast_detail
    {
        template<
            class ToType, class FromType
          , bool ToInt      = aux::is_integral<ToType>::value
          , bool ToFloat    = aux::is_floating_point<ToType>::value
          , bool ToString   = aux::is_same<ToType, std::string>::value
          , bool ToBool     = aux::is_same<ToType, bool>::value
          , bool FromInt    = aux::is_integral<FromType>::value
          , bool FromFloat  = aux::is_floating_point<FromType>::value
          , bool FromString = aux::is_string_type<FromType>::value
        >
        struct cast_type
        {
            using BadCastType = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        ////////////////////////////////////////////////////////////////////////
        //To Int
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , true /* ToInt */, false, false, false
          , true /* FromInt */, false, false
        >
        {
            using IntToInt = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , true /* ToInt */, false, false, false
          , false, true /* FromFloat */, false
        >
        {
            using FloatToInt = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , true /* ToInt */, false, false, false
          , false, false, true /* FromString */
        >
        {
            using StringToInt = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        ////////////////////////////////////////////////////////////////////////
        // ToFloat
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , false, true /* ToFloat */, false, false
          , true /* FromInt */, false, false
        >
        {
            using IntToFloat = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , false, true /* ToFloat */, false, false
          , false, true /* FromFloat */, false
        >
        {
            using FloatToFloat = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , false, true /* ToFloat */, false, false
          , false, false, true /* FromString */
        >
        {
            using StringToFloat = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        ////////////////////////////////////////////////////////////////////////
        // To String
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , false, false, true /* ToString */, false
          , true /* FromInt */, false, false
        >
        {
            using IntToString = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , false, false, true /* ToString */, false
          , false, true /* FromFloat */, false
        >
        {
            using FloatToString = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , false, false, true /* ToString */, false
          , false, false, true /* FromString */
        >
        {
            using StringToString = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        ////////////////////////////////////////////////////////////////////////
        // ToBool
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , true, false, false, true /* ToBool */
          , true /* FromInt */, false, false
        >
        {
            using IntToBool = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , true, false, false, true /* ToBool */
          , false, true /* FromFloat */, false
        >
        {
            using FloatToBool = ToType;
            using To = ToType;
            using From = FromType;
        };
        
        template <class ToType, class FromType>
        struct cast_type<
            ToType, FromType
          , true, false, false, true /* ToBool */
          , false, false, true /* FromString */
        >
        {
            using StringToBool = ToType;
            using To = ToType;
            using From = FromType;
        };
     
        template <class To, class From>
        To from_string_cast(From const & from)
        {
            To t{};
            std::stringstream ss;  
            
            ss << from;
            ss >> t;
            
            if (!ss) 
                throw bad_lexical_cast(
                    std::string{"bad lexical cast from string: \""}
                    + from + "\""
                  );
            
            return t;
        }
        
        template <class To, class From>
        bool from_string_cast(From const & from, To & dest) noexcept
        {
            std::stringstream ss;
            ss << from;
            ss >> dest;
            return bool(ss);
        }
        
        template <class From>
        bool from_string_to_bool_cast(From const & f)
        {
            bool b{};
            std::stringstream ss;
            
            // try reading as "true" or "false"
            ss << std::boolalpha << f;
            ss >> b;
            
            // success on first try
            // input string was "true" or "false"
            if (ss) return b;
        
            // input string was a digit
            ss.clear();
            ss << std::noboolalpha;
            ss >> b;
            if (ss) return b;
                
            throw bad_lexical_cast(
                    std::string{"Bad lexical cast from string to bool: \""}
                        + f + '"'
                );
        }
        
        template <class From>
        bool from_string_to_bool_cast(From const & f, bool & dest) noexcept
        {
            std::stringstream ss;
            ss << std::boolalpha << f;
            ss >> dest;
            if (ss) return true;
                
            ss.clear();
            ss <<  std::noboolalpha;
            ss >> dest;
            
            return bool(ss);
        }
        
        template <class From>
        std::string to_string_cast(From from)
        {
            std::stringstream ss;
            if (aux::is_same<From, bool>::value)
                ss.setf(std::ios_base::boolalpha);
            ss << from;
            return ss.str();
        }
        
        template <class To, class From>
        struct is_valid_lexical_cast_impl
        {
            template <class CastType, class = typename CastType::BadCastType>
            static constexpr bool test(int) noexcept { return false; }
            
            template <class>
            static constexpr bool test(...) noexcept { return true; }
            
            using type = bool_< test<cast_type<To, From>>(0) >;
        };
    }                                                       // namespace detail

    // TODO: rename this. 
    template <class T>
    using is_lexical = 
        aux::or_<
            aux::is_integral<T>
          , aux::is_floating_point<T>
          , aux::is_string_type<T>
          >;
    
    template <class To, class From>
    using is_valid_lexical_cast = typename 
        lexical_cast_detail::is_valid_lexical_cast_impl<To, From>::type;
        
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    constexpr typename lexical_cast_detail::cast_type<To, From>::IntToInt
    lexical_cast(From from) noexcept
    {
        return static_cast<To>(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::IntToInt{}
        )
      >
    inline bool lexical_cast(From from, To & dest) noexcept
    {
        dest = static_cast<To>(from);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    constexpr typename lexical_cast_detail::cast_type<To, From>::FloatToInt
    lexical_cast(From from) noexcept
    {
        return static_cast<To>(from + 0.5f);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::FloatToInt{}
        )
      >
    inline bool lexical_cast(From from, To & dest) noexcept
    {
        dest = static_cast<To>(from + 0.5f);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    inline typename lexical_cast_detail::cast_type<To, From>::StringToInt
    lexical_cast(From const & from) 
    {
        return lexical_cast_detail::from_string_cast<To>(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::StringToInt{}
        )
      >
    inline bool lexical_cast(From const & from, To & to) noexcept
    {
        return lexical_cast_detail::from_string_cast<To>(from, to);
    }
  
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    constexpr typename lexical_cast_detail::cast_type<To, From>::IntToFloat
    lexical_cast(From from) noexcept
    {
        return static_cast<To>(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::IntToFloat{}
        )
      >
    inline bool lexical_cast(From from, To & to) noexcept
    {
        to = static_cast<To>(from);
        return true;
    }

    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    constexpr typename lexical_cast_detail::cast_type<To, From>::FloatToFloat
    lexical_cast(From from) noexcept
    {
        return static_cast<To>(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::FloatToFloat{}
        )
      >
    inline bool lexical_cast(From from, To & to) noexcept
    {
        to = static_cast<To>(from);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    inline typename lexical_cast_detail::cast_type<To, From>::StringToFloat
    lexical_cast(From const & from)
    {
        return lexical_cast_detail::from_string_cast<To>(from);
    }
        
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::StringToFloat{}
        )
      >
    inline bool lexical_cast(From const & from, To & to)
    {
        return lexical_cast_detail::from_string_cast(from, to);
    }
     
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    inline typename lexical_cast_detail::cast_type<To, From>::IntToString
    lexical_cast(From from)
    {
        return lexical_cast_detail::to_string_cast(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::IntToString{}
        )
      >
    inline bool lexical_cast(From from, To & to) noexcept
    {
        to = lexical_cast_detail::to_string_cast(from);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    inline typename lexical_cast_detail::cast_type<To, From>::FloatToString
    lexical_cast(From from)
    {
        return lexical_cast_detail::to_string_cast(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::FloatToString{}
        )
      >
    inline bool lexical_cast(From from, To & to) noexcept
    {
        to = lexical_cast_detail::to_string_cast(from);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    inline typename lexical_cast_detail::cast_type<To, From>::StringToString
    lexical_cast(From const & from)
    {
        return std::string(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::StringToString{}
        )
      >
    inline bool lexical_cast(From const & from, To & to)
    {
        to = std::string(from);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    constexpr typename lexical_cast_detail::cast_type<To, From>::IntToBool
    lexical_cast(From from) noexcept
    {
        return static_cast<bool>(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::IntToBool{}
        )
      >
    inline bool lexical_cast(From from, To & to) noexcept
    {
        to = static_cast<bool>(from);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    constexpr typename lexical_cast_detail::cast_type<To, From>::FloatToBool
    lexical_cast(From from) noexcept
    {
        return static_cast<bool>(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::FloatToBool{}
        )
      >
    inline bool lexical_cast(From from, To & to) noexcept
    {
        to = static_cast<bool>(from);
        return true;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    template <class To, class From>
    inline typename lexical_cast_detail::cast_type<To, From>::StringToBool
    lexical_cast(From const & from)
    {
        return lexical_cast_detail::from_string_to_bool_cast(from);
    }
    
    template <
        class From, class To
      , ELIB_ENABLE_IF_VALID_EXPR(
          typename lexical_cast_detail::cast_type<To, From>::StringToBool{}
        )
      >
    inline bool lexical_cast(From const & from, To & to) noexcept
    {
        return lexical_cast_detail::from_string_to_bool_cast(from, to);
    }
}                                                            // namespace elib
#endif /* ELIB_LEXICAL_CAST_HPP */