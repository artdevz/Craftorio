#include "items/tools/Axe.hpp"
#include <iostream>

Axe::Axe(ToolMaterial material, unsigned int id) :
    Tool(material, id, GetToolMaterialStats(material).name + " Axe") {}

void Axe::Update() {}

void Axe::Draw() const {
    std::cout << "Drawing: " << GetName() << std::endl;
}

void Axe::Interact() {
    std::cout << "Interagiu com o " << GetName() << "!" << std::endl;
}