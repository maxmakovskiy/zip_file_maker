#ifndef ZIP_CODER_TREE_H_
#define ZIP_CODER_TREE_H_

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

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
    std::pair<std::string,std::string> ExtractLeaf();

private:
    tree_ptr root_ = nullptr;    
    std::vector<tree_ptr> pool_;

    void buildTree();
    void deleteLeaf(const std::string& target);

};

void tree_traversal_print(const tree_ptr& node, int depth);
void tree_traversal_delete(tree_ptr& node,
        const std::string& target);

} 
#endif
