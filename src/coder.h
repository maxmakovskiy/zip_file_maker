#ifndef ZIP_MAKER_CODER_H_
#define ZIP_MAKER_CODER_H_

#include <string>
#include <exception>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <memory>

#include "tree.h"

namespace zip_maker {

class Coder
{
public:
    explicit Coder(const std::string& filename);

private:
    std::ifstream file_;
    std::unordered_map<char, size_t> charFreq_;
    
    Tree tree;

    void processFile();

};

}

#endif
