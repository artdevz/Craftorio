#pragma once
#include <raylib.h>
#include "Structure.hpp"

class Tile {

public:
    static const int SIZE = 32;

    Tile();
    Tile(Vector2 position, bool isWalkable, const Texture2D& texture);

    void Update();
    void Draw() const;

    Vector2 GetPosition() const;
    bool IsWalkable() const;
    Structure* GetStructure() const;
    bool HasStructure() const;

    void SetStructure(Structure* structure);

private:
    Vector2 position;
    bool isWalkable;
    Texture2D texture;
    Structure* structure = nullptr;

};