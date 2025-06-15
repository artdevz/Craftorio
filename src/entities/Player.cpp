#include "entities/Player.hpp"
#include "core/Input.hpp"

Player::Player() {
    position = {0, 0};
    moveSpeed = 100.0f;
}

void Player::Update() {
    float deltaTime = GetFrameTime();
    float sprint = 1;
    if (Input::IsRunning()) sprint *= 2.5;
    if (Input::IsMovingUp()) position.y -= moveSpeed * deltaTime * sprint;
    if (Input::IsMovingLeft()) position.x -= moveSpeed * deltaTime * sprint;
    if (Input::IsMovingDown()) position.y += moveSpeed * deltaTime * sprint;
    if (Input::IsMovingRight()) position.x += moveSpeed * deltaTime * sprint;
    
}

void Player::Draw() {
    DrawCircleV(position, 16, GREEN);
    TraceLog(LOG_DEBUG, "Desenhando player");
}

Vector2 Player::GetPosition() const { return this->position; }