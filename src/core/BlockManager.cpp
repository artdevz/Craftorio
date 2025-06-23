#include "core/BlockManager.hpp"

void BlockManager::AddBlock(std::shared_ptr<Block> block) { blocks.push_back(block); }

void BlockManager::Update() { for (auto& block : blocks) block->Update(); }

void BlockManager::Draw() const { for (const auto& block : blocks) block->Draw(); }

const std::vector<std::shared_ptr<Block>>& BlockManager::GetBlocks() const { return blocks; }