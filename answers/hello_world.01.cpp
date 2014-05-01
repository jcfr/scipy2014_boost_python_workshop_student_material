#include <iostream>
#include <string>

#include <boost/python.hpp>

void greet()
{
    std::cout << "Hello, world!" << std::endl;
}

BOOST_PYTHON_MODULE(hello_world)
{}
