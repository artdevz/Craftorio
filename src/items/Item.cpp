#include "items/Item.hpp"

Item::Item() {}

Item::Item(bool stackable, unsigned int id, const std::string& name) :
    stackable(stackable), id(id), name(name) {}

bool Item::IsStackable() const { return stackable; }

unsigned int Item::GetId() const { return id; }

std::string Item::GetName() const { return name; }