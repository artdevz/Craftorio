#include "world/structures/Rock.hpp"

Rock::Rock(Vector2 position, Texture2D texture) :
    Structure(position, texture, false) {}

void Rock::Interact() {
    TraceLog(LOG_INFO, "Interagiu");
}