#include <boost/python.hpp>

int test() { return 42; }

BOOST_PYTHON_MODULE(smoke_test)
{
    boost::python::def("test", test);
}
