
################################################################################
find_package( Threads REQUIRED )

################################################################################
if (CONFIG_PYTHON3)
    set(PythonInterp_FIND_VERSION  "3.0")
endif()

include (FindPythonInterp)

if (PYTHONINTERP_FOUND)
    add_definitions(-DELIB_PYTHON_EXECUTABLE=${PYTHON_EXECUTABLE})
else()    
    message(WARNING "Python not found!")
endif()
