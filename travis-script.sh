set -e
if [[ "$CXX" == "g++" ]]
then
    export CXX="g++-4.8"
    export CC="gcc-4.8"
fi
if [[ "$CXX" == "clang++" ]]
then
    sudo apt-get install -qq clang-3.5
    export CXX="clang++-3.5"
    export CC="clang-3.5"
fi

make HEADER_TESTS=ON configure
make -j2
make -j2 check-elib
