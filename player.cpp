#include "box2d/box2d.h"
#include "raylib.h"
#include "entity.hpp"
#include "player.hpp"

const int RATIO(32.0f);

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