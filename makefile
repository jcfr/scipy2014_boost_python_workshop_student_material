PYTHON_COMPILE_FLAGS = $(shell python3-config --cflags)
PYTHON_LINK_FLAGS = $(shell python3-config --ldflags)
PYTHON_EXTENSION_SUFFIX = $(shell python3-config --extension-suffix)
BOOST_COMPILE_FLAGS = -I/usr/local/include
BOOST_LINK_FLAGS = -L/usr/local/lib -lboost_python3

ALL_FLAGS = $(BOOST_COMPILE_FLAGS) $(BOOST_LINK_FLAGS) $(PYTHON_COMPILE_FLAGS) $(PYTHON_LINK_FLAGS) 

plumbing_test: plumbing_test.cpp
	g++ $(PYTHON_COMPILE_FLAGS) $(BOOST_COMPILE_FLAGS) -c -o plumbing_test.o plumbing_test.cpp
	g++ plumbing_test.o $(PYTHON_LINK_FLAGS) $(BOOST_LINK_FLAGS)

smoke_test: smoke_test.cpp
	g++ $(ALL_FLAGS) -fPIC -shared smoke_test.cpp -o smoke_test$(PYTHON_EXTENSION_SUFFIX)