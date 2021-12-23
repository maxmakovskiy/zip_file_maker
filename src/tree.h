#ifndef ZIP_CODER_TREE_H_
#define ZIP_CODER_TREE_H_

#include <memory>
#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

namespace zip_maker {


struct TreeNode 
{
    TreeNode(size_t w, const std::string& phr, 
            std::unique_ptr<TreeNode> l = nullptr,
            std::unique_ptr<TreeNode> r = nullptr)
        : weight(w)
        , phrase(phr)
        , left0(std::move(l))
        , right1(std::move(r))
    {
    }
    
    bool operator<(const TreeNode& other);

    size_t weight = 0;
    std::string phrase;
    std::unique_ptr<TreeNode> left0 = nullptr;
    std::unique_ptr<TreeNode> right1 = nullptr;
};

typedef std::unique_ptr<TreeNode> tree_ptr;

class Tree
{
public:
    Tree() = default;

    void Assign(std::vector<tree_ptr> free);

    void Traverse() const;

private:
    tree_ptr root_ = nullptr;    
    std::vector<tree_ptr> pool_;

    void buildTree();
    
};

void tree_traversal(const tree_ptr& node);

} 
#endif
