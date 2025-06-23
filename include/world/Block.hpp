#pragma once
#include <raylib.h>

class Block {

public:
    Block(Vector3 position, bool walkable, Color color);
    virtual ~Block() = default;

    virtual void Update();
    virtual void Draw() const;

    virtual bool IsWalkable() const;
    virtual void Interact();

    Vector3 GetPosition() const;
    BoundingBox GetBoundingBox() const;

protected:
    Vector3 position;
    bool walkable;
    Color color;

};