#include <stdexcept>

#include <boost/python.hpp>

namespace bp=boost::python;

class MathError : public std::runtime_error
{
public:
    MathError(const std::string& msg) : std::runtime_error(msg) {}
};

double divide(double x, double y)
{
    if (0 == y)
        throw MathError("Denominator can not be 0.");

    return x / y;
}

double py_divide(double x, double y)
{
    try {
        return divide(x, y);
    }
    catch (const MathError& e) {
        PyErr_SetString(PyExc_ValueError, e.what());
        bp::throw_error_already_set();
        return 0;
    }
}

BOOST_PYTHON_MODULE(exceptions)
{
    bp::def("divide", py_divide);
}
