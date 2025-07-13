#pragma once

#include <cstddef>

struct Vector3i {
    int x, y, z;

    bool operator==(const Vector3i& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

namespace std {
    template<>
    struct hash<Vector3i> {
        size_t operator()(const Vector3i& v) const noexcept {
            size_t hx = std::hash<int>{}(v.x);
            size_t hy = std::hash<int>{}(v.y);
            size_t hz = std::hash<int>{}(v.z);
            return hx ^ (hy << 1) ^ (hz << 2);
        }
    };
}