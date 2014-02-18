#ifndef ELIB_CONFIG_COVERITY_SCAN_CONFIG_HPP
#define ELIB_CONFIG_COVERITY_SCAN_CONFIG_HPP
# 
# // TODO This is defined when using coverity scan to watch build
# // scan currently hangs on some parts of elib and this macro
# // should be used to turn them off when building with scan
# if defined(ELIB_CONFIG_COVERITY_SCAN)
# endif
# 
#endif /* ELIB_CONFIG_COVERITY_SCAN_CONFIG_HPP */