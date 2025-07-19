#pragma once

#include <raylib.h>

enum class LeafType {
    OAK,
    SPRUCE
};

inline Color GetColorForLeaf(LeafType type) {
    switch(type) {
        case LeafType::OAK: return DARKGREEN;
        case LeafType::SPRUCE: return Color{0, 85, 30, 255};
        default: return GRAY;
    }
}