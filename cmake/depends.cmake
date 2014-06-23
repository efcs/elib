
add_custom_target(depends ALL)

################################################################################
find_package( Threads REQUIRED )

################################################################################
if (CONFIG_PYTHON3)
    set(PythonInterp_FIND_VERSION  "3.0")
endif()

include (FindPythonInterp)
if (PYTHONINTERP_FOUND)
    
    set(ELIB_PYTHON_EXECUTABLE ${ELIB_ROOT_PATH}/bin/elib_python_executable)

    add_custom_target(elib_python_executable
        ALL ln -fs ${PYTHON_EXECUTABLE} ${ELIB_PYTHON_EXECUTABLE})

    add_dependencies(depends elib_python_executable)

    add_definitions(-DELIB_PYTHON_EXECUTABLE=${ELIB_PYTHON_EXECUTABLE})

else()    
    message(WARNING "Python not found!")
endif()
