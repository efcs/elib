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
	
.PHONY: ej
ej:
	@ $(MAKE) --no-print-directory distclean
	@ $(MAKE) --no-print-directory redep
	@ $(MAKE) --no-print-directory -j2 -C build
	
.PHONY: clean
clean:
	@ if [ -f build/Makefile ]; \
		then $(MAKE) --no-print-directory -C build clean ; \
	fi
	
.PHONY: redep
redep: 
	@ rm -rf build/ ; mkdir -p build/ ; cd build/ ; cmake $(ELIB_CMAKE_ARGS) ..  ; cd ..
	
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

.PHONY: check_shared
check_shared:
	@ echo === Building tests ===
	@ $(MAKE) --no-print-directory -C build
	@ echo 
	@ echo === Running shared tests ===
	@ ./bin/elib_test_shared --log_level=message --report_level=short

.PHONY: check_static
check_static:
	@ echo === Building tests ===
	@ $(MAKE) --no-print-directory -C build
	@ echo
	@ echo === Running static tests ===
	@ ./bin/elib_test_static --log_level=message --report_level=short
	
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

.PHONY: scan
scan:
	@ $(MAKE) --no-print-directory distclean
	@ rm -rf build/ ; mkdir -p build/ ; cd build/ ; cmake -DCONFIG_ELIB_COVERITY_SCAN=ON .. ; cd ..
	@ cov-build --dir cov-int $(MAKE) -C build all

.PHONY: scan_build
scan_build:
	@ rm -rf build/ ; mkdir -p build ; cd build/ ; scan-build cmake .. ; scan-build make ; cd ..

.PHONY: config_silent
config_silent:
	@ $(MAKE) -j2 --no-print-directory -C build all 1> /dev/null

.PHONY: config_loud
config_loud:
	@ $(MAKE) -j2 --no-print-directory -C build all 


.PHONY: config
config:
	@ $(MAKE) --no-print-directory distclean
	@ rm -rf build/ ; mkdir -p build/ ; cd build/ ; cmake $(BUILD_TYPE) $(STD) -DCONFIG_ELIB_ASSERT_CONFIG=ON -DCONFIG_INCLUDE_TESTS=ON .. ; cd ..
	@ time $(MAKE) --no-print-directory config_loud
	@ echo === Running static tests ===
	@ ./bin/elib_test_static --log_level=message --report_level=short
	@ echo === Running shared tests ===
	@ ./bin/elib_test_shared --log_level=message --report_level=short
	@ echo

.PHONY: san_config
san_config:
	@ $(MAKE) --no-print-directory distclean
	@ rm -rf build/ ; mkdir -p build/ ; cd build/ ; cmake $(CMAKE_CONFIG) $(BUILD_TYPE) $(STD) -DCONFIG_ELIB_ASSERT_CONFIG=ON -DCONFIG_INCLUDE_TESTS=ON .. ; cd ..
	@ time $(MAKE) --no-print-directory config_loud
	@ echo === Running shared tests ===
	@ ./bin/elib_test_shared --log_level=message --report_level=short
	@ echo

