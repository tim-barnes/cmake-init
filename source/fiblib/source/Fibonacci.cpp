
#include <iostream>
#include <fiblib/fiblib_meta.h>

#include <fiblib/Fibonacci.h>


namespace fiblib
{


Fibonacci::Fibonacci()
{
    std::cout << "path = " << g_libraryPath << std::endl;
}

Fibonacci::~Fibonacci()
{
}

unsigned int Fibonacci::operator()(const unsigned int i)
{
    if (i < 2)
        return i;
    else
        return this->operator()(i - 1) + this->operator()(i - 2);
}


} // namespace fiblib
