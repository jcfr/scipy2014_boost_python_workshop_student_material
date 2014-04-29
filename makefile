PYTHON_COMPILE_FLAGS = $(shell python3-config --cflags)
PYTHON_LINK_FLAGS = $(shell python3-config --ldflags)
PYTHON_EXTENSION_SUFFIX = $(shell python3-config --extension-suffix)
BOOST_COMPILE_FLAGS = -I/usr/local/include
BOOST_LINK_FLAGS = -L/usr/local/lib -lboost_python3

ALL_FLAGS = $(BOOST_COMPILE_FLAGS) $(BOOST_LINK_FLAGS) $(PYTHON_COMPILE_FLAGS) $(PYTHON_LINK_FLAGS) 

%$(PYTHON_EXTENSION_SUFFIX): %.cpp
	g++ $< -o $@ $(ALL_FLAGS) -fPIC -shared

plumbing_test: plumbing_test.cpp
	g++ plumbing_test.cpp -o plumbing_test $(ALL_FLAGS)

smoke_test: smoke_test$(PYTHON_EXTENSION_SUFFIX) ;

hello_world: hello_world$(PYTHON_EXTENSION_SUFFIX) ;

clean:
	rm -f *$(PYTHON_EXTENSION_SUFFIX)
	rm -f *.o