#pragma once
#include <memory>
#include "world/Block.hpp"
#include "world/Aggregator.hpp"

inline std::shared_ptr<Block> CreateBlock(Vector3 position, BlockType type) {
    switch (type) {
        case BlockType::GRASS: return std::make_shared<GrassBlock>(position);        
        case BlockType::STONE: return std::make_shared<StoneBlock>(position);
        case BlockType::DIRT: return std::make_shared<DirtBlock>(position, DirtType::DRY);
        case BlockType::WOOD: return std::make_shared<WoodBlock>(position, WoodType::OAK);
        case BlockType::LEAVES: return std::make_shared<LeafBlock>(position, LeafType::OAK);
        default: return nullptr;
        }
}