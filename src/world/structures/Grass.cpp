#include "world/structures/Grass.hpp"

Grass::Grass(Vector2 position, Texture2D) :
    Structure(position, texture, true) {}

void Grass::Interact() {
    TraceLog(LOG_DEBUG, "Interagiu");
}