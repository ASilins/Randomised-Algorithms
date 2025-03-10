#include "RedBlackSearchTree.h"

void RedBlackSearchTree::insert(const uint32_t x) {
    table.insert(x);
}

bool RedBlackSearchTree::query(const uint32_t x) const {
    return table.contains(x);
}

