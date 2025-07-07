#pragma once
#include "enums/ItemType.hpp"
#include <string>

class Item {

public:
    Item();
    Item(bool stackable, unsigned int id, const std::string& name);
    virtual ~Item() = default;

    virtual void Update() = 0;
    virtual void Draw() const = 0;
    virtual void Interact() = 0;

    bool IsStackable() const noexcept;
    unsigned int GetId() const noexcept;
    virtual const std::string& GetName() const noexcept;
    virtual ItemType GetItemType() const = 0;

protected:
    bool stackable = false;
    unsigned int id = 0;
    std::string name;
    
};