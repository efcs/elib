#!/bin/bash

if [ -d /opt/gnu/lib64 ]; then
	export LD_LIBRARY_PATH="/opt/gnu/lib64:$LD_LIBRARY_PATH"
fi

echo ""
echo "Running shared library tests"
./elib_test_shared

echo ""
echo "Running static library tests"
./elib_test_static
