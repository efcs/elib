#ifndef COMMONDEF_H
#define COMMONDEF_H

/* A nice macro to get rid of unused parameters */
#define UNUSED(x) (void)(x)

/* turn off copy constructor */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)
  
#endif /* COMMONDEF_H */
