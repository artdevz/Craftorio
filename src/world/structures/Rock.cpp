#include "world/structures/Rock.hpp"

Rock::Rock(Vector2 position, Texture2D texture) :
    Structure(position, texture, {0, 0, 0, 0}, false) {}

void Rock::Interact() {
    TraceLog(LOG_INFO, "Interagiu");
}