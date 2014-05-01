#include <stdexcept>

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
