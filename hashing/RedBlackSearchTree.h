#ifndef REDBLACKSEARCHTREE_H
#define REDBLACKSEARCHTREE_H
#include <cstdint>
#include <set>


class RedBlackSearchTree {
public:
    void insert(uint32_t x);
    [[nodiscard]] bool query(uint32_t x) const;
private:
    std::set<uint32_t> table;
};

#endif //REDBLACKSEARCHTREE_H
