#ifndef UTILS_H
#define UTILS_H

#include "brick.h"

typedef Tower (*Algorithm_function)(std::istream& stream); 

std::vector<Brick> get_bricks(std::istream& stream = std::cin, bool expand = true);
int call(Algorithm_function func);

#endif // UTILS_H
