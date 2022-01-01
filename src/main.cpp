#include <iostream>
#include <sstream>
#include "coder.h"

int main()
{
    std::istringstream iss;
    iss.str("abcdaba");
    std::ostringstream oss;
    zip_maker::Coder coder(iss);
    
    coder.Encode(oss);
    std::cout << oss.str() << std::endl;

    return 0;
}

