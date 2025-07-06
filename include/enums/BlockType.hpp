#pragma once
#include <raylib.h>

enum class BlockType {
    AIR,
    END,
    GRASS,
    DIRT,
    STONE,
    WOOD,
    LEAVES
};

inline Color GetColorForBlock(BlockType type) {
    switch (type) {
        case BlockType::END: return BLACK;
        case BlockType::GRASS: return GREEN;
        case BlockType::DIRT: return BROWN;
        case BlockType::STONE: return GRAY;
        case BlockType::WOOD: return DARKBROWN;
        case BlockType::LEAVES: return DARKGREEN;
        case BlockType::AIR: 
        default: return BLANK;
    }
}

inline bool IsWalkable(BlockType type) {
    switch (type) {
        case BlockType::LEAVES:
        case BlockType::AIR:
            return true;
        default: return false;
    }
}