#include <iostream>
#include "entity.hpp"
#include "raylib.h"
#include "box2d/box2d.h"

const int RATIO(32.0f);

Entity::Entity(b2World & world, float x, float y, float width, float height, bool staticbody): m_width(width), m_height(height) {
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
    fd.friction = 1.0f;
    fd.density = 1.0f;

    body = world.CreateBody(&bd);

    body->CreateFixture(&fd);

    body->SetFixedRotation(true);
}

Vector2 Entity::getRaylibPos()
{
    return Vector2{(body->GetPosition().x * RATIO - m_width/2), body->GetPosition().y * RATIO - m_height / 2};
}

void Entity::render() {
    DrawRectangleV(getRaylibPos(), Vector2{m_width, m_height}, RED);
};