#include <Python.h>

#include <iostream>
#include <string>

#include <boost/python.hpp>

namespace bp=boost::python;

int main(int, char**) 
{
    Py_Initialize();
    bp::object sys = bp::import("sys");
    bp::object version = sys.attr("version");
    std::cout << bp::extract<std::string>(version)() 
	      << std::endl;
    return 0;
}
