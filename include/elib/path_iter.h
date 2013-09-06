#ifndef ELIB_PATH_ITER_H
#define ELIB_PATH_ITER_H


namespace elib {
  

class path_iterator {
public:
    path_iterator();
    path_iterator(const path & p);
    
private:
    path m_path;
};
    
} /* namespace elib */
#endif /* ELIB_PATH_ITER_H */
