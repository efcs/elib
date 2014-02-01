#ifndef ELIB_LOG_ELOG_HPP
#define ELIB_LOG_ELOG_HPP

# include <elib/log/static_log.hpp>

namespace elib { namespace log 
{      
    struct elog_tag_t {};
    
    using elog = static_log<elog_tag_t>;

}}                                                          // namespace elib
#endif /* ELIB_LOG_ELOG_HPP */