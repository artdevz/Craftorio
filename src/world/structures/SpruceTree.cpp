#include "world/structures/SpruceTree.hpp"

void SpruceTree::Generate(BlockManager& manager, int x, int y, int z) {
    srand(time(nullptr));
    int trunkHeight = 30 + rand() % 5;
    TraceLog(LOG_DEBUG, "AlturaSpruce: %d", trunkHeight);

    for (int i = 0; i < trunkHeight; i++) {
        manager.AddBlockAt( { (float)x, (float)(y+i), (float)z }, BlockType::SPRUCE_WOOD );
    }

    int canopyRadius = 7;
    for (int y = 6; y < trunkHeight; y += 4) {
        for (int dx = -canopyRadius; dx <= canopyRadius; dx++) {
            for (int dz = -canopyRadius; dz <= canopyRadius; dz++) {
                float dist = std::sqrt(dx*dx + dz*dz);
                if (dist <= canopyRadius) {
                    manager.AddBlockAt( { (float)(x + dx), (float)(y), (float)(z + dz) }, BlockType::SPRUCE_LEAVES );
                    manager.AddBlockAt( { (float)(x + dx), (float)(y+1), (float)(z + dz) }, BlockType::SPRUCE_LEAVES );
                }
            }
        }
        if (canopyRadius > 1) canopyRadius--;
    }

    manager.AddBlockAt( { (float)x, (float)(trunkHeight), (float)z }, BlockType::SPRUCE_LEAVES );
    manager.AddBlockAt( { (float)x+1, (float)(trunkHeight), (float)z }, BlockType::SPRUCE_LEAVES );
    manager.AddBlockAt( { (float)x-1, (float)(trunkHeight), (float)z }, BlockType::SPRUCE_LEAVES );
    manager.AddBlockAt( { (float)x, (float)(trunkHeight), (float)z+1 }, BlockType::SPRUCE_LEAVES );
    manager.AddBlockAt( { (float)x, (float)(trunkHeight), (float)z-1 }, BlockType::SPRUCE_LEAVES );
}