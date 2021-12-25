#include "tree.h"

namespace zip_maker {

bool
TreeNode::operator<
(const TreeNode& other)
{
    return weight < other.weight;
}

void
Tree::buildTree()
{
    while (pool_.size() > 1) {
        auto target1It = std::min_element(pool_.begin(),
                pool_.end());
        tree_ptr target1 = std::move(*target1It);
        pool_.erase(target1It);
        auto target2It = std::min_element(pool_.begin(),
                pool_.end());
        tree_ptr target2 = std::move(*target2It);
        pool_.erase(target2It);

        tree_ptr parent = std::make_unique<TreeNode>(
                target1->weight + target2->weight,
                std::string(target1->phrase + target2->phrase),
                std::move(target1),
                std::move(target2));

        pool_.push_back(std::move(parent));
    }

    root_ = std::move(pool_.front());
}

void
Tree::Assign
(std::vector<tree_ptr> free)
{
    pool_ = std::move(free);
    buildTree();
}

void
Tree::Traverse() const
{
    tree_traversal(root_);
}

void tree_traversal(const tree_ptr& node)
{
    if (!node) return;

    std::cout << "phrase: '" << node->phrase << "'" << std::endl;

    tree_traversal(node->left0);
    tree_traversal(node->right1);

}

}

