#ifndef ZIP_MAKER_CODER_H_
#define ZIP_MAKER_CODER_H_

#include <string>
#include <exception>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <cmath>
#include <iostream>
#include "tree.h"

namespace zip_maker {

//using CoderTable = std::unordered_map<char, size_t>;
using CoderTable = std::unordered_map<char, std::string>;

class Coder
{
public:
    explicit Coder(const std::string& filename);
    void Encode(std::ostream& os);
    CoderTable GetCoderTable() const;

private:
    std::ifstream file_;
    std::unordered_map<char, size_t> charFreq_;
    CoderTable coderTable_;
    
    Tree tree;

    void processFile();
    void fillCoderTable();
};

size_t to_uint(const std::string& binary);
void print_coder_table(const CoderTable& table);

}

#endif
