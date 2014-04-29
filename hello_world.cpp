#include <iostream>
#include <string>

void hello_world(const std::string& name="world")
{
  std::cout << "Hello, " << name << std::endl;
}
