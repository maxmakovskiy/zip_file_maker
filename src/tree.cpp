#include "tree.h"

namespace zip_maker {

void
Tree::buildTree()
{
/* Some fancy stuff for printf-like debug - because
 * gdb doesn't allow to look up inside unique_ptr

    auto poolSnapshot = [](const std::string& stage, 
            const std::vector<tree_ptr>& cont) {
        std::cout << "== " << stage << " =================\n";
        std::for_each(cont.begin(), cont.end(), 
                [](const tree_ptr& el) {
                    std::cout << "weight: " << el->weight << "; "
                        << "phrase: " << el->phrase << std::endl;
                });
    };
    
    auto ptrSnapshot = [] (const tree_ptr& p1,
            const tree_ptr& p2) {
        std::cout << "it1: (" << p1->phrase << "); "
            << "it2: (" << p2->phrase << ")\n";
    };
*/

    auto lessTreeNode = [] (const auto& n1,
            const auto& n2) {
        return n1->weight < n2->weight; 
    };

    while (pool_.size() > 1) {
        auto target1It = std::min_element(pool_.begin(),
                pool_.end(), lessTreeNode);
        tree_ptr target1 = std::move(*target1It);
        pool_.erase(target1It);
       
        auto target2It = std::min_element(pool_.begin(),
                pool_.end(), lessTreeNode);
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
    tree_traversal(root_, 0);
}

tree_ptr
Tree::ExtractLeaf() 
{
    return tree_traversal(root_);
}

// for printf-like visual debug
void tree_traversal(const tree_ptr& node, int depth)
{
    if (!node) return;

    std::cout << "depth: " << depth << "; ";
    std::cout << "phrase: '" << node->phrase << "'" << std::endl;

    tree_traversal(node->left0, depth + 1);
    tree_traversal(node->right1, depth + 1);
}

tree_ptr tree_traversal(tree_ptr& node)
{
    if (node->phrase.size() == 1) return std::move(node);

    tree_traversal(node->left0);
    tree_traversal(node->right1);

    return nullptr;
}

}

