#pragma once
#include <cstddef>

struct Vector2i {
    int x, z;

    bool operator==(const Vector2i other) const { return x == other.x && z == other.z; }
};

namespace std {
    template<>
    struct hash<Vector2i> {
        size_t operator()(const Vector2i v) const noexcept {
            return std::hash<int>{}(v.x) ^ (std::hash<int>{}(v.z) << 1);
        }
    };
}
