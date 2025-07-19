#pragma once

#include <raylib.h>

enum class BlockType {
    AIR,
    END,
    GRASS,
    DIRT,
    STONE,
    WOOD,
    SPRUCE_WOOD,
    LEAVES,
    SPRUCE_LEAVES
};

inline Color GetColorForBlock(BlockType type) {
    switch (type) {
        case BlockType::END: return BLACK;
        case BlockType::GRASS: return GREEN;
        case BlockType::DIRT: return BROWN;
        case BlockType::STONE: return GRAY;
        case BlockType::WOOD: return DARKBROWN;
        case BlockType::SPRUCE_WOOD: return Color{100, 40, 50, 255};
        case BlockType::LEAVES: return Color{0, 117, 44, 210};
        case BlockType::SPRUCE_LEAVES: return Color{0, 85, 30, 210};
        case BlockType::AIR: 
        default: return BLANK;
    }
}

inline bool IsWalkable(BlockType type) {
    switch (type) {
        case BlockType::LEAVES:
        case BlockType::SPRUCE_LEAVES:
        case BlockType::AIR:
            return true;
        default: return false;
    }
}