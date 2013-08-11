#ifndef ELIB_ENUM_ITERATOR_H
#define ELIB_ENUM_ITERATOR_H

#include "basic_enum_traits.h"

#include <iterator>

namespace elib {
    
/* used to construct iterators for an enum class at a givin position 
 * enum_traits not provided for this */
enum class iter_pos_e {
    begin,
    end
};
    
/* A iterator class for enumerations */
template <typename Enum>
class enum_iterator {
public:
    /* required typedefs for iterator_traits */
    typedef Enum value_type;
    typedef Enum& reference;
    typedef const Enum& const_reference;
    typedef Enum* pointer;
    typedef std::forward_iterator_tag iterator_category;
    typedef unsigned difference_type;
    
    /* construct an iterator with the current position at e */
    enum_iterator(Enum e);
    /* construct an iterator with the current position at the
     * begining or end */
    enum_iterator(iter_pos_e place = iter_pos_e::begin);
    
    enum_iterator &
    operator++();
    
    enum_iterator
    operator++(int);
    
    const_reference
    operator*() const;
    
    bool operator==(const enum_iterator & other);
    bool operator!=(const enum_iterator & other);
    
private:
    /* various typedefs used in implementation */
    typedef basic_enum_traits<Enum> basic_traits;
    typedef typename basic_traits::map_type map_type;
    typedef typename map_type::iterator map_iterator;
    typedef typename map_type::const_iterator map_const_iterator;
private:
    /* really we just adapt the maps key-value iterator,
     * so we just implement it using a map iterator */
    map_const_iterator m_iter;
};
    
} /* namespace elib */


#include "detail/_enum_iterator.h"

#endif /* ELIB_ENUM_ITERATOR_H */