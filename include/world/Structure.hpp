#pragma once
#include <raylib.h>

class Structure {

public:
    Structure();
    Structure(Vector2 position, const Texture2D& texture, Rectangle hitbox, bool isWalkable);
    virtual ~Structure() = default;

    virtual void Update();
    virtual void Draw(Vector2 playerPosition) const;
    virtual void Interact();

    Vector2 GetPosition() const;
    Rectangle GetBounds() const;
    Rectangle GetHitBox() const;
    bool IsWalkable() const;

protected:
    int baseOffset = 32; // Quantidade de Pixel que a textura tá "acima" da posição real (Hitbox)
    Vector2 position;
    Texture2D texture;
    Rectangle hitbox;
    bool isWalkable;

};