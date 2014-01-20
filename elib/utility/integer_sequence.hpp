#ifndef ELIB_UTILITY_INTEGER_SEQUENCE_HPP
#define ELIB_UTILITY_INTEGER_SEQUENCE_HPP

# include <cstddef>

namespace elib 
{
    namespace utility
    {
        
        template<class T, T ...Seq> 
        struct integer_sequence
        {
            using type = integer_sequence;
            
            using value_type = T;
            
            static constexpr T size = sizeof...(Seq);

            using next = integer_sequence<T, Seq..., sizeof...(Seq)>;
        };

        template<int... I>
        using int_sequence = integer_sequence<int, I...>;
        
        template<size_t... I>
        using index_sequence = integer_sequence<std::size_t, I...>;

        namespace detail
        {
            ////////////////////////////////////////////////////////////////////
            //
            template <class LHS, class RHS>
            struct integer_seq_join;
           
            template <class T, T ...Vs0, T ...Vs1>
            struct integer_seq_join<
                integer_sequence<T, Vs0...>
              , integer_sequence<T, Vs1...>
            >
            {
                using type = integer_sequence<T, Vs0..., (Vs1 + sizeof...(Vs0))...>;
            };
           
            //////////////////////////////////////////////////////////////////////
            //
            template <class T, std::size_t N>
            struct integer_seq_impl
              : integer_seq_join<
                    typename integer_seq_impl<T, (N / 2)>::type
                  , typename integer_seq_impl<T, (N - (N/2))>::type
                >
            {};
            
            template <class T>
            struct integer_seq_impl<T, 0>
            {
                using type = integer_sequence<T>;
            };
            
            template <class T>
            struct integer_seq_impl<T, 1>
            {
                using type = integer_sequence<T, 0>;
            };
        }                                                   // namespace detail
        
        ////////////////////////////////////////////////////////////////////////
        //
        template<class T, T N>
        using make_integer_sequence = typename 
            detail::integer_seq_impl<
                T
              , static_cast<std::size_t>(N)
            >::type;

        template<int N>
        using make_int_sequence = make_integer_sequence<int, N>;

        template<size_t N>
        using make_index_sequence = make_integer_sequence<std::size_t, N>;

        ////////////////////////////////////////////////////////////////////////
        //
        template<class... T>
        using to_int_sequence = make_int_sequence<sizeof...(T)>;

        template<class... T>
        using to_index_sequence = make_index_sequence<sizeof...(T)>;
    }                                                       // namespace utility
}                                                           // namespace elib
#endif /* ELIB_UTILITY_INTEGER_SEQUENCE_HPP */