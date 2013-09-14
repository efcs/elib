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
#ifndef ELIB_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP
#define ELIB_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/conditional.hpp>
#include <elib/type_traits/is_reference.hpp>
#include <elib/type_traits/is_void.hpp>
#include <elib/type_traits/remove_reference.hpp>

namespace elib {
namespace type_traits {
namespace detail {
    
    
template <typename T,
    bool b1 = AND<NOT<is_reference<T>>, NOT<is_void<T>> >::value,
    bool b2 = is_rvalue_reference<T>::value> 
struct add_lvalue_reference {
    typedef T type;
};

template <typename T>
struct add_lvalue_reference<T, true, false> {
    typedef T& type;
};

template <typename T>
struct add_lvalue_reference<T, false, true> {
    typedef typename remove_reference<T>::type& type;
};


} /* namespace detail */


template <typename T>
struct add_lvalue_reference : public detail::add_lvalue_reference<T>
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_ADD_LVALUE_REFERENCE_HPP */
