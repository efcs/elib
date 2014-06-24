
################################################################################
find_package( Threads REQUIRED )

################################################################################
include (FindPythonInterp)
if (PYTHONINTERP_FOUND)
    set(ELIB_PYTHON_EXECUTABLE ${PYTHON_EXECUTABLE} 
        CACHE FILEPATH "Path to python executable")
    list(APPEND ELIB_AVAILABLE_FEATURES "ELIB_PYTHON_EXECUTABLE")
else()    
    message(WARNING "Python not found!")
endif()




