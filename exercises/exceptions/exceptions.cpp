#include <stdexcept>
#include <vector>

#include <boost/foreach.hpp>

class MathError : public std::runtime_error
{
public:
    MathError(const std::string& msg) : std::runtime_error(msg) {}
};

double mean(const std::vector<int>& ints)
{
    if (ints.empty())
	throw MathError("Input to mean can not be empty.");
    
    int sum = 0;
    BOOST_FOREACH(int i, ints) {
	sum += i;
    }
    return sum / ints.size();
}
