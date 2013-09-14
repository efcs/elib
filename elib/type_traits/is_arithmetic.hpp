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
#ifndef ELIB_TYPE_TRAITS_IS_ARITHMETIC_HPP
#define ELIB_TYPE_TRAITS_IS_ARITHMETIC_HPP

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/is_integral.hpp>
#include <elib/type_traits/is_floating_point.hpp>

namespace elib {
namespace type_traits {

    
template <typename T>
struct is_arithmetic 
    : public integral_constant<bool,
        is_integral<T>::value || 
        is_floating_point<T>::value>
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_ARITHMETIC_HPP */