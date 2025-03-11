#include "RedBlackSearchTree.h"

RedBlackSearchTree::RedBlackSearchTree(const std::vector<uint32_t> &list) {
    for (const uint32_t &x: list) {
        insert(x);
    }
}

void RedBlackSearchTree::insert(const uint32_t x) {
    table.insert(x);
}

bool RedBlackSearchTree::query(const uint32_t x) const {
    return table.contains(x);
}

