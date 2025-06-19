#include "core/StructureManager.hpp"

void StructureManager::AddStructure(std::shared_ptr<Structure> structure) {
    structures.push_back(structure);
}

void StructureManager::Update() {
    for (auto& structure : structures) structure->Update();
}

void StructureManager::Draw(Vector2 playerPosition) const {
    for (const auto& structure : structures) structure->Draw(playerPosition);
}

const std::vector<std::shared_ptr<Structure>>& StructureManager::GetStructures() const { return structures; }