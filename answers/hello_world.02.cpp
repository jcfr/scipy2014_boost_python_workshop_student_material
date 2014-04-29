#include <iostream>
#include <string>

#include <boost/python.hpp>

void greet(const std::string& name)
{
    std::cout << "Hello, " << name << "!" << std::endl;
}

BOOST_PYTHON_MODULE(hello_world)
{
    boost::python::def("greet", greet);
}
