#pragma once
#include <vector>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include "world/Block.hpp"

struct Chunk {
    static constexpr int SIZE = 16;

    Vector3 origin;
    std::vector<std::shared_ptr<Block>> blocks;

    Chunk(Vector3 origin) : origin(origin) {}

    void AddBlock(std::shared_ptr<Block> block) { blocks.push_back(block); }

    void Draw(const Vector3& playerPosition, float maxRenderDistance) const {
        for (const auto& block : blocks) {
            if (Vector3Distance(block->GetPosition(), playerPosition) <= maxRenderDistance) block->Draw();
        }
    }
};