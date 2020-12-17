#ifndef BRICK_H
#define BRICK_H

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <sstream>
#include <chrono>

struct Brick {
    double height;
    double width;
    double depth;

    Brick() : Brick(0, 0, 0) {}

    Brick(const double& x, const double& y, const double& z) : depth(z) {
        width = std::min(x, y);
        height = std::max(x, y);
    }

    bool operator<(const Brick& rhs) const {
        return width < rhs.width && height < rhs.height;
    }

    bool operator>(const Brick& rhs) const {
        return width > rhs.width && height > rhs.height;
    }

    bool operator==(const Brick& rhs) const {
        return height == rhs.height && width == rhs.width && depth == rhs.depth;
    }
};


struct Tower {
    std::vector<Brick> bricks;
    double depth;
    Brick base;
    Tower* rest;

    Tower() : depth(0) {};

    Tower(const Brick& b, Tower* tower) {
        depth = b.depth;
        base = b;
        rest = tower;
        if (rest != nullptr)
            depth += rest->depth;
    }

    Tower(const std::vector<Brick>& b) {
        depth = 0;
        for (const Brick &brick : b)
            depth += brick.depth;
        bricks = b;
    }

    void fillBricks() {
        Tower* t = this;
        while (t != nullptr) {
            bricks.push_back(t->base);
            t = t->rest;
        }
        std::reverse(bricks.begin(), bricks.end());
    }
};

#endif //BRICK_H