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
    tree.Traverse();
}


void
Coder::processFile()
{
    for(std::string temp; std::getline(file_, temp); )
    {
        for (char c : temp) { charFreq_[c]++; }
    }
   
    std::vector<tree_ptr> freeNodes;
    std::for_each(charFreq_.begin(), charFreq_.end(),
            [&](auto& p) {
                freeNodes.push_back(
                    std::make_unique<TreeNode>(
                            p.second, std::string(1u, p.first)));
            });

    tree.Assign(std::move(freeNodes));
}

}


