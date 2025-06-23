#pragma once
#include <vector>
#include <memory>
#include "world/Block.hpp"

class BlockManager {

public:
    void AddBlock(std::shared_ptr<Block> block);
    void Update();
    void Draw() const;

    const std::vector<std::shared_ptr<Block>>& GetBlocks() const;

private:
    std::vector<std::shared_ptr<Block>> blocks;

};