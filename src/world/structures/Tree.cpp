#include "world/structures/Tree.hpp"

void Tree::Generate(BlockManager& manager, int x, int y, int z) {
    srand(time(nullptr));
    int trunkHeight = 8 + rand() % 5;
    TraceLog(LOG_DEBUG, "Altura: %d", trunkHeight);
    int logBase = 2;
    int canopyRadius = 8;

    // Base
    for (int i = 0; i < logBase; i++) {
        manager.AddBlockAt( { (float)x-1, (float)(y + i), (float)z },   BlockType::WOOD );
        manager.AddBlockAt( { (float)x-1, (float)(y + i), (float)z+1 }, BlockType::WOOD );
        manager.AddBlockAt( { (float)x,   (float)(y + i), (float)z-1 }, BlockType::WOOD );
        manager.AddBlockAt( { (float)x+1, (float)(y + i), (float)z-1 }, BlockType::WOOD );
        manager.AddBlockAt( { (float)x+2, (float)(y + i), (float)z },   BlockType::WOOD );
        manager.AddBlockAt( { (float)x+2, (float)(y + i), (float)z+1 }, BlockType::WOOD );
        manager.AddBlockAt( { (float)x,   (float)(y + i), (float)z+2 }, BlockType::WOOD );
        manager.AddBlockAt( { (float)x+1, (float)(y + i), (float)z+2 }, BlockType::WOOD );
    }

    // Tronco
    for (int i = 0; i < trunkHeight; i++) {
        manager.AddBlockAt( { (float)x,   (float)(y + i), (float)z },   BlockType::WOOD );
        manager.AddBlockAt( { (float)x,   (float)(y + i), (float)z+1 }, BlockType::WOOD );
        manager.AddBlockAt( { (float)x+1, (float)(y + i), (float)z },   BlockType::WOOD );
        manager.AddBlockAt( { (float)x+1, (float)(y + i), (float)z+1 }, BlockType::WOOD );
    }

    // Copa
    int topY = y + trunkHeight;
    float centerOffset = -0.5f;
    for (int dx = -canopyRadius; dx <= canopyRadius; dx++) {
        for (int dz = -canopyRadius; dz <= canopyRadius; dz++) {
            for (int dy = -4; dy <= canopyRadius; dy++) {
                float dist = std::sqrt(
                    (dx + centerOffset) * (dx + centerOffset) +
                    (dz + centerOffset) * (dz + centerOffset) +
                    (dy + centerOffset) * (dy + centerOffset)
                );
                if (dist <= canopyRadius) {
                    manager.AddBlockAt( { (float)(x + dx), (float)(topY + dy), (float)(z + dz) }, BlockType::LEAVES );
                }
            }
        }
    }
}