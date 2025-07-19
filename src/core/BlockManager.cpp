#include "core/BlockManager.hpp"

#include <cmath>

#include "core/BlockFactory.hpp"
#include "utils/Vector3i.hpp"

void BlockManager::AddBlock(std::shared_ptr<Block> block) { blocks.push_back(block); }

void BlockManager::AddBlockAt(Vector3 position, BlockType type) {
    /*auto block = std::make_shared<Block>(position, type);
    blocks.push_back(block);*/

    Vector2i chunkCoords = GetChunkCoords(position);
    Vector3 chunkOrigin = { 
        static_cast<float>(chunkCoords.x * Chunk::SIZE),
        0.0f,
        static_cast<float>(chunkCoords.z * Chunk::SIZE)
    };

    auto it = chunks.find(chunkCoords);
    if (it == chunks.end()) {
        chunks.emplace(chunkCoords, Chunk(chunkOrigin));
        it = chunks.find(chunkCoords);
    }

    auto block = CreateBlock(position, type);
    if (block) it->second.AddBlock(block);
}

void BlockManager::LoadChunkAt(int chunkX, int chunkZ) {
    int startX = chunkX * Chunk::SIZE;
    int startZ = chunkZ * Chunk::SIZE;

    for (int x = startX; x < startX + Chunk::SIZE; x++) {
        for (int z = startZ; z < startZ + Chunk::SIZE; z++) {
            for (int y = 0; y > -1; y--) {
                AddBlockAt({ (float)x, (float)y, (float)z }, BlockType::GRASS); // Temporário
            }
        }
    }
}

void BlockManager::Update() { for (auto& block : blocks) block->Update(); }

void BlockManager::Draw(const Vector3& playerPosition, float maxRenderDistance) const { 
    // for (const auto& block : blocks) block->Draw(); 

    Vector2i playerChunk = GetChunkCoords(playerPosition);
    constexpr int renderRadiusChunks = 3;

    for (const auto& [coords, chunk] : chunks) {
        int dx = coords.x - playerChunk.x;
        int dz = coords.z - playerChunk.z;

        if (std::abs(dx) <= renderRadiusChunks && std::abs(dz) <= renderRadiusChunks) {
            chunk.Draw(playerPosition, maxRenderDistance);
        }
    }
}

void BlockManager::Interact(float deltaTime, const Vector3& origin, const Vector3& direction, float maxDistance, std::shared_ptr<Item> item, ItemManager* itemManager) {
    const float step = 0.1f;
    for (float t = 0.0f; t <= maxDistance; t += step) {
        Vector3 point = Vector3Add(origin, Vector3Scale(direction, t));
        Vector3i blockPosition = { (int)floorf(point.x), (int)floorf(point.y), (int)floorf(point.z) };

        Vector2i chunkCoords = GetChunkCoords( { (float)blockPosition.x, (float)blockPosition.y, (float)blockPosition.z } );
        auto it = chunks.find(chunkCoords);
        if (it != chunks.end()) {
            for (const auto& block : it->second.blocks) {
                Vector3 posistion = block->GetPosition();
                if ( (int)posistion.x == blockPosition.x && (int)posistion.y == blockPosition.y && (int)posistion.z == blockPosition.z ) {
                    block->Interact(deltaTime, item);
                    if (block->GetType() == BlockType::AIR) {
                        if (itemManager) {
                            auto drop = block->GetDrop();
                            if (drop.has_value()) itemManager->AddItem(std::make_shared<ItemEntity>(std::move(*drop), Vector3{posistion.x+0.5f, posistion.y+0.5f, posistion.z+0.5f}));
                        }
                        it->second.RemoveBlockAt(blockPosition);
                    }
                    return;
                }
            }
        }
    }
}

const std::vector<std::shared_ptr<Block>>& BlockManager::GetBlocks() const { return blocks; }

std::vector<std::shared_ptr<Block>> BlockManager::GetNearbyBlocks(const Vector3& playerPosition, float radius) {
    std::vector<std::shared_ptr<Block>> nearby;
    
    Vector2i playerChunk = GetChunkCoords(playerPosition);
    int chunkRadius = static_cast<int>(ceil(radius / Chunk::SIZE));
    
    for (int dx = -chunkRadius; dx <= chunkRadius; dx++) {
        for (int dz = -chunkRadius; dz <= chunkRadius; dz++) {
            Vector2i coords = { playerChunk.x + dx, playerChunk.z + dz };
            auto it = chunks.find(coords);
            if (it != chunks.end()) 
                for (const auto& block : it->second.blocks) 
                    if (Vector3Distance(block->GetPosition(), playerPosition) <= radius) nearby.push_back(block);
        }
    }
    return nearby;
}