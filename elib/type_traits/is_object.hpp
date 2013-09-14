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
#ifndef ELIB_TYPE_TRAITS_IS_OBJECT_HPP
#define ELIB_TYPE_TRAITS_IS_OBJECT_HPP

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/is_scalar.hpp>
#include <elib/type_traits/is_array.hpp>
#include <elib/type_traits/is_union.hpp>
#include <elib/type_traits/is_class.hpp>

namespace elib {
namespace type_traits {
    
    
template< class T>
struct is_object 
    : public integral_constant<bool,
        is_scalar<T>::value ||
        is_array<T>::value  ||
        is_union<T>::value  ||
        is_class<T>::value> 
{ };
        

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_OBJECT_HPP */