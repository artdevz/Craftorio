#pragma once
#include <unordered_map>
#include <vector>
#include <memory>
#include "world/Block.hpp"
#include "enums/BlockType.hpp"
#include "world/Chunk.hpp"
#include "utils/Vector2i.hpp"

class BlockManager {

public:
    void AddBlock(std::shared_ptr<Block> block);
    void AddBlockAt(Vector3 position, BlockType type);
    void LoadChunkAt(int chunkX, int chunkZ);
    void Update();
    void Draw(const Vector3& playerPosition, float maxRenderDistance) const;

    const std::vector<std::shared_ptr<Block>>& GetBlocks() const;
    std::vector<std::shared_ptr<Block>> GetNearbyBlocks(const Vector3& playerPosition, float radius);

    static Vector2i GetChunkCoords(const Vector3& position) {
        return Vector2i{ (int)floor(position.x / Chunk::SIZE), (int)floor(position.z / Chunk::SIZE) };
    }

private:
    std::vector<std::shared_ptr<Block>> blocks;
    std::unordered_map<Vector2i, Chunk> chunks;

};