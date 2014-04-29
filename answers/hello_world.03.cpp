#include <string>

#include <boost/python.hpp>

std::string greet(const std::string& name)
{
    return "Hello, " + name + "!";
}

BOOST_PYTHON_MODULE(hello_world)
{
    boost::python::def("greet", greet);
}
