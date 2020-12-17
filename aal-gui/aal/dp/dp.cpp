#include "aal/inc/dp.h"

Tower get_highest_tower(std::istream &stream) {
    auto bricks = get_bricks(stream);
    std::sort(bricks.begin(), bricks.end(), [] (const Brick &lhs, const Brick &rhs) { return lhs.width < rhs.width; });
    
    auto towers = std::list<Tower*>();
    auto addresses = std::vector<Tower*>();

    while (!bricks.empty()) {
        double cutoff = 0;
        auto it = bricks.begin();
        auto apexes = std::vector<Brick>();

        while (it != bricks.end()) {
            Brick brick = *it;
            bool is_apex = true;

            for (Brick apex : apexes) {
                if (brick.width > apex.width && brick.height > apex.height) {
                    is_apex = false;
                    break;
                }
            }
            if (is_apex) {
                apexes.push_back(brick);
                cutoff = std::max(cutoff, brick.height);
                bricks.erase(it);
            } else
                ++it;
            
            if (it != bricks.end() && it->width > cutoff)
                break;
        }

        int size = apexes.size();
        Tower *new_towers = new Tower[size];
        addresses.push_back(new_towers);
        for (int i = 0; i < size; ++i) {
            Tower *best_tower_for_apex = nullptr;
            for (auto tower = towers.begin(); tower != towers.end(); ++tower) {
                if (apexes[i].width > (*tower)->base.width && apexes[i].height > (*tower)->base.height) {
                    best_tower_for_apex = *tower;
                    break;
                }
            }
            new_towers[i] = Tower(apexes[i], best_tower_for_apex);
            towers.insert(std::lower_bound(towers.begin(), towers.end(), &new_towers[i], 
                [](Tower* a, Tower* b) {return a->depth > b->depth; }), &new_towers[i]);
        }
    }
    Tower ans = *towers.front();
    ans.fillBricks();

    for (Tower* address : addresses)
        delete[] address;
    return ans;
}
