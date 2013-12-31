#ifndef FOLD_HELPER_HPP
# define FOLD_HELPER_HPP

#include <elib/mp/algorithm.hpp>
#include <elib/mp/metafunctions.hpp>
#include <elib/mp/sequence.hpp>
#include <elib/mp/iterator.hpp>
#include <elib/mp/pack.hpp>
#include <elib/mp/list.hpp>
#include <elib/mp/vector.hpp>
#include <elib/mp/void.hpp>
#include <elib/mp/identity.hpp>
#include <elib/mp/integral_constant.hpp>

using namespace elib::mp;

template <class T>
struct IterCountOpImpl
{
  template <class State, class Iter>
  using apply = 
    eval_if_< 
        same_type<T, deref_t<Iter>>
      , next<State>
      , State
      >;
};

template <class T>
using IterCountOp = protect< IterCountOpImpl<T> >;


template <class P, class T>
using iter_foldl_n_count = iter_foldl_n_t<P, int_<0>, IterCountOp<T>>;
    
template <class P, class T>
using iter_foldr_n_count = iter_foldr_n_t<P, int_<0>, IterCountOp<T>>;
    
    
template <class P, class T>
using iter_foldl_if_count = iter_foldl_if_t<P, int_<0>, IterCountOp<T>>;

template <class P, class T>
using iter_foldr_if_count = iter_foldr_if_t<P, int_<0>, IterCountOp<T>>;


template <class P, class T>
using iter_foldl_count = iter_foldl_t<P, int_<0>, IterCountOp<T>>;

template <class P, class T>
using iter_foldr_count = iter_foldr_t<P, int_<0>, IterCountOp<T>>;


template <class T>
struct CountOpImpl
{
  template <class State, class Item>
  using apply = 
    eval_if_< 
        same_type<T, Item>
      , next<State>
      , State
      >;
};

template <class T>
using CountOp = protect< CountOpImpl<T> >;


template <class P, class T>
using foldl_n_count = foldl_n_t<P, int_<0>, CountOp<T>>;
    
template <class P, class T>
using foldr_n_count = foldr_n_t<P, int_<0>, CountOp<T>>;
    
    
template <class P, class T>
using foldl_if_count = foldl_if_t<P, int_<0>, CountOp<T>>;


template <class P, class T>
using foldr_if_count = foldr_if_t<P, int_<0>, CountOp<T>>;


template <class P, class T>
using foldl_count = foldl_t<P, int_<0>, CountOp<T>>;

template <class P, class T>
using foldr_count = foldr_t<P, int_<0>, CountOp<T>>;


# endif 