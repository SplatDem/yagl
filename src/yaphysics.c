#include "yagl.h"

Hitbox CreateHitbox(float x, float y, float width, float height) {
    Hitbox hb;
    hb.left = x - width / 2.0f; hb.right = x + width / 2.0f;
    hb.bottom = y - height / 2.0f; hb.top = y + height / 2.0f;
    return hb;
}

void UpdateHitbox(Hitbox* hb, float x, float y) {
    float width = hb->right - hb->left;
    float height = hb->top - hb->bottom;
    hb->left = x - width / 2.0f; hb->right = x + width / 2.0f;
    hb->bottom = y - height / 2.0f; hb->top = y + height / 2.0f;
}

bool collision(const Hitbox* hb1, const Hitbox* hb2) {
    return !(hb1->right < hb2->left
            || hb1->left > hb2->right
            || hb1->top < hb2->bottom
            || hb1->bottom > hb2->top);
}

int CircleCollision(const CircleHitbox* c1, const CircleHitbox* c2) {
    float dx = c1->x - c2->x; float dy = c1->y - c2->y;
    float distanceSquared = dx * dx + dy * dy;
    float radiusSum = c1->radius + c2->radius;
    return distanceSquared <= radiusSum * radiusSum;
}

void InitObject(Object* obj, float x, float y, float width, float height) {
    obj->x = x; obj->y = y;
    obj->width = width; obj->height = height;
    obj->hitbox = CreateHitbox(x, y, width, height);
}

void UpdateObject(Object* obj, float newX, float newY) {
    obj->x = newX; obj->y = newY;
    UpdateHitbox(&obj->hitbox, newX, newY);
}
