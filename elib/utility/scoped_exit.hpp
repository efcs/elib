#ifndef ELIB_UTILITY_SCOPED_EXIT_HPP
#define ELIB_UTILITY_SCOPED_EXIT_HPP

# include <functional>

namespace elib
{
   
  class scoped_exit
  {
  public:
    typedef std::function<void()> exit_fn_t;
    
    scoped_exit() = delete;
    
    scoped_exit(exit_fn_t fn)
      : m_fn{fn}
    { }
      
    scoped_exit(const scoped_exit&) = delete;
    scoped_exit(scoped_exit&&) = delete;
    
    scoped_exit& operator=(const scoped_exit&) = delete;
    scoped_exit& operator=(scoped_exit&&) = delete;
    
    ~scoped_exit()
    {
      if (m_fn) m_fn();
    }
    
    void release()
    {
      m_fn = exit_fn_t{};
    }
    
    operator bool() const
    { 
      return static_cast<bool>(m_fn); 
    }
    
  private:
    exit_fn_t m_fn;
  };                                                        // class scoped_exit
  
  
}                                                           // namespace elib
#endif /* ELIB_UTILITY_SCOPED_EXIT_HPP */