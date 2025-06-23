#pragma once
#include <raylib.h>
#include <memory>
#include <vector>

class Block; // Forward

using BlockList = std::vector<std::shared_ptr<Block>>;

static constexpr float PLAYER_HEIGHT = 1.8f;

class Player {

public:
    Player();

    void Update(const BlockList& nearbyBlocks);
    void Draw();

    Vector3 GetPosition() const;
    void SetPosition(Vector3 position);

    bool IsOnGround() const;

private:
    Vector3 position;
    bool isOnGround;
    float moveSpeed;
    float velocityY;

};