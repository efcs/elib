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
#ifndef ELIB_COMMON_DEF_HPP
#define ELIB_COMMON_DEF_HPP
# 
# /* used to suppress unused warnings */
# define ELIB_UNUSED(x) ((void)x)
# 
# /* ELIB_TODO can be used to locate TODO 's in code */
# if defined( ELIB_STATIC_ASSERT_TODO )
#   define ELIB_TODO(str) static_assert(! "ELIB TODO FOUND: ", str)
# elif defined( ELIB_ASSERT_TODO )
#   define ELIB_TODO(msg) ELIB_ASSERT(! "ELIB TODO", msg)
# elif defined( ELIB_WARN_TODO )
#   define ELIB_TODO(msg) ELIB_WARN(! "ELIB TODO", msg)
# elif defined( ELIB_THROW_TODO )
#   define ELIB_TODO(msg) throw "ELIB TODO " msg
# else
#   define ELIB_TODO(msg) ((void)0)
# endif
# 
# /* used to clearly have exposition for code we don't want to compile */
# define ELIB_EXPO(...) 
# 
#endif /* ELIB_COMMON_DEF_HPP */