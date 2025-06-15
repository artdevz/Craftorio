#include "core/Cam.hpp"

Cam::Cam(Vector2 target, Vector2 offset) {
    camera.target = target;
    camera.offset = offset;
    camera.rotation = 0;
    camera.zoom = 1.0;
}

void Cam::Update(Vector2 target) {
    camera.target = target;
    target = { (float)1280 / 2, (float)720 / 2};
    camera.offset = { (float)1280 / 2, (float)720 / 2};
}

Camera2D Cam::GetCamera2D() const { return camera; }