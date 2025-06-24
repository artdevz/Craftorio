#pragma once
#include <raylib.h>
#include "enums/BlockType.hpp"

class Block {

public:
    Block(Vector3 position, BlockType type);
    virtual ~Block() = default;

    virtual void Update();
    virtual void Draw() const;

    virtual bool IsWalkable() const;
    virtual void Interact();

    Vector3 GetPosition() const;
    BoundingBox GetBoundingBox() const;

protected:
    Vector3 position;
    BlockType type;

};