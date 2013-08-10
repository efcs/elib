#include "elib/semaphore.h"
#include "detail/semaphore_impl.h"

namespace elib {

semaphore::semaphore(unsigned count)
    : m_impl(new detail::semaphore_impl(count))    
{ 
}

semaphore::~semaphore()
{
    delete m_impl;
}

void
semaphore::lock()
{
    m_impl->lock();
}

void
semaphore::unlock()
{
    m_impl->unlock();
}

bool
semaphore::try_lock()
{
    return m_impl->try_lock();
}

unsigned
semaphore::count() const
{
    return m_impl->count();
}

unsigned
semaphore::max() const
{
    return m_impl->max();
}
    
} /* namespace elib */