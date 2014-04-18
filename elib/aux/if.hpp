#ifndef ELIB_AUX_IF_HPP
#define ELIB_AUX_IF_HPP

# include <elib/aux/integral_constant.hpp>
# include <elib/aux/no_decay.hpp>
# include <elib/aux/none.hpp>
# include <elib/aux/traits/conditional.hpp>

namespace elib { namespace aux
{
    namespace detail
    {
        template <class T>
        struct conditional_branch_eval
        {
            using type = typename T::then;
        };

        template <class Cond, class Then>
        struct conditional_branch
        {
            using condition = Cond;
            using then = Then;
        };

        template <class ...Branches>
        struct conditional_evalute;

        template <class First, class ...Rest>
        struct conditional_evalute< First,  Rest...>
          : aux::conditional_t<
                First::condition::type::value
              , conditional_branch_eval< First >
              , conditional_evalute<Rest...>
            >
        {};

        template <class ...Branches>
        class conditional_accumulate 
        {
            template <class Cond, class Then, class Else = aux::none>
            struct make_else_if
              : no_decay<
                  conditional_evalute<
                      Branches...
                    , conditional_branch<Cond, Then>
                    , conditional_branch<true_, Else>
                    >
                >
            {};

            template <class Cond, class Then>
            struct make_else_if<Cond, Then>
              : no_decay<
                    conditional_accumulate<
                        Branches..., conditional_branch<Cond, Then>
                    >
                >
            {};

        public:

            template <class Cond, class Then, class Else = aux::none>
            using else_if = typename make_else_if<Cond, Then, Else>::type;

            template <bool Cond, class Then, class Else = aux::none>
            using else_if_c = typename make_else_if<bool_<Cond>, Then, Else>::type;

            template <class Else>
            using else_ = 
                conditional_evalute<
                    Branches...
                  , conditional_branch<true_, Else>
                  >;
        };
    }                                                   // namespace detail


    template <
        class Cond
      , class Then = aux::none
      , class Else = aux::none
      >
    struct if_;
    
    template <class Cond, class Then, class Else>
    struct if_
      : detail::conditional_accumulate<>::template 
          else_if<Cond, Then, Else>
    {};

    template <class Cond>
    struct if_<Cond>
      : if_<
            Cond
          , aux::no_decay<void>
          , aux::none
          >
    {};

    template <class Cond, class Then>
    struct if_<Cond, Then>
      : detail::conditional_accumulate<>::template else_if<Cond, Then>
    {};

    template <
        class Cond
      , class Then = aux::none
      , class Else = aux::none
      >
    using if_t = typename if_<Cond, Then, Else>::type;


    template <
        bool Cond
      , class Then = aux::none
      , class Else = aux::none
      >
    using if_c = if_<bool_<Cond>, Then, Else>;


    template <
        bool Cond
      , class Then = aux::none
      , class Else = aux::none
      >
    using if_c_t = typename if_<integral_constant<Cond>, Then, Else>::type;


    ////////////////////////////////////////////////////////////////////////////
    // aux::eval_if
    template <class Pred, class Then, class Else>
    struct eval_if
    {
        using type = typename if_t<Pred, Then, Else>::type;
    };
        
    ////////////////////////////////////////////////////////////////////////////
    // aux::eval_if_t
    template <class Pred, class Then, class Else>
    using eval_if_t = typename if_t<Pred, Then, Else>::type;
        
    ////////////////////////////////////////////////////////////////////////////
    // aux::eval_if_c
    template <bool Pred, class Then, class Else>
    struct eval_if_c
    {
        using type = typename if_c_t<Pred, Then, Else>::type;
    };
        
    ////////////////////////////////////////////////////////////////////////////
    // aux::eval_if_c_t
    template <bool Pred, class Then, class Else>
    using eval_if_c_t = typename if_c_t<Pred, Then, Else>::type;

}}                                                          // namespace elib
namespace elib
{
    using aux::if_;
    using aux::if_t;
    using aux::if_c;
    using aux::if_c_t;
    
    using aux::eval_if;
    using aux::eval_if_t;
    using aux::eval_if_c;
    using aux::eval_if_c_t;
}                                                           // namespace elib
#endif /* ELIB_AUX_IF_HPP */