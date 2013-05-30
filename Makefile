SHELL := /bin/bash

.PHONY: all
all: | silent
	$(MAKE) -C build
	
.PHONY: e
e: | silent
	$(MAKE) -s distclean
	$(MAKE) -s redep
	$(MAKE) -C build -j
	$(MAKE) -s install

.PHONY: clean
clean: | silent
	if [ -d build ] && [ -f build/Makefile ]; then $(MAKE) -C build clean; fi
	
.PHONY: install
install: | silent
	if [ -d ${HOME}/lib/include ]; then mkdir -p ${HOME}/lib/include/elib; fi
	$(MAKE) -C build install
	
.PHONY: uninstall
uninstall: | silent
	if [ -d ${HOME}/lib ]; then rm -f libelib.a libelib_s.so; fi
	if [ -d ${HOME}/lib/include/elib ]; then rm -rf ${HOME}/lib/include/elib; fi
	
.PHONY: redep
redep: 
	mkdir -p build/ ; cd build/ ; cmake .. ; cd ..
	
.PHONY: distclean
distclean: |silent
	if [ -d build ] && [ -f build/Makefile ]; then $(MAKE) -s -C build clean; fi
	rm -rf build/ 
	
silent:
	@:
	

