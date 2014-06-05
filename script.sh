if [[ "$CXX" == "g++" ]]
then
    export CXX="g++-4.8"
    export CC="gcc-4.8"
fi
if [[ "$CXX" == "clang++" ]]
then
    export CXX="clang++-3.5"
    export CC="clang-3.5"
fi

make configure
make -j2
make check
