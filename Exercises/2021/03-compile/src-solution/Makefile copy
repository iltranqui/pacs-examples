# the make File in the folder is executed when you type "make" in the terminal

CXXFLAGS = -std=c++17 -O2 -fPIC
CPPFLAGS = -DNDEBUG -I$(mkSuitesparseInc) -I$(mkEigenInc) -I../include
LDFLAGS = -L. -L$(mkSuitesparseLib) -Wl,-rpath=$(PWD)
LIBS = -lumfpack -llinearalgebra
CXX= g++ -fPIC

.PHONY: all clean distclean


# if you print "make all" the terminal will execute what it under the all section:
all: test
# Example
hello: 
	echo "Hello World"
	echo "HEllo World, again"

test: test.o liblinearalgebra.so
	# using dollars you can put a variable command in the name to what to execute
	$(CXX) $(LDFLAGS) test.o -o test $(LIBS)
    # this will print out
	# g++ -fPIC -l. -L$(mkSuitesparseLib) -Wl,-rpath=$(PWD) test.o -o test -lumfpack -llinearalgebra


test.o: test.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c test.cpp

liblinearalgebra.so: Utilities.o
	$(CXX) $(LDFLAGS) -shared -Wl,-soname,liblinearalgebra.so \
	Utilities.o -o liblinearalgebra.so

Utilities.o: Utilities.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c Utilities.cpp

clean:
	$(RM) *.o 

clean_unofficial: 
	rm -f Utilities.o test.o liblinearalgebra.so test

compile_test: test.cpp
	g++ -I${mkEigenInc} .I${mkSuitesparseInc} -I../include test.cpp\ -c

distclean: clean
	$(RM) liblinearalgebra.so test
