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
#ifndef ELIB_TYPE_TRAITS_CONST_VOLATILE_HPP
#define ELIB_TYPE_TRAITS_CONST_VOLATILE_HPP

namespace elib {
namespace type_traits {
    
    
template <typename T>
struct remove_const {
    typedef T type;
};

template <typename T>
struct remove_const<const T> {
    typedef T type;
};

template <typename T>
struct remove_volatile {
    typedef T type;
};

template <typename T>
struct remove_volatile<volatile T> {
    typedef T type;
};

template <typename T>
struct remove_cv {
    typedef typename remove_const<typename remove_volatile<T>::type>::type type;
};

template <typename T>
struct add_const {
    typedef const T type;
};

template <typename T>
struct add_volatile {
    typedef volatile T type;
};

template <typename T>
struct add_cv {
    typedef typename add_const<typename add_volatile<T>::type>::type type;
};


////////////////////////////////////////////////////////////////////////////////
//                               C++14                                           
////////////////////////////////////////////////////////////////////////////////


template <typename T>
using remove_const_t = typename remove_const<T>::type;

template <typename T>
using remove_volatile_t = typename remove_volatile<T>::type;

template <typename T>
using remove_cv_t = typename remove_cv<T>::type;

template <typename T>
using add_const_t = typename add_const<T>::type;

template <typename T>
using add_volatile_t = typename add_volatile<T>::type;

template <typename T>
using add_cv_t = typename add_cv<T>::type;

} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_CONST_VOLATILE_HPP */