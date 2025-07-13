#pragma once

#include "core/BlockManager.hpp"

class Structure {

public:
    virtual void Generate(BlockManager& manager, int x, int y, int z) = 0;
    virtual ~Structure() = default;

};