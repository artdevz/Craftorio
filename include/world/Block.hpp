#pragma once
#include <raylib.h>
#include "enums/BlockType.hpp"

class Block {

public:
    Block(Vector3 position, BlockType type) :
        position(position), type(type) {};
    virtual ~Block() = default;

    virtual void Update() = 0;
    virtual void Draw() const = 0;
    virtual bool IsSolid() const = 0;
    virtual void Interact() = 0;

    Vector3 GetPosition() const { return position; };

    BoundingBox GetBoundingBox() const {
        return {
            {position.x - 0.5f, position.y - 0.5f, position.z - 0.5f},
            {position.x + 0.5f, position.y + 0.5f, position.z + 0.5f}
        };
    };

protected:
    Vector3 position;
    BlockType type;
    bool solid;

};