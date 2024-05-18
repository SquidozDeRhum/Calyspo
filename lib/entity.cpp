#include <iostream>
#include "../include/entity.hpp"
#include "raylib.h"
#include "box2d/box2d.h"

const int RATIO(16.0f);

Entity::Entity(b2World & world, float x, float y, float width, float height, Texture2D &texture, bool staticbody): m_width(width), m_height(height), m_texture(texture) {
    bd.position.Set(x / RATIO, y / RATIO);
    if (staticbody) {
        bd.type = b2_staticBody;
    }
    else {
        bd.type = b2_dynamicBody;
    }
    bd.awake = true;
    bd.fixedRotation = true;

    shape.SetAsBox(width / RATIO / 2, height / RATIO / 2);

    fd.shape = &shape;
    fd.friction = 0.0f;
    fd.density = 1.0f;

    body = world.CreateBody(&bd);

    body->CreateFixture(&fd);

    body->SetFixedRotation(true);
}

Vector2 Entity::getRaylibPos()
{
    return Vector2{(body->GetPosition().x * RATIO), body->GetPosition().y * RATIO};
}

void Entity::render() {
    DrawTexture(m_texture, getRaylibPos().x, getRaylibPos().y, WHITE);
};