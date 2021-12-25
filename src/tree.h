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
    using TreePtr = std::unique_ptr<TreeNode>;

    TreeNode() = default;

    TreeNode(size_t w, const std::string& phr, 
            TreePtr l = nullptr,
            TreePtr r = nullptr)
        : weight(w)
        , phrase(phr)
        , left0(std::move(l))
        , right1(std::move(r))
    {
    }
    
    bool operator<(const TreeNode& other);

    size_t weight = 0;
    std::string phrase;
    TreePtr left0 = nullptr;
    TreePtr right1 = nullptr;
};

typedef std::unique_ptr<TreeNode> tree_ptr;

class Tree
{
public:
    void Assign(std::vector<tree_ptr> free);

    void Traverse() const;
    tree_ptr ExtractLeaf();

private:
    tree_ptr root_ = nullptr;    
    std::vector<tree_ptr> pool_;

    void buildTree();
    
};

void tree_traversal(const tree_ptr& node, int depth);
tree_ptr tree_traversal(tree_ptr& node);

} 
#endif
