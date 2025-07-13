#pragma once

#include <cmath>

#include "world/Structure.hpp"

class Tree : public Structure {

public:
    void Generate(BlockManager& manager, int x, int y, int z) override;

};