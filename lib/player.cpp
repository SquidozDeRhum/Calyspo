#include "box2d/box2d.h"
#include "raylib.h"
#include "../include/entity.hpp"
#include "../include/player.hpp"

void Player::inputHandling() {
    if (IsKeyDown(KEY_A)) {
        velocity = body->GetLinearVelocity();
        velocity.x = -8.0f;
        body->SetLinearVelocity(velocity);
    }
    if (IsKeyDown(KEY_D)) {
        velocity = body->GetLinearVelocity();
        velocity.x = 8.0f;
        body->SetLinearVelocity(velocity);
    }
    if (IsKeyUp(KEY_A) && IsKeyUp(KEY_D)) {
        velocity = body->GetLinearVelocity();
        velocity.x = 0.0f;
        body->SetLinearVelocity(velocity);
    }
}