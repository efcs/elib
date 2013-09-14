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
#ifndef ELIB_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP
#define ELIB_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP

namespace elib {
namespace type_traits {
    
    
template <class T, T v>
struct integral_constant {
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant<T, v> type;
    
    constexpr
    operator value_type() const 
    { return value; }
    
    constexpr value_type
    operator()() const
    { return value; }
};


typedef integral_constant<bool, true> true_type;
typedef integral_constant<bool, false> false_type;


} /* namespace type_traits */    
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_INTEGRAL_CONSTANT_HPP */