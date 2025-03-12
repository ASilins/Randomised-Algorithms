#ifndef REDBLACKSEARCHTREE_H
#define REDBLACKSEARCHTREE_H
#include <cstdint>
#include <set>
#include <vector>


class RedBlackSearchTree {
public:
    explicit RedBlackSearchTree(const std::vector<uint64_t> &list);
    void insert(uint64_t x);
    bool query(uint64_t x) const;
private:
    std::set<uint64_t> table;
};

#endif //REDBLACKSEARCHTREE_H
