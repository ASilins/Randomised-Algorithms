#include "RedBlackSearchTree.h"

RedBlackSearchTree::RedBlackSearchTree(const std::vector<uint64_t> &list) {
    for (const uint64_t &x: list) {
        insert(x);
    }
}

void RedBlackSearchTree::insert(const uint64_t x) {
    table.insert(x);
}

bool RedBlackSearchTree::query(const uint64_t x) const {
    return table.contains(x);
}

