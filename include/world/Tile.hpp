#pragma once
#include <raylib.h>
#include "Structure.hpp"

class Item;

class Tile {

public:
    static const int SIZE = 32;

    Tile(Vector2 position, const Texture2D& texture);
    virtual ~Tile() = default;

    virtual void Update();
    virtual void Draw() const;

    virtual bool IsWalkable() const = 0;
    virtual void Interact(const Item& tool) = 0;

    Vector2 GetPosition() const;
    Rectangle GetBounds() const;
    Texture2D GetTexture() const;

    Structure* GetStructure() const;
    bool HasStructure() const;
    void SetStructure(Structure* structure);

protected:
    Structure* structure = nullptr;

private:
    Vector2 position;
    Texture2D texture;

};