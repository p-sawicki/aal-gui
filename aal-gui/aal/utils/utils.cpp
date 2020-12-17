#include "aal/inc/utils.h"

std::vector<Brick> get_bricks(std::istream& stream, bool expand) {
    int bricks_amount = 0;
    stream >> bricks_amount;

    auto bricks = std::vector<Brick>();
    bricks.reserve(bricks_amount);
    for (int i = 0; i < bricks_amount; ++i) {
        double x, y, z;
        stream >> x >> y >> z;
        bricks.emplace_back(Brick(x, y, z));
        if (expand && x != z)
            bricks.emplace_back(Brick(z, y, x));
        if (expand && y != z)
            bricks.emplace_back(Brick(x, z, y));
    }

    return bricks;
}

int call(Algorithm_function func) {
    auto start = std::chrono::system_clock::now();
    Tower tower = func(std::cin);
    auto end = std::chrono::system_clock::now();

    std::cout << "Tower depth: " << tower.depth << "\nBricks\nWidth\t\t\tHeight\t\t\tDepth\n";
    for (Brick brick : tower.bricks)
        std::cout << brick.width << "\t\t\t" << brick.height << "\t\t\t" << brick.depth << "\n";
    std::cout << "Time (seconds): " << std::chrono::duration<double>(end - start).count() << "\n";
    return 0;
}
