#include "aal/inc/bf.h"

Tower bf_get_highest_tower(std::istream &stream) {
    auto bricks = get_bricks(stream);
    auto predicate = [] (const Brick &lhs, const Brick &rhs) { return lhs.width < rhs.width; };
    std::sort(bricks.begin(), bricks.end(), predicate);

    Tower highest_tower;
    do {
        for (auto i = bricks.begin(); i < bricks.end(); ++i) {
            auto j = i + 1;
            while (j < bricks.end() && *j > *i)
                ++j;
            Tower tower = Tower(std::vector<Brick>(i, j));
            if (tower.depth > highest_tower.depth)
                highest_tower = tower;
        }
    } while (std::next_permutation(bricks.begin(), bricks.end(), predicate));

    return highest_tower;
}
