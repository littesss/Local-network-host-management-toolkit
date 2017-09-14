.PHONY: clean
.PHONY: all
.PHONY: lasync
.PHONY: lib
.PHONY: ut

CXXFLAGS = -g -lpthread -I lib  lib/*.o

all: binaries #ut

binaries: lasync  laclient

lasync: lib  lasync.cpp
	$(CXX)  $(CXXFLAGS) lasync.cpp -o $@

laclient: lib  laclient.cpp
	$(CXX)  $(CXXFLAGS) laclient.cpp -lpthread -o $@

ut:
	cd ut; $(MAKE)

lib:
	cd lib; $(MAKE)


clean: 
	rm -rf  lasync  laclient
	cd  ut; $(MAKE) clean
	cd  lib; $(MAKE) clean


