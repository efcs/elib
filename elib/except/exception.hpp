#ifndef ELIB_EXCEPT_EXCEPTION_HPP
#define ELIB_EXCEPT_EXCEPTION_HPP

# include <elib/except/fwd.hpp>
# include <elib/except/error_info.hpp>
# include <elib/aux.hpp>
# include <elib/any.hpp>
# include <exception>
# include <stdexcept>
# include <memory>
# include <string>
# include <typeindex>
# include <typeinfo>
# include <unordered_map>
# include <utility>

# define ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(Ex)                      \
    static_assert(                                                  \
      ::elib::except::is_exception<::elib::aux::uncvref<Ex>>::value \
      , #Ex " is not an exception type"                             \
    )

namespace elib { namespace except
{
# if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wweak-vtables"
# endif
    class exception : public std::exception
    {
    public:
        exception(std::string const & what_arg)
          : m_impl(std::make_shared<exception_storage>(what_arg))
        {
        }
        
        exception(const char* what_arg)
          : m_impl(std::make_shared<exception_storage>(what_arg))
        {
        }
        
        ELIB_DEFAULT_COPY_MOVE(exception);
        
        virtual const char* what() const noexcept 
        { 
            if (m_impl->m_fmt == "")
            {
                m_impl->m_fmt = m_impl->m_what_arg;
                if (has_throw_info())
                    m_impl->m_fmt += ("\n  Thrown from " + throw_info_str());
            }

            return m_impl->m_fmt.c_str();
        }   
        
        virtual ~exception() = default;

    public:
        bool has_throw_info() const
        {
            return this->has_error_info<throw_func>()
                && this->has_error_info<throw_file>()
                && this->has_error_info<throw_line>();
        }
        
        std::string throw_info_str() const
        {
            std::string s;
            if (!has_throw_info()) return s;
            
            s = get_error_info<throw_file>()->value();
            s += "::" 
              + std::to_string( get_error_info<throw_line>()->value() );
            s += " in function ";
            s += get_error_info<throw_func>()->value();
            
            return s;
        }
        
        template <class ErrorInfo>
        bool has_error_info() const
        {
            ELIB_EXCEPT_ASSERT_ERROR_INFO_TYPE(ErrorInfo);
            
            auto pos = m_impl->m_info_map.find(std::type_index(typeid(ErrorInfo)));
            return (pos != m_impl->m_info_map.end());
        }
        
        template <class ErrorInfo, class ...Args>
        bool emplace_error_info(Args &&... args)
        {
            ELIB_EXCEPT_ASSERT_ERROR_INFO_TYPE(ErrorInfo);
            
            return m_impl->m_info_map.emplace(
                std::make_pair(
                    std::type_index(typeid(ErrorInfo))
                  , elib::any(ErrorInfo(elib::forward<Args>(args)...))
            )).second;
        }
        
        template <class ErrorInfo>
        bool insert_error_info(ErrorInfo && e)
        {
            ELIB_EXCEPT_ASSERT_ERROR_INFO_TYPE(ErrorInfo);
            
            return m_impl->m_info_map.insert(
                std::make_pair(
                    std::type_index(typeid(ErrorInfo))
                  , elib::any(elib::forward<ErrorInfo>(e))
            )).second;
        }
        
        template <class ErrorInfo>
        void set_error_info(ErrorInfo && e)
        {
            ELIB_EXCEPT_ASSERT_ERROR_INFO_TYPE(ErrorInfo);
            
            m_impl->m_info_map[std::type_index(typeid(ErrorInfo))] = 
                elib::forward<ErrorInfo>(e);
        }

        template <class ErrorInfo>
        ErrorInfo const * get_error_info() const
        {
            return const_cast<exception &>(*this).template get_error_info<ErrorInfo>();
        }
        
