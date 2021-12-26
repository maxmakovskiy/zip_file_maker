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
    fillCoderTable();   
}

CoderTable
Coder::GetCoderTable() const
{
    return coderTable_;
}

void 
Coder::fillCoderTable()
{
    for (size_t i = 0; i < charFreq_.size(); i++) 
    {
        auto temp = tree.ExtractLeaf();
//        coderTable_[temp.first[0]] = toUInt(temp.second);
        coderTable_[temp.first[0]] = temp.second;
    }
}

void
Coder::Encode(std::ostream& os) 
{
    for(std::string temp; std::getline(file_, temp); )
    {
        for (char c : temp) { 
            os << coderTable_[c] << "|";
        }
    }
}

void
Coder::processFile()
{
    for(std::string temp; std::getline(file_, temp); )
    {
        for (char c : temp) { charFreq_[c]++; }
    }
    file_.clear();
    file_.seekg(0);

    std::vector<tree_ptr> freeNodes;
    std::for_each(charFreq_.begin(), charFreq_.end(),
            [&](auto& p) {
                freeNodes.push_back(
                    std::make_unique<TreeNode>(
                            p.second, std::string(1u, p.first)));
            });

    tree.Assign(std::move(freeNodes));
}

size_t toUInt(const std::string& binary)
{
    size_t result = 0;
    int i = binary.size() - 1;
    for (char c : binary)
    {
        size_t tempNum = c - '0';
        if (tempNum == 0) continue;

        result += std::pow(2, i);
        i--;
    }
    
    return result;
}

void
print_coder_table
(const CoderTable& table)
{
    std::cout << "======== CoderTable =========\n";
    for (const auto& [symbol, bin] : table)
    {
        std::cout << symbol << " - " << bin << '\n';
    }
}

}


