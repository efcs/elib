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


/* ELIB_TODO can be used to locate TODO 's in code */
# if ELIB_STATIC_ASSERT_TODO
#   define ELIB_TODO(str) static_assert(! "ELIB TODO FOUND: ", str)
# elif ELIB_ASSERT_TODO
#   define ELIB_TODO(msg) ELIB_ASSERT(! "ELIB TODO", msg)
# elif ELIB_WARN_TODO
#   define ELIB_TODO(msg) ELIB_WARN(! "ELIB TODO", msg)
# elif ELIB_THROW_TODO
#   define ELIB_TODO(msg) throw "ELIB TODO " msg
# else
#   define ELIB_TODO(msg) ((void)0)
# endif

    
/* allow for macro overloading by counting # args */
#define \
  _ELIB_OVERLOAD(NAME, _1, _2, _3, _4, _5, _6,  _7,  _8,  _9,  _, ...) NAME##_
  
#define ELIB_OVERLOAD(NAME, ...) \
  _ELIB_OVERLOAD(NAME, __VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)


// Default declaration macros

# define ELIB_DEFAULT_CTOR(class, ...) \
  class() __VA_ARGS__ = default
  
# define ELIB_CONSTEXPR_CTOR(class) \
  constexpr class() noexcept = default;
  
# define ELIB_DEFAULT_DTOR(class, ...) \
  ~class() __VA_ARGS__ = default
    
# define ELIB_DEFAULT_CTOR_AND_DTOR(class, ...) \
  ELIB_DEFAULT_CTOR(class, __VA_ARGS__);            \
  ELIB_DEFAULT_DTOR(class, __VA_ARGS__)

# define ELIB_DEFAULT_COPY(class, ...)   \
  class(const class&) __VA_ARGS__ = default; \
  class& operator=(const class&) __VA_ARGS__ = default
  
# define ELIB_DEFAULT_MOVE(class, ...) \
  class(class&&) __VA_ARGS__ = default;    \
  class& operator=(class&&) __VA_ARGS__ = default
  
# define ELIB_NOEXCEPT_MOVE(class) \
  ELIB_DEFAULT_MOVE(class, noexcept)
  
# define ELIB_DEFAULT_COPY_AND_MOVE(class, ...) \
  ELIB_DEFAULT_COPY(class, __VA_ARGS__);            \
  ELIB_DEFAULT_MOVE(class, __VA_ARGS__)
  
# define ELIB_ALL_DEFAULT_DECLARATIONS(class) \
  ELIB_DEFAULT_CTOR_AND_DTOR(class);        \
  ELIB_DEFAULT_COPY_AND_MOVE(class);        \


// Delete declaration macros

# define ELIB_DELETE_COPY(class) \
  class(const class&) = delete;       \
  class& operator=(const class&) = delete;
  
# define ELIB_DELETE_MOVE(class) \
  class(class&&) = delete;            \
  class& operator=(class&&) = delete;
  
# define ELIB_DELETE_COPY_AND_MOVE(class) \
  ELIB_DELETE_COPY(class);                \
  ELIB_DELETE_MOVE(class)
  


#endif /* ELIB_COMMON_DEF_HPP */