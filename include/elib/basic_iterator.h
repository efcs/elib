#ifndef ELIB_BASIC_ITERATOR_H
#define ELIB_BASIC_ITERATOR_H

namespace elib {
    
    
template <typename Iterator, typename Value, typename Category,
          typename Reference = Value&, typename Difference = std::ptrdiff_t>
class basic_iterator {
public:
    typedef std::remove_const<Value>::type value_type;
    typedef Reference reference;
    typedef Value* pointer;
    typedef Difference difference_type;
    typedef Category iterator_category;
    
    reference
    operator*() const;
    
    
protected:
    typedef basic_iterator _basic_iterator;
};


    
} /* namespace elib */
#endif /* ELIB_BASIC_ITERATOR_H */
