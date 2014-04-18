
CXX_FLAGS := -std=c++11 -Wall -Wextra -pedantic -O3 -I../../../
OBJS := standard_map.out flat_map.out linear_flat_map.out

.PHONY: all
all: $(OBJS)
	
-include $(OBJS:.out=.d)

%.out: flat_map_benchmark.cpp
	$(CXX) $(CXX_FLAGS) -DMAP_TYPE=$* flat_map_benchmark.cpp -o $*.out
	$(CXX) -MM $(CXX_FLAGS)  -DMAP_TYPE=$* flat_map_benchmark.cpp > $*.d

.PHONY: clean
clean:
	rm -f *.out *.d *.o

.PHONY: check
check: $(OBJS)
	./flat_map.out
	@ echo
	./linear_flat_map.out
	@ echo
	./standard_map.out
