#ifndef ELIB_ELOG_H
#define ELIB_ELOG_H


#include "static_log.h"


namespace elib {
    

struct elog_tag_t {};


typedef static_log<elog_tag_t> elog;

    
} /* namespace elib */
#endif /* ELIB_ELOG_H */