        template <class ErrorInfo>
        ErrorInfo* get_error_info()
        {
            ELIB_EXCEPT_ASSERT_ERROR_INFO_TYPE(ErrorInfo);
            
            auto pos = m_impl->m_info_map.find(std::type_index(typeid(ErrorInfo)));
            if (pos == m_impl->m_info_map.end()) return nullptr;
            return elib::addressof(
                any_cast<ErrorInfo &>(pos->second)
            );
        }
        
    private:
        struct exception_storage
        {
            exception_storage(std::string what_arg)
              : m_what_arg(what_arg)
            {}
            
            std::string m_what_arg;
            mutable std::string m_fmt;
            std::unordered_map<std::type_index, elib::any> m_info_map;
        };
        
        std::shared_ptr<exception_storage> m_impl;
    };
    
# if defined(__clang__)
#   pragma clang diagnostic pop
# endif

    ////////////////////////////////////////////////////////////////////////////
    //
    template <class T>
    struct is_exception : aux::is_base_of<exception, aux::uncvref<T>> {};
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class ErrorInfo, class E>
    bool has_error_info(E const & e)
    {
        ELIB_EXCEPT_ASSERT_ERROR_INFO_TYPE(ErrorInfo);
        ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(E);
        
        return e.template has_error_info<ErrorInfo>();
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class E, class Tag, class T>
    bool insert_error_info(E & e, error_info<Tag, T> const & i)
    {
        ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(E);
        return e.insert_error_info(i);
    }
    
    template <class E, class Tag, class T>
    bool insert_error_info(E & e, error_info<Tag, T> && i)
    {
        ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(E);
        return e.insert_error_info(elib::move(i));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class ErrorInfo, class E, class ...Args>
    bool emplace_error_info(E & e, Args &&... args)
    {
        ELIB_EXCEPT_ASSERT_ERROR_INFO_TYPE(ErrorInfo);
        ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(E);
        
        return 
        e.template emplace_error_info<ErrorInfo>(elib::forward<Args>(args)...);
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class E, class Tag, class T>
    void set_error_info(E & e, error_info<Tag, T> const & i)
    {
        ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(E);
        e.set_error_info(i);
    }
    
    template <class E, class Tag, class T>
    void set_error_info(E & e, error_info<Tag, T> && i)
    {
        ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(E);
        e.set_error_info(elib::move(i));
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class ErrorInfo, class E>
    ErrorInfo const & get_error_info(E const & e)
    {
        // all logic in non-const version is const so const_cast is safe.
        return get_error_info<ErrorInfo>(const_cast<E &>(e));
    }
    
    template <class ErrorInfo, class E>
    ErrorInfo & get_error_info(E & e)
    {
        ELIB_EXCEPT_ASSERT_ERROR_INFO_TYPE(ErrorInfo);
        ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(E);
        
        auto ptr = e.template get_error_info<ErrorInfo>();
        if (!ptr) throw std::logic_error("No such error info");
        return *ptr;
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class ErrorInfo, class E>
    typename ErrorInfo::error_info::value_type &
    get_error_info_value(E & e)
    {
        return get_error_info<ErrorInfo>(e).value();
    }
    
    template <class ErrorInfo, class E>
    typename ErrorInfo::error_info::value_type const & 
    get_error_info_value(E const & e)
    {
        return get_error_info<ErrorInfo>(e).value();
    }
    
    ////////////////////////////////////////////////////////////////////////////
    //
    template <class E, class Tag, class T>
    E & operator<<(E & e, error_info<Tag, T> const & i)
    {
        ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(E);
        
        e.set_error_info(i);
        return e;
    }
    
    template <class E, class Tag, class T>
    E & operator<<(E & e, error_info<Tag, T> && i)
    {
        ELIB_EXCEPT_ASSERT_EXCEPTION_TYPE(E);
        
        e.set_error_info(elib::move(i));
        return e;
    }
    
    //template <class E, class ...Tags, class ...Types>
    //E & operator<<(E const &, elib::tuple<error_info<Tags, Types>...> const &);
}}                                                          // namespace elib
#endif /* ELIB_EXCEPT_EXCEPTION_HPP */