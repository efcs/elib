if [[ "$CXX" == "g++" ]]
then
    export CXX="g++-4.8"
fi

make UNIT_TESTS=OFF configure
make
