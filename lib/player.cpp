#include "box2d/box2d.h"
#include "raylib.h"
#include "../include/entity.hpp"
#include "../include/player.hpp"

#include <iostream>

const int RATIO(16.0f);

void Player::positionProcess() {
    if (IsKeyDown(KEY_A)) {
        velocity = body->GetLinearVelocity();
        velocity.x = -16.0f;
        body->SetLinearVelocity(velocity);
    }
    if (IsKeyDown(KEY_D)) {
        velocity = body->GetLinearVelocity();
        velocity.x = 16.0f;
        body->SetLinearVelocity(velocity);
    }
    if (IsKeyDown(KEY_SPACE) && getRaylibPos().y > 270) {
        velocity = body->GetLinearVelocity();
        velocity.y = -6.0f;
        body->SetLinearVelocity(velocity);
    }
    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
        velocity = body->GetLinearVelocity();
        velocity.x = 0.0f;
        body->SetLinearVelocity(velocity);
    }

    if (getRaylibPos().y > 500) {
        body->SetTransform(b2Vec2{200 / RATIO, 100 / RATIO}, body->GetAngle());
    }
}