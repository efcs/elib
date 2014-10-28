set(WARNING_FLAGS"")

if (CONFIG_ALL_WARNINGS)

    add_flags( WARNING_FLAGS
    -pedantic-errors  -Waggregate-return -Wcast-align 
    -Wcast-qual  -Wchar-subscripts  -Wcomment -Wconversion 
    -Wdisabled-optimization -Wfloat-equal  -Wformat  -Wformat=2 
    -Wformat-nonliteral -Wformat-security  -Wformat-y2k -Wimport  -Winit-self  
    -Winline -Winvalid-pch -Wlong-long -Wmissing-braces 
    -Wmissing-field-initializers -Wmissing-format-attribute 
    -Wmissing-include-dirs -Wmissing-noreturn -Wpacked  -Wpadded -Wparentheses
    -Wpointer-arith -Wredundant-decls -Wreturn-type -Wsequence-point  -Wshadow 
    -Wsign-compare  -Wstack-protector -Wstrict-aliasing -Wstrict-aliasing=2 
    -Wswitch  -Wswitch-default -Wswitch-enum -Wtrigraphs  -Wuninitialized 
    -Wunknown-pragmas  -Wunreachable-code -Wunused -Wunused-function  
    -Wunused-label  -Wunused-parameter -Wunused-value  -Wunused-variable  
    -Wvariadic-macros -Wvolatile-register-var  -Wwrite-strings
   )
  
  if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
        #add_flags( WARNING_FLAGS -Wunsafe-loop-optimizations )
        #add_flags( WARNING_FLAGS -Weffc++)
        add_flags( WARNING_FLAGS -Wno-stack-protector)
  elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        add_flags( WARNING_FLAGS
            -Weverything -Wno-c++98-compat 
            -Wno-c++98-compat-pedantic -Wno-newline-eof)
        add_flags(UNIT_TEST_FLAGS -Wno-global-constructors -Wno-exit-time-destructors -Wno-unused-local-typedef)
  endif()
  
  add_flags( WARNING_FLAGS
        -Wno-padded -Wno-aggregate-return -Wno-inline -Wno-long-long)

endif()
