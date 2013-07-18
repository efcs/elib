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
	
.PHONY: uninstall
uninstall:
	@ $(error no such rule uninstall)
	
	
.PHONY: check
check:
	@ ./bin/elib_test_static
	@ echo "Static Library tests passed"
	@ echo ""
	@ ./bin/elib_test_shared
	@ echo "Shared Library tests passed"

