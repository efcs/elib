#include "elib/semaphore.h"
#include "_semaphore.h"
#include <climits>

namespace elib {
	
Semaphore::Semaphore() : m_impl(new _elib::SemaphoreImpl(UINT_MAX))
{
}

Semaphore::Semaphore(unsigned int size) : m_impl(new _elib::SemaphoreImpl(size))
{
}

Semaphore::~Semaphore() { }

void Semaphore::lock() 
{ 
	m_impl->down();
}

bool Semaphore::try_lock()
{
	unsigned int tmp;
	return m_impl->try_down(tmp);
}

void Semaphore::unlock()
{
	m_impl->up();
}

unsigned int Semaphore::down()
{
	return m_impl->down();
}

bool Semaphore::try_down(unsigned int &resource)
{
	return m_impl->try_down(resource);
}

void Semaphore::up()
{
	m_impl->up();
}

unsigned int Semaphore::size() const
{
	return m_impl->size();
}

unsigned int Semaphore::available() const
{
	return m_impl->available();
}

unsigned int Semaphore::taken() const 
{
	return m_impl->taken();
}


	
} /* namespace elib */