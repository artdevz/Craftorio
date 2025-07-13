#pragma once

#include "items/Item.hpp"
#include "items/tools/ToolMaterial.hpp"

class Tool : public Item {
    
public:
    Tool(ToolMaterial material, unsigned int id, const std::string& name, bool stackable = false);
    
    ItemType GetItemType() const noexcept override;
    int GetDurability() const noexcept;
    float GetEfficiency() const noexcept;
    ToolMaterial GetMaterial() const noexcept;

    void Interact() override;

protected:
    ToolMaterial material;
    ToolStats stats;

};