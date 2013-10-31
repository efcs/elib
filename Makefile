SHELL := /bin/bash

.PHONY: all
all: 
	@ mkdir -p build/ ; cd build/ ; cmake .. ; cd ..
	@ $(MAKE) --no-print-directory -C build
	
.PHONY: e
e:
	@ $(MAKE) --no-print-directory distclean
	@ $(MAKE) --no-print-directory redep
	@ $(MAKE) --no-print-directory -C build
	
.PHONY: clean
clean:
	@ if [ -f build/Makefile ]; then $(MAKE) --no-print-directory -C build clean; fi
	
.PHONY: redep
redep: 
	@ rm -rf ./build ; mkdir -p build/ ; cd build/ ; cmake .. ; cd ..
	
.PHONY: distclean
distclean: 
	@ $(MAKE) --no-print-directory clean
	@ rm -rf ./build ./bin
	
.PHONY: install
install:
	@ $(MAKE) --no-print-directory -C build install
	
	
.PHONY: check
check:
	@ echo === Building tests ===
	@ $(MAKE) --no-print-directory -C build
	@ echo
	@ echo === Running static tests ===
	@ ./bin/elib_test_static --log_level=message --report_level=short
	@ echo 
	@ echo === Running shared tests ===
	@ ./bin/elib_test_shared --log_level=message --report_level=short
	
.PHONY: test
test:
	@ echo === Building test ===
	@ $(MAKE) --no-print-directory -C build
	@ echo
	@ echo === Running tests ===
	@ ./bin/elib_test_main
	
.PHONY: boost_test
boost_test:
	@ echo === Building test ===
	@ $(MAKE) --no-print-directory -C build
	@ echo
	@ echo === Running tests ===
	@ ./bin/elib_boost_test_main --log_level=message --report_level=short
