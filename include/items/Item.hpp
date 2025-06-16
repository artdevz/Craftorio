#pragma once
#include <string>

class Item {

public:
    Item();
    Item(bool stackable, unsigned int id, const std::string& name);
    virtual ~Item() = default;

    virtual void Update() = 0;
    virtual void Draw() const = 0;
    virtual void Interact() = 0;

    bool IsStackable() const;
    unsigned int GetId() const;
    std::string GetName() const;

protected:
    bool stackable;
    unsigned int id;
    std::string name;
    
};