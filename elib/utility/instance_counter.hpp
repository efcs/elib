#ifndef ELIB_INSTANCE_COUNTER_HPP
#define ELIB_INSTANCE_COUNTER_HPP

namespace elib {
    

template <typename T>
class instance_counter {
public:
    static unsigned created;
    static unsigned alive;
    
    instance_counter();
protected:
    ~instance_counter();
};
    
    
} /* namespace elib */
#endif /* ELIB_INSTANCE_COUNTER_HPP */
