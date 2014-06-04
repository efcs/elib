
.PHONY: doc
doc:
	doxygen doxygen.ini
	find html/ -type d -exec chmod 750 {} \; 
	find html/ -type f -exec chmod 640 {} \;

.PHONY: clean
clean:
	rm -rf latex html