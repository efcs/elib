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


/* used to suppress unused warnings */
#define ELIB_UNUSED(x) ((void)x)


#define ELIB_DISALLOW_COPY_AND_ASSIGN(T) \
    T(const T &); \
    T & operator=(const T &)
    
    
/* allow for macro overloading by counting # args */
#define _ELIB_NARGS_COUNT(NAME, _1, _2, _3, _4, _5, _, ...) NAME##_
#define ELIB_NARGS(NAME, ...) _ELIB_NARGS_COUNT(NAME, __VA_ARGS__, 5, 4, 3, 2, 1, 0)



#endif /* ELIB_COMMON_DEF_HPP */