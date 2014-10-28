set -e

if [[ "$BUILD" == "RELEASE" ]]
then
    export THREADS=18
else
    export THREADS=24
fi
if [[ "$CXX" == "g++" ]]
then
    export CXX="g++-4.8"
    export CC="gcc-4.8"
fi
if [[ "$CXX" == "clang++" ]]
then
    export CXX="clang++-3.5"
    export CC="clang-3.5"

    if [[ "$BUILD" == "DEBUG" ]]
    then
        sudo apt-get install -qq clang-3.6
    else
        sudo apt-get install -qq clang-3.6 python3
        export ELIB_CMAKE_OPTIONS="$ELIB_CMAKE_OPTIONS -DCONFIG_PYTHON3=ON"
    fi

fi

make configure
make -j8 elib
make batch-check-all

