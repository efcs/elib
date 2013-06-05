SHELL := /bin/bash

.PHONY: all
all: 
	@ $(MAKE) --no-print-directory -C build
	
.PHONY: e
e:
	@ $(MAKE) --no-print-directory distclean
	@ $(MAKE) --no-print-directory redep
	@ $(MAKE) --no-print-directory -C build -j
	
.PHONY: clean
clean:
	@ if [ -f build/Makefile ]; then $(MAKE) --no-print-directory -C build clean; fi
	
.PHONY: redep
redep: 
	@ mkdir -p build/ ; cd build/ ; cmake .. ; cd ..
	
.PHONY: distclean
distclean: 
	@ $(MAKE) --no-print-directory clean
	@ rm -rf build/ 
	
.PHONY: install
install:
	@ if [ -d ${HOME}/lib/include ]; then mkdir -p ${HOME}/lib/include/elib; fi
	@ $(MAKE) --no-print-directory -C build install
	
.PHONY: uninstall
uninstall:
	@ if [ -d ${HOME}/lib ]; then rm -f libelib.a libelib_s.so; fi
	@ if [ -d ${HOME}/lib/include/elib ]; then rm -rf ${HOME}/lib/include/elib; fi

