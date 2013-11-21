#ifndef ELIB_VERSION_CONFIG_HPP
#define ELIB_VERSION_CONFIG_HPP
# 
# define ELIB_FORMAT_VERSION(maj, min, rev)    (maj * 10000) + (min * 100) + rev
# define ELIB_FORMAT_VERSION_STR(maj, min, rev) "" #maj "_" #min "_" #rev
# 
# // set the version information
# define ELIB_MAJOR_VERSION 0
# define ELIB_MINOR_VERSION 1
# define ELIB_REVISION_VERSION 5
# 
# define ELIB_VERSION ELIB_FORMAT_VERSION( \
  ELIB_MAJOR_VERSION                       \
    , ELIB_MINOR_VERSION                   \
    , ELIB_REVISION_VERSION) 
#                           
# define ELIB_VERSION_STR ELIB_FORMAT_VERSION_STR( \
    ELIB_MAJOR_VERSION                             \
    , ELIB_MINOR_VERSION                           \
    , ELIB_REVISION_VERSION)
# 
#endif                                               // ELIB_VERSION_CONFIG_HPP