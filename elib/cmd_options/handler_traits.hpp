#ifndef ELIB_CMD_OPTIONS_HANDLER_TRAITS_HPP
#define ELIB_CMD_OPTIONS_HANDLER_TRAITS_HPP

namespace elib { namespace cmd_options
{
    namespace detail
    {
        
    }                                                       // namespace detail
    
    template <class Handler>
    struct handler_traits
    {
        using handler = Handler;
        using value_type = typename Handler::value_type;
        
        template <class ...Args>
        static value_type construct(Handler &, Args &&... args );
        
        template <class ...Args>
        static void construct(Handler &, value_type*, Args &&... args);
        
        static void store(Handler &, storage_type &, value_type const &);
        static void store(Handler &, storage_type &, value_type &&);
        
        template <class ...Args>
        static void store_emplace(Handler, storage_type &, Args &&... args);
        
        static value_type parse_and_construct(Handler &, parsed_option const &);
        static void parse_and_store(Handler &, storage_type &, parsed_option const &);
    };
}}                                                          // namespace elib
#endif /* ELIB_CMD_OPTIONS_HANDLER_TRAITS_HPP */