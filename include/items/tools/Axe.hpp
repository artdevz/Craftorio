#pragma once
#include "items/tools/Tool.hpp"

class Axe : public Tool {
    
public:
    Axe(ToolMaterial material, unsigned int id);

    void Update() override;
    void Draw() const override;
    void Interact() override;

};