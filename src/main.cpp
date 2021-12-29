#include <iostream>
#include <sstream>
#include "coder.h"

int main()
{
    std::ostringstream oss;
    zip_maker::Coder coder(
            "/home/xemerius/devs/zip_file_maker/src/sample.txt");
//            "/home/xemerius/devs/zip_file_maker/src/image.jpg");
    
    coder.Encode(oss);
    std::cout << oss.str() << std::endl;

    return 0;
}

