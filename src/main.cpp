#include <iostream>
#include <sstream>
#include "coder.h"

int main()
{
    std::ostringstream oss;
    zip_maker::Coder coder(
            "/home/xemerius/devs/zip_file_maker/src/sample.txt");
    
    coder.Encode(oss);
    zip_maker::print_coder_table(coder.GetCoderTable());
    std::cout << "RESULT: " << oss.str() << std::endl;

    return 0;
}

