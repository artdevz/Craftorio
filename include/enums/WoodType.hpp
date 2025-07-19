#pragma once

#include <raylib.h>

enum class WoodType {
    OAK,
    SPRUCE
};

inline Color GetColorForWood(WoodType type) {
    switch(type) {
        case WoodType::OAK: return DARKBROWN;
        case WoodType::SPRUCE: return Color{60, 40, 30, 255};
        default: return GRAY;
    }
}