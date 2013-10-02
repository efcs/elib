#ifndef ELIB_ENUMERATION_ENUM_ADAPTER_HPP
# define ELIB_ENUMERATION_ENUM_ADAPTER_HPP

# include <elib/config.hpp>
# include <elib/enumeration/v2/enum_fields.hpp>
# include <elib/enumeration/v2/enum_traits.hpp>
# include <elib/enumeration/v2/enum_cast.hpp>

# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace enumeration
  {
    
    
    template <typename EnumT>
    class basic_enum_adapter
    {
      static_assert(std::is_enum<EnumT>::value, 
          "EnumT must be an enumeration type");
          
      //
    public:
      //
      
      // typedefs
      typedef EnumT enum_type;
      typedef std::underlying_type_t<EnumT> value_type;
      
      // Ctors & Dtors
      constexpr basic_enum_adapter() noexcept = default;
      
      constexpr explicit basic_enum_adapter(enum_type val) noexcept
        : m_val{val}
      { }
      
      constexpr explicit basic_enum_adapter(value_type val) noexcept
        : m_val{static_cast<enum_type>(val)}
      { }
      
      constexpr basic_enum_adapter(const basic_enum_adapter&) noexcept = default;
      constexpr basic_enum_adapter(basic_enum_adapter&&) noexcept = default;
      
      basic_enum_adapter& operator=(const basic_enum_adapter&) noexcept = default;
      basic_enum_adapter& operator=(basic_enum_adapter&&) noexcept = default;
      
      ~basic_enum_adapter() noexcept = default;
      
      
      // Assignments
      basic_enum_adapter& operator=(enum_type e) noexcept
      {
        m_val = e;
        return *this;
      }
      
      basic_enum_adapter& operator=(value_type v) noexcept
      {
        m_val = static_cast<enum_type>(v);
        return *this;
      }
      
      // Observers
      const enum_type& get() const noexcept
      { return m_val; }
      
      enum_type& get() noexcept
      { return m_val; }
      
      
      // costexpr observers
      constexpr enum_type& operator*() noexcept
      { return m_val; }
      
      constexpr enum_type enum_value() noexcept
      { return m_val; }
      
      constexpr value_type value() noexcept
      { return static_cast<value_type>(m_val); }
      
      constexpr bool good() noexcept
      { return static_cast<bool>(m_val); }
      
      // Cast operators
      constexpr operator enum_type() noexcept
      { return m_val; }
      
      // For safe-bool
      constexpr operator bool() noexcept
      {
        return good();
      }
      
      // Comparision
      // to make it a constexpr function
      // add -(less_than) and (greater_than)
      constexpr int compare(enum_type e) noexcept
      {
        return (-static_cast<int>(m_val < e) +
                static_cast<int>(m_val > e));
      }
      
      constexpr int compare(value_type v) noexcept
      {
        return compare(static_cast<enum_type>(v));
      }
      
      constexpr int compare(const basic_enum_adapter& e) noexcept
      {
        return compare(e.get());
      }
      
      //
    private:
      //
      
      enum_type m_val;
      
    };                                              // class basic_enum_adapter
    
    ////////////////////////////////////////////////////////////////////////////////
    //                   BASIC_ENUM_ADAPTER COMPARISON FUNCTIONS                                                        
    ////////////////////////////////////////////////////////////////////////////////
    
    namespace detail
    {
      
      template <typename EnumT, typename T, typename=void>
      struct adapter_is_comparible : public std::false_type
      { };
      
      
      template <typename EnumT, typename T>
      struct adapter_is_comparible<EnumT, T, enable_if_enum_t<EnumT>>
        : public std::integral_constant<bool, 
            std::is_same<EnumT, T>::value
            || std::is_integral<T>::value
            || std::is_base_of<basic_enum_adapter<EnumT>, T>::value>
      { };
      
      template <typename EnumT, typename U, typename Ret=void>
      using enable_if_comparible_t =
          std::enable_if_t<adapter_is_comparible<EnumT, U>::value, Ret>;
      
    }                                                       // namespace detail
    
    // LHS comparisions
    template <typename EnumT, typename U>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator==(const basic_enum_adapter<EnumT>& lhs, const U& rhs) noexcept
    {
      return lhs.compare(rhs) == 0;
    }
    
    template <typename EnumT, typename U>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator!=(const basic_enum_adapter<EnumT>& lhs, const U& rhs) noexcept
    {
      return lhs.compare(rhs) != 0;
    }
    
    template <typename EnumT, typename U>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator<(const basic_enum_adapter<EnumT>& lhs, const U& rhs) noexcept
    {
      return lhs.compare(rhs) < 0;
    }
    
    template <typename EnumT, typename U>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator<=(const basic_enum_adapter<EnumT>& lhs, const U& rhs) noexcept
    {
      return lhs.compare(rhs) <= 0;
    }
    
    template <typename EnumT, typename U>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator>(const basic_enum_adapter<EnumT>& lhs, const U& rhs) noexcept
    {
      return lhs.compare(rhs) > 0;
    }
    
    template <typename EnumT, typename U>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator>=(const basic_enum_adapter<EnumT>& lhs, const U& rhs) noexcept
    {
      return lhs.compare(rhs) >= 0;
    }
    
    // RHS comparisions
    template <typename U, typename EnumT>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator==(const U& lhs, const basic_enum_adapter<EnumT>& rhs)
    {
      return rhs == lhs;
    }
    
    template <typename U, typename EnumT>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator!=(const U& lhs, const basic_enum_adapter<EnumT>& rhs)
    {
      return rhs != lhs;
    }
    
    template <typename U, typename EnumT>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator<(const U& lhs, const basic_enum_adapter<EnumT>& rhs)
    {
      return rhs >= lhs;
    }
    
    template <typename U, typename EnumT>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator<=(const U& lhs, const basic_enum_adapter<EnumT>& rhs)
    {
      return rhs > lhs;
    }
    
    template <typename U, typename EnumT>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator>(const U& lhs, const basic_enum_adapter<EnumT>& rhs)
    {
      return rhs <= lhs;
    }
    
    template <typename U, typename EnumT>
    inline detail::enable_if_comparible_t<EnumT, U, bool>
    operator>=(const U& lhs, const basic_enum_adapter<EnumT>& rhs)
    {
      return rhs < lhs;
    }
    
    
  ////////////////////////////////////////////////////////////////////////////////
  //                        bitwise_enum_adapter                                               
  ////////////////////////////////////////////////////////////////////////////////

    template <typename T, >
    static 
    
  }                                                         // namespace enumeration
}                                                           // namespace elib
#endif /* ELIB_ENUMERATION_ENUM_ADAPTER_HPP */