#ifndef ZIP_MAKER_CODER_H_
#define ZIP_MAKER_CODER_H_

#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <cmath>
#include <iostream>
#include "tree.h"

namespace zip_maker {

using CharFreqTable = std::unordered_map<std::byte, size_t>;

class Coder
{
public:
    explicit Coder(std::istream& input);
    void Encode(std::ostream& os);

private:
    std::istream& inputStream_;
    CharFreqTable charFreq_;
    Tree tree_;

    void processInput();
    void fillCoderTable();
};

size_t to_uint(const std::string& binary);
void print_coder_table(const CoderTable& table);
std::ostream& operator<<(std::ostream& os, const Code& codes);


}

#endif
