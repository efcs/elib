#ifndef ELIB_MP_ALGORITHM_ALGORITHM_FWD_HPP
#define ELIB_MP_ALGORITHM_ALGORITHM_FWD_HPP

namespace elib 
{
  namespace mp
  {
   
  //////////////////////////////////////////////////////////////////////////////
  //                            Inserters                                              
  //////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- inserter --------------------------------// 
  
    template <class State, class Operation> struct inserter;
   
  //-------------------------------- back_inserter---------------------------//
  
    template <class Seq> struct back_inserter;
    
  //-------------------------------- front_inserter -------------------------// 
  
    template <class Seq> struct front_inserter;
    
  //////////////////////////////////////////////////////////////////////////////
  //                            Iteration                                              
  //////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- fold --------------------------------// 
    
    template <class Seq, class State, class ForwardOp> struct fold;
    
    template <class Seq, class State, class ForwardOp>
    using fold_t = typename fold<Seq, State, ForwardOp>::type;
  
  //-------------------------------- iter_fold ------------------------------// 
  
    template <class Seq, class State, class ForwardOp> struct iter_fold;
    
    template <class Seq, class State, class ForwardOp>
    using iter_fold_t = typename iter_fold<Seq, State, ForwardOp>::type;
  
  //-------------------------------- reverse_fold ---------------------------//
  
    template <class Seq, class State, class ForwardOp, class BackwardOp>
    struct reverse_fold;
    
    template <class Seq, class State, class ForwardOp, class BackwardOp>
    using reverse_fold_t = 
      typename reverse_fold<Seq, State, ForwardOp, BackwardOp>::type;
    
  //-------------------------------- reverse_iter_fold ----------------------// 
    
    template <class Seq, class State
      , class BackwardOp, class ForwardOp
    >
    struct reverse_iter_fold;
    
    template <class Seq, class State, class ForwardOp, class BackwardOp>
    using reverse_iter_fold_t = 
      typename reverse_iter_fold<Seq, State, ForwardOp, BackwardOp>::type;
    
  //-------------------------------- accumulate -----------------------------// 
    
    template <class Seq, class State, class ForwardOp>
    struct accumulate;
    
    template <class Seq, class State, class ForwardOp>
    using accumulate_t = typename accumulate<Seq, State, ForwardOp>::type;
    
  //////////////////////////////////////////////////////////////////////////////
  //                            Querying                                              
  //////////////////////////////////////////////////////////////////////////////
  
  //-------------------------------- find -----------------------------------//
  
    template <class Seq, class T> struct find;
    
    template <class Seq, class T>
    using find_t = typename find<Seq, T>::type;
  
  //-------------------------------- find_if --------------------------------// 
  
    template <class Seq, class Pred> struct find_if;
      
    template <class Seq, class Pred>
    using find_if_t = typename find_if<Seq, Pred>::type;
    
  //-------------------------------- contains -------------------------------//
    
    template <class Seq, class T> struct contains;
    
    template <class Seq, class T>
    using contains_t = typename contains<Seq, T>::type;
  
  //-------------------------------- count ----------------------------------//
    
    template <class Seq, class T> struct count;
    
    template <class Seq, class T>
    using count_t = typename count<Seq, T>::type;
  
  //-------------------------------- count_if --------------------------------//
  
    template <class Seq, class Pred> struct count_if;
    
    template <class Seq, class Pred>
    using count_if_t = typename count_if<Seq, Pred>::type;
  
  //-------------------------------- lower_bound ----------------------------//
  
    template <class Seq, class T, class Pred>
    struct lower_bound;
    
    template <class Seq, class T, class Pred>
    using lower_bound_t = typename lower_bound<Seq, T, Pred>::type;
  
  //-------------------------------- upper_bound ----------------------------//
  
    template <class Seq, class T, class Pred>
    struct upper_bound;
    
    template <class Seq, class T, class Pred>
    using upper_bound_t = typename upper_bound<Seq, T, Pred>::type;
  
  //-------------------------------- min_element ----------------------------// 
  
    template <class Seq, class Pred>
    struct min_element;
    
    template <class Seq, class Pred>
    using min_element_t = typename min_element<Seq, Pred>::type;
    
  //-------------------------------- max_element ----------------------------//
  
    template <class Seq, class Pred>
    struct max_element;
    
    template <class Seq, class Pred>
    using max_element_t = typename max_element<Seq, Pred>::type;
  
  //-------------------------------- equal ----------------------------------// 
  
    template <class Seq1, class Seq2, class Pred>
    struct equal;
    
    template <class Seq1, class Seq2, class Pred>
    using equal_t = typename equal<Seq1, Seq2, Pred>::type;
  
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