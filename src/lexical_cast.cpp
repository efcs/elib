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
#include "elib/lexical_cast.h"

namespace elib {
   
/* see lexical_cast.h for a description of casting */
template <>
bool
lexical_cast(const std::string & from)
{
    std::stringstream ss;
    
    if (from.size() >= 1 && (from[0] == 't' || from[0] == 'f'))
        ss << std::boolalpha;
    
    bool val;
    ss << from;
    ss >> val;
    if (! ss)
        throw bad_lexical_cast();
    
    return val;
}


template <>
std::string
lexical_cast(const bool & b)
{
    std::stringstream ss;
    ss << std::boolalpha;
    ss << b;
    
    std::string tmp;
    ss >> tmp;
    if (! ss)
        throw bad_lexical_cast();
    
    return tmp;
}
   
   
} /* namespace elib */