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
#ifndef ELIB_TYPE_TRAITS_DECAY_HPP
#define ELIB_TYPE_TRAITS_DECAY_HPP

#include <elib/type_traits/integral_constant.hpp>
#include <elib/type_traits/remove_reference.hpp>
#include <elib/type_traits/remove_extent.hpp>
#include <elib/type_traits/remove_extent.hpp>
#include <elib/type_traits/conditional.hpp>
#include <elib/type_traits/is_array.hpp>
#include <elib/type_traits/add_pointer.hpp>
#include <elib/type_traits/is_function.hpp>
#include <elib/type_traits/remove_cv.hpp>

namespace elib {
namespace type_traits {
    
    
template <typename T>
struct decay {
    typedef typename remove_reference<T>::type U;
    typedef typename conditional< 
        is_array<U>::value,
        typename remove_extent<U>::type*,
        typename conditional< 
            is_function<U>::value,
            typename add_pointer<U>::type,
            typename remove_cv<U>::type
        >::type
    >::type type;
};
       
        
} /* namespace type_traits */
} /* namespace elib */
#endif /* ELIB_TYPE_TRAITS_DECAY_HPP */