#include "world/structures/Tree.hpp"

void Tree::Generate(BlockManager& manager, int x, int y, int z) {
    int trunkHeight = 5;

    for (int i = 0; i < trunkHeight; i++) {
        manager.AddBlockAt( { (float)x, (float)(y + i), (float)z }, BlockType::WOOD );
    }

    int topY = y + trunkHeight;
    for (int dx = -2; dx <= 2; dx++) {
        for (int dz = -2; dz <= 2; dz++) {
            for (int dy = 0; dy <= 2; dy++) {
                float dist = std::sqrt(dx * dx + dz * dz + dy * dy);
                if (dist <= 2.5f) {
                    manager.AddBlockAt( { (float)(x + dx), (float)(topY + dy), (float)(z + dz) }, BlockType::LEAVES );
                }
            }
        }
    }
}