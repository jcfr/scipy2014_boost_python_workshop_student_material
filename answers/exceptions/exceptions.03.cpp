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

void translateMathError(const MathError& e)
{
    PyErr_SetString(PyExc_ValueError, e.what());
}

BOOST_PYTHON_MODULE(exceptions)
{
    bp::register_exception_translator<MathError>(translateMathError);

    bp::def("divide", divide);
}
