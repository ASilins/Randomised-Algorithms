#ifndef REDBLACKSEARCHTREE_H
#define REDBLACKSEARCHTREE_H
#include <cstdint>
#include <set>
#include <vector>


class RedBlackSearchTree {
public:
    explicit RedBlackSearchTree(const std::vector<uint32_t> &list);
    void insert(uint32_t x);
    bool query(uint32_t x) const;
private:
    std::set<uint32_t> table;
};

#endif //REDBLACKSEARCHTREE_H
