#pragma once
#include <vector>
#include <memory>
#include "world/Structure.hpp"

class StructureManager {

public:
    void AddStructure(std::shared_ptr<Structure> structure);
    void Update();
    void Draw() const;

    const std::vector<std::shared_ptr<Structure>>& GetStructures() const;

private:
    std::vector<std::shared_ptr<Structure>> structures;

};