#pragma once
#include "world/Structure.hpp"
#include <cmath>

class Tree : public Structure {

public:
    void Generate(BlockManager& manager, int x, int y, int z) override;

};