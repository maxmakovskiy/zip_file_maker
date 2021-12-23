#include "coder.h"

namespace zip_maker {

Coder::Coder
(const std::string& filename)
    : file_(filename, std::ios::binary)
{
    if (!file_.is_open()) {
        throw std::invalid_argument("Can't open file " + filename);
    }

    processFile();
}


void
Coder::processFile()
{
    std::unordered_map<char, size_t> freq;
    char c;
    while (file_ >> std::noskipws >> c) {
        freq[c]++;       
    }
    
    std::for_each(freq.begin(), freq.end(),
            [&](auto& p) { charFreq_.insert({p.second, p.first}); });
}

}


