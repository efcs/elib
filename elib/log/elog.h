#ifndef ELIB_LOG_ELOG_H
#define ELIB_LOG_ELOG_H


#include "static_log.h"


namespace elib {
namespace log {
    

struct elog_tag_t {};


typedef static_log<elog_tag_t> elog;

    
} /* namespace log */
} /* namespace elib */
#endif /* ELIB_LOG_ELOG_H */