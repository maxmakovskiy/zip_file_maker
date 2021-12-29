#ifndef ZIP_CODER_TREE_H_
#define ZIP_CODER_TREE_H_

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <cstdint>

#include <iostream>

namespace zip_maker {

struct TreeNode;
using TreePtr = std::shared_ptr<TreeNode>;
using Symbols = std::vector<std::byte>;
using Code = std::vector<uint8_t>;
using CoderTable = std::unordered_map<std::byte, Code>;

struct TreeNode
{
    TreeNode(size_t w, std::vector<std::byte> phr,
            TreePtr l = nullptr,
            TreePtr r = nullptr)
        : weight(w)
        , phrase(std::move(phr))
        , left0(l)
        , right1(r)
    {
    }

    uint32_t weight = 0;
    Symbols phrase;
    TreePtr left0 = nullptr;
    TreePtr right1 = nullptr;
};

std::ostream& operator<<(std::ostream& os, const Symbols& bytes);

struct TreeNodeComp
{
    bool operator()(TreePtr lhs, TreePtr rhs)
    {
        return lhs->weight >= rhs->weight;
    }
};

struct Leaf
{
    Symbols phrase;
    Code code;
};

class Tree
{
public:
    Tree()
    {}

    void Assign(const std::vector<TreePtr>& pool);

    void Traverse() const;
    CoderTable GetCoderTable() const;
    void FindMatch(std::byte target);

private:
    TreePtr root_ = nullptr;
    std::priority_queue<TreePtr, std::vector<TreePtr>,
                TreeNodeComp> pool_;
    CoderTable coderTable_;

    void buildTree();
    void treeTraverse(const TreePtr& node, std::byte target, Code& code);

};

void tree_traversal_print(const TreePtr& node, int depth);


} 
#endif
