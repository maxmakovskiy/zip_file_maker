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
    tree_traversal_print(root_, 0);
}

std::pair<std::string, std::string>
Tree::ExtractLeaf() 
{
    auto temp = root_.get();
    std::string code;
    while (temp != nullptr)
    {
        if (temp->phrase.size() == 1) {
            break;
        }

        if (temp->left0 != nullptr) {
            code += '0';
            temp = temp->left0.get();
        } else {
            code += '1';
            temp = temp->right1.get();
        }
    }
    
    std::string copyString(temp->phrase);
    deleteLeaf(temp->phrase);
    return std::make_pair(copyString, code);
}

// for printf-like visual debug
void
tree_traversal_print
(const tree_ptr& node, int depth)
{
    if (!node) return;

    std::cout << "depth: " << depth << "; ";
    std::cout << "phrase: '" << node->phrase << "'" << std::endl;

    tree_traversal_print(node->left0, depth + 1);
    tree_traversal_print(node->right1, depth + 1);
}

void
Tree::deleteLeaf
(const std::string& target)
{
    tree_traversal_delete(root_, target);
}

void
tree_traversal_delete
(tree_ptr& node, const std::string& target)
{
/*
 // Some printf-like debugging style 
    auto nodeSnapshot = [](const tree_ptr& node) {
        std::cout << "============= NODE: " << node->phrase << '\n'
          << "Weight: " << std::to_string(node->weight) << '\n'
          << "Right child: " << (node->right1 ? 
                  (node->right1->phrase) : "nullptr") << '\n'
          << "Left child: " << (node->left0 ? 
                  (node->left0->phrase) : "nullptr")
          << std::endl;
    };
*/

    if (!node) return;

//    nodeSnapshot(node);
    if (node->phrase == target) {
        auto toDel = std::move(node);
        return;
    }

    tree_traversal_delete(node->left0, target);
    tree_traversal_delete(node->right1, target);

}


}

