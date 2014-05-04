#ifndef ELIB_ITERATOR_ALGORITHM_HPP
#define ELIB_ITERATOR_ALGORITHM_HPP

# include <elib/iterator/traits.hpp>
# include <elib/aux.hpp>
# include <algorithm>
# include <iterator>

namespace elib { namespace iter
{
    namespace detail
    {
        template <
            class Integral
          , ELIB_ENABLE_IF(aux::is_signed<Integral>::value)
          >
        constexpr Integral abs(Integral i) noexcept
        {
            return i < 0 ? -i : i;
        }
        
        template <
            class Integral
          , ELIB_ENABLE_IF(aux::is_unsigned<Integral>::value)
          >
        constexpr Integral abs(Integral i) noexcept
        {
            return i;
        }
        
        template <class Iterator, class Difference>
        Difference advance_upto_impl(
            Iterator & it, Difference n, Iterator limit
          , std::forward_iterator_tag
          )
        {
            if (n < 0) return;
            while (n > 0 && it != limit) {
                ++it;
                --n;
            }
            return n;
        }
        
        template <class Iterator, class Difference>
        Difference advance_upto_impl(
            Iterator & it, Difference n, Iterator limit
          , std::bidirectional_iterator_tag
          )
        {
            if (n > 0) {
                while (n > 0 && it != limit) {
                    ++it;
                    --n;
                }
            }
            else if (n < 0) {
                while (n < 0 && it != limit) {
                    --it;
                    ++n;
                }
            }
            return n;
        }
        
        template <class Iterator, class Difference>
        Difference advance_upto_impl(
            Iterator & it, Difference n, Iterator limit
          , std::random_access_iterator_tag
          )
        {
           Difference dist = limit - it;
           
           if (dist > 0) {
                ELIB_ASSERT(n >= 0);
           }
           else if (dist < 0) {
                ELIB_ASSERT(n <= 0);
           }
           
           if (detail::abs(dist) > detail::abs(n)) {
                it += n;
                return 0;
           }
           else {
                it = limit;
                return n - dist;
           }
        }
        
    }                                                       // namespace detail
    
    namespace adl_barrier
    {
        template <class Iterator, class Difference>
        auto advance_upto(
            Iterator it, Difference n, Iterator limit
        )
        ELIB_AUTO_RETURN_NOEXCEPT(
            detail::advance_upto_impl(it, n, limit, iterator_category_t<Iterator>{})
        )
    }                                                  // namespace adl_barrier
    
    using adl_barrier::advance_upto;
    
    namespace detail
    {
        template <class Iterator>
        constexpr auto size_impl(
            Iterator begin, Iterator end
          , std::forward_iterator_tag
          ) -> decltype(std::distance(begin, end))
        {
            return std::distance(begin, end);
        }
        
        template <class Iterator>
        constexpr auto size_impl(
            Iterator begin, Iterator end
          , std::random_access_iterator_tag
          ) -> decltype( end - begin )
        {
            return end - begin;
        }
    }                                                       // namespace detail

    namespace adl_barrier
    {
        template <class Iterator>
        constexpr auto size(Iterator xbegin, Iterator xend)
        ELIB_AUTO_RETURN_NOEXCEPT( 
            detail::size_impl(xbegin, xend, iterator_category_t<Iterator>{})
        )
        
        template <class Iterator>
        constexpr auto distance(Iterator xbegin, Iterator xend)
        ELIB_AUTO_RETURN_NOEXCEPT(
            detail::size_impl(xbegin, xend, iterator_category_t<Iterator>{})
        )
    }                                                  // namespace adl_barrier
    
    using adl_barrier::size;
    using adl_barrier::distance;
    
}}                                                          // namespace elib
#endif /* ELIB_ITERATOR_ALGORITHM_HPP */