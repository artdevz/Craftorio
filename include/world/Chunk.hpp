#pragma once

#include <algorithm>
#include <memory>
#include <vector>

#include <raylib.h>
#include <raymath.h>

#include "utils/Vector3i.hpp"
#include "world/Block.hpp"

struct Chunk {
    static constexpr int SIZE = 16;

    Vector3 origin;
    std::vector<std::shared_ptr<Block>> blocks;

    Chunk(Vector3 origin) : origin(origin) {}

    void AddBlock(std::shared_ptr<Block> block) { blocks.push_back(block); }

    void RemoveBlockAt(const Vector3i& position) {
        blocks.erase(
            std::remove_if(blocks.begin(), blocks.end(),
                [&position](const std::shared_ptr<Block>& block) {
                    Vector3i blockPosition = { 
                        (int)floor(block->GetPosition().x), 
                        (int)floor(block->GetPosition().y), 
                        (int)floor(block->GetPosition().z) 
                    };
                    return blockPosition == position;
                }
            ),
            blocks.end()             
        );
    }

    void Draw(const Vector3& playerPosition, float maxRenderDistance) const {
        for (const auto& block : blocks) {
            if (Vector3Distance(block->GetPosition(), playerPosition) <= maxRenderDistance*SIZE) block->Draw();
        }
    }
};