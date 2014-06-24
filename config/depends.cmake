
################################################################################
find_package( Threads REQUIRED )

################################################################################
include (FindPythonInterp)
if (PYTHONINTERP_FOUND)
    add_definitions(-DELIB_PYTHON_EXECUTABLE=${PYTHON_EXECUTABLE})
else()    
    message(WARNING "Python not found!")
endif()




