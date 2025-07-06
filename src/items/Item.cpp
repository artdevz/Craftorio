#include "items/Item.hpp"

Item::Item() {}

Item::Item(bool stackable, unsigned int id, const std::string& name) :
    stackable(stackable), id(id), name(name) {}

bool Item::IsStackable() const noexcept { return stackable; }

unsigned int Item::GetId() const noexcept { return id; }

const std::string& Item::GetName() const noexcept { return name; }