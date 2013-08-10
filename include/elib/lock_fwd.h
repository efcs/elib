#ifndef ELIB_LOCK_FWD_H
#define ELIB_LOCK_FWD_H

namespace elib {

class semaphore;
class rw_lock;
class rw_read_lock;
class rw_write_lock;

namespace detail {
    
class semaphore_impl;
class rw_lock_impl;

} /* namespace detail */
} /* namespace elib */
#endif /* ELIB_LOCK_FWD_H */