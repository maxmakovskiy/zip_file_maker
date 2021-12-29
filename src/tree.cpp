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

    auto glewSymbols = [](const Symbols& lhs,
            const Symbols& rhs)
    {
        Symbols res(lhs);
        res.insert(res.end(), rhs.begin(), rhs.end());
        return res;
    };

    while (pool_.size() > 1)
    {
        TreePtr target1 = pool_.top();
        pool_.pop();
        TreePtr target2 = pool_.top();
        pool_.pop();
       
        auto newNode = std::make_shared<TreeNode>(
                target1->weight + target2->weight,
                glewSymbols(target1->phrase, target2->phrase),
                target1,
                target2);

        pool_.push(newNode);
    }

    root_ = pool_.top();
    pool_.pop();
}

void
Tree::Assign
(const std::vector<TreePtr>& pool)
{
    std::for_each(pool.begin(), pool.end(),
                  [&](TreePtr item){
                    pool_.push(item);
                  });

    buildTree();
}

void
Tree::Traverse() const
{
    tree_traversal_print(root_, 0);
}

/*
Leaf
Tree::ExtractLeaf() 
{
    TreePtr trailing = nullptr;
    TreePtr traverser = root_;
    Code code;

//    while(traverser->left0 != nullptr
//          || traverser->right1 != nullptr)
    while(traverser->phrase.size() != 1)
    {
        trailing = traverser;
        if (traverser->left0 != nullptr) {
            code.push_back(0);
            traverser = traverser->left0;
        } else {
            code.push_back(1);
            traverser = traverser->right1;
        }
    }

    if (trailing->left0 == traverser) {
        trailing->left0 = nullptr;
    } else {
        trailing->right1 = nullptr;
    }

    return Leaf{std::move(traverser->phrase), std::move(code)};
}
*/

// for printf-like visual debug
void
tree_traversal_print
(const TreePtr& node, int depth)
{
    if (!node) return;

    std::cout << "depth: " << depth << "; ";
    std::cout << "phrase: '" << node->phrase << "'" << std::endl;

    tree_traversal_print(node->left0, depth + 1);
    tree_traversal_print(node->right1, depth + 1);
}

std::ostream&
operator<<
(std::ostream& os, const Symbols& bytes)
{
    std::for_each(bytes.begin(),
                  bytes.end(),
                  [&](std::byte item){
                    os << static_cast<char>(item);
                  });

    return os;
}

void
Tree::FindMatch
(std::byte target)
{
    Code code;
    treeTraverse(root_, target, code);
}


void
Tree::treeTraverse
(const TreePtr& node, std::byte target, Code& code)
{
    if (!node) return;
    if (node->phrase.size() == 1 &&
        node->phrase.front() == target)
    {
        coderTable_[target] = code;
/*
        std::cout << "Target: " << std::to_string(static_cast<uint8_t>(target)) << "; Code: ";
        for(uint8_t item : code) {
            std::cout << static_cast<uint32_t>(item);
        }
        std::cout << std::endl;
*/
        return;
    }
    else
    {
        code.push_back(0);
        treeTraverse(node->left0, target, code);
        code.pop_back();

        code.push_back(1);
        treeTraverse(node->right1, target, code);
        code.pop_back();
    }
}

CoderTable
Tree::GetCoderTable() const
{
    return coderTable_;
}

}

