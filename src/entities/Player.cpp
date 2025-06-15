#include "entities/Player.hpp"
#include "core/Input.hpp"

Player::Player() {
    position = {0, 0};
    moveSpeed = 100.0f;
}

void Player::Update() {
    float deltaTime = GetFrameTime();
    if (Input::IsMovingUp()) position.y -= moveSpeed * deltaTime;
    if (Input::IsMovingLeft()) position.x -= moveSpeed * deltaTime;
    if (Input::IsMovingDown()) position.y += moveSpeed * deltaTime;
    if (Input::IsMovingRight()) position.x += moveSpeed * deltaTime;
    
}

void Player::Draw() {
    DrawCircleV(position, 16, GREEN);
    TraceLog(LOG_DEBUG, "Desenhando player");
}

Vector2 Player::GetPosition() const { return this->position; }