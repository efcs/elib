#ifndef ELIB_SEMAPHORE_H
#define ELIB_SEMAPHORE_H

#include "lock.h"
#include <memory>

namespace elib {
	

namespace _elib {
class SemaphoreImpl;	
}

class SemaphoreInterface 
{
public:
	virtual ~SemaphoreInterface() { }
	virtual unsigned int down() = 0;
	virtual bool try_down(unsigned int &resource) = 0;
	virtual void up() = 0;
	
	virtual unsigned int size() const = 0;
	virtual unsigned int available() const = 0;
	virtual unsigned int taken() const = 0;
};


class Semaphore : public SemaphoreInterface, public LockInterface
{
public:
	Semaphore();
	explicit Semaphore(unsigned int size);
	~Semaphore();
	
	/* semaphore interface */
	unsigned int down();
	bool try_down(unsigned int &resource);
	void up();
	
	unsigned int size() const;
	unsigned int available() const;
	unsigned int taken() const;
	
	/* lock interface */
	void lock();
	bool try_lock();
	void unlock();
private:
	std::shared_ptr<_elib::SemaphoreImpl> m_impl;
};


} /* namespace elib */
#endif /* ELIB_SEMAPHORE_H */