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
#ifndef ELIB_TYPE_TRAITS_IS_INTEGRAL_HPP
#define ELIB_TYPE_TRAITS_IS_INTEGRAL_HPP

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/remove_cv.hpp>

namespace elib {
namespace type_traits {
namespace detail {
    
    
template <typename T>
struct is_integral : public false_type
{ };

template <>
struct is_integral<bool> : public true_type
{ };

template <>
struct is_integral<char> : public true_type
{ };

template <>
struct is_integral<signed char> : public true_type
{ };

template <>
struct is_integral<unsigned char> : public true_type
{ };

template <>
struct is_integral<char16_t> : public true_type
{ };

template <>
struct is_integral<char32_t> : public true_type
{ };

template <>
struct is_integral<wchar_t> : public true_type
{ };

template <>
struct is_integral<short> : public true_type
{ };

template <>
struct is_integral<unsigned short> : public true_type
{ };

template <>
struct is_integral<int> : public true_type
{ };

template <>
struct is_integral<unsigned int> : public true_type
{ };

template <>
struct is_integral<long> : public true_type
{ };

template <>
struct is_integral<unsigned long> : public true_type
{ };

template <>
struct is_integral<long long> : public true_type
{ };

template <>
struct is_integral<unsigned long long> : public true_type
{ };


} /* namespace detail */


template <typename T>
struct is_integral 
    : public detail::is_integral<typename remove_cv<T>::type>::type
{ };


} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_IS_INTEGRAL_HPP */
