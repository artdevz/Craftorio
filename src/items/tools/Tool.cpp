#include "items/tools/Tool.hpp"

Tool::Tool(ToolMaterial material, unsigned int id, const std::string& name, bool stackable) :
    Item(stackable, id, name), material(material), stats(GetToolMaterialStats(material)) {}

ItemType Tool::GetItemType() const noexcept { return ItemType::TOOL; }

int Tool::GetDurability() const noexcept { return stats.durability; }
float Tool::GetEfficiency() const noexcept { return stats.efficiency; }
ToolMaterial Tool::GetMaterial() const noexcept { return material; }

void Tool::Interact() {}