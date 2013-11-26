#ifndef ELIB_MP_ALGORITHM_ALGORITHM_FWD_HPP
#define ELIB_MP_ALGORITHM_ALGORITHM_FWD_HPP

# include <elib/mp/types.hpp>
# include <elib/mp/metafunction/arg.hpp>
# include <elib/mp/metafunction/comparison.hpp>
# include <elib/CXX14/type_traits.hpp>

namespace elib 
{
  namespace mp
  {
   
  //////////////////////////////////////////////////////////////////////////////
  //                            Inserters                                              
  //////////////////////////////////////////////////////////////////////////////
  
   
  //-------------------------------- back_inserter---------------------------//
  
    template <class Seq> struct back_inserter;
    
  //-------------------------------- front_inserter -------------------------// 
  
    template <class Seq> struct front_inserter;
    
  //-------------------------------- inserter --------------------------------// 
  
    template <class State, class Operation> struct inserter;
    
  //////////////////////////////////////////////////////////////////////////////
  //                            Iteration                                              
  //////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- fold --------------------------------// 
    
    template <class Seq, class State, class ForwardOp> struct fold;
  
  //-------------------------------- iter_fold ------------------------------// 
  
    template <class Seq, class State, class ForwardOp> struct iter_fold;
  
  //-------------------------------- reverse_fold ---------------------------//
  
    template <class Seq, class State, class ForwardOp, class BackwardOp>
    struct reverse_fold;
    
  //-------------------------------- reverse_iter_fold ----------------------// 
    
    template <class Seq, class State
      , class BackwardOp, class ForwardOp
    >
    struct reverse_iter_fold;
    
  //-------------------------------- accumulate -----------------------------// 
    
    template <class Seq, class State, class ForwardOp>
    struct accumulate;
    
  //////////////////////////////////////////////////////////////////////////////
  //                            Querying                                              
  //////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- find -----------------------------------//
  
    template <class Seq, class T> struct find;
  
  //-------------------------------- find_if --------------------------------// 
  
    template <class Seq, class Pred> struct find_if;
      
  //-------------------------------- contains -------------------------------//
    
    template <class Seq, class T> struct contains;
  
  //-------------------------------- count ----------------------------------//
    
    template <class Seq, class T> struct count;
  
  //-------------------------------- count_if --------------------------------//
  
    template <class Seq, class Pred> struct count_if;
  
  //-------------------------------- lower_bound ----------------------------//
  
    template <class Seq, class T, class Pred>
    struct lower_bound;
  
  //-------------------------------- upper_bound ----------------------------//
  
    template <class Seq, class T, class Pred>
    struct upper_bound;
  
  //-------------------------------- min_element ----------------------------// 
  
    template <class Seq, class Pred>
    struct min_element;
    
  //-------------------------------- max_element ----------------------------//
  
    template <class Seq, class Pred>
    struct max_element;
  
  //-------------------------------- equal ----------------------------------// 
  
    template <class Seq1, class Seq2, class Pred>
    struct equal;
  
  //////////////////////////////////////////////////////////////////////////////
  //                            Transformation                                              
  //////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- copy -----------------------------------//
  
    template <class Seq, class In> struct copy;
  
  //-------------------------------- copy_if --------------------------------//
  
    template <class Seq, class Pred, class In> struct copy_if;
  
  //-------------------------------- transform ------------------------------// 
  
    // Overload:
    //       <class Seq, class Op, class In = na>
    //       <class Seq1, class Seq2, class BinaryOp, class In = na>
    template <class Seq1, class Seq2, class BinaryOp, class In>
    struct transform;
  
  //-------------------------------- replace --------------------------------//
  
    template <class Seq, class Old, class New, class In>
    struct replace;
  
  //-------------------------------- replace_if -----------------------------//
    
    template <class Seq, class Pred, class NewType, class In>
    struct replace_if;
  
  //-------------------------------- remove ---------------------------------//
    
    template <class Seq, class T, class In>
    struct remove;
  
  //-------------------------------- remove_if ------------------------------//
  
    template <class Seq, class Pred, class In>
    struct remove_if;
  
  //-------------------------------- unique ---------------------------------//
  
    template <class Seq, class Pred, class In>
    struct unique;
    
  //-------------------------------- partition ------------------------------//
    
    template <class Seq, class Pred, class In1, class In2>
    struct partition;
  
  //-------------------------------- stable_partition -----------------------//
  
    template <class Seq, class Pred, class In1, class In2>
    struct stable_partition;
  
  //-------------------------------- sort -----------------------------------//
  
    template <class Seq, class Pred, class In>
    struct sort;
  
  //-------------------------------- reverse --------------------------------//
  
    template <class Seq, class In> struct reverse;
  
  //-------------------------------- reverse_copy ---------------------------//
    
    template <class Seq, class In> struct reverse_copy;
  
  //-------------------------------- reverse_copy_if ------------------------//
  
    template <class Seq, class Pred, class In> 
    struct reverse_copy_if;
    
  //-------------------------------- reverse_transform ----------------------//
  
    // Overload:
    //        class Seq, class Op, class In=na
    //        class Seq1, class Seq2, class BinaryOp, class In
    template <class Seq1, class Seq2, class Op, class In>
    struct reverse_transform;
  
  //-------------------------------- reverse_replace ------------------------//
  
    template <class Seq, class Old, class New, class In>
    struct reverse_replace;
  
  //-------------------------------- reverse_replace_if ---------------------//
  
    template <class Seq, class Pred, class New, class In>
    struct reverse_replace_if;
  
  //-------------------------------- reverse_remove -------------------------//
    
    template <class Seq, class T, class In>
    struct reverse_remove;
  
  //-------------------------------- reverse_remove_if ----------------------//
  
    template <class Seq, class Pred, class In>
    struct reverse_remove_if;
  
  //-------------------------------- reverse_unique -------------------------//
  
    template <class Seq, class Pred, class In>
    struct reverse_unique;
  
  //-------------------------------- reverse_partition ----------------------// 
  
    template <class Seq, class Pred, class In1, class In2>
    struct reverse_partition;
  
  //-------------------------------- reverse_stable_partition ---------------// 
  
    template <class Seq, class Pred, class In1, class In2>
    struct reverse_stable_partition;
  
  //////////////////////////////////////////////////////////////////////////////
  //                            Runtime                                              
  //////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- for_each -------------------------------// 
    
    template <class Seq, class F>
    void for_each(F f);
  
    template <class Seq, class TransformOp, class F>
    void for_each(F f);
  
  }                                                         // namespace mp
}                                                           // namespace elib
#endif /* ELIB_MP_ALGORITHM_ALGORITHM_FWD_HPP */