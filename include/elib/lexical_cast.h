/* 
 * Copyright (C) 2013  Eric Fiselier
 * 
 * This file is part of elib.
 *
 * elib is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * elib is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with elib.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ELIB_LEXICAL_CAST_H
#define ELIB_LEXICAL_CAST_H

#include <stdexcept>
#include <sstream>

namespace elib {

    
class bad_lexical_cast : public std::runtime_error {
public:
    bad_lexical_cast()
        : std::runtime_error("bad lexical cast")
    { }
};


template <typename ToType, typename FromType>
ToType
lexical_cast(const FromType & from)
{
    std::stringstream ss;
    ToType val;
    try {
        ss << from;
        ss >> val;
    } catch (...) {
        throw bad_lexical_cast();
    }
    
    return val;
}

    
} /* namespace elib */
#endif /* ELIB_LEXICAL_CAST_H */