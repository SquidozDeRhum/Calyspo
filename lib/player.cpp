#include <iostream>
#include "../include/player.hpp"
#include "../include/raylib.h"
#include "../include/entity.hpp"

Player::Player(Camera2D & cam) : velocity{200, 200}, camera(cam), debug(false), one{0, 0}, four{one.x + collision.width - 1, one.y + collision.height - 1}, center{one.x + collision.width / 2, one.y + collision.height / 2}{
    perso = LoadTexture("./assets/character.png");
    camera.target = center;
    collision = (Rectangle){one.x, one.y, 32, 32};
}

void Player::keyhandling() {
        if (IsKeyDown(KEY_A)) {
            left = true;
        }
        if (IsKeyDown(KEY_D)) {
            right = true;
        }
        if (IsKeyDown(KEY_W)) {
            up = true;
        }
        if (IsKeyDown(KEY_S)) {
            down = true;
        }
        if (IsKeyUp(KEY_A)) {
            left = false;
        }
        if (IsKeyUp(KEY_D)) {
            right = false;
        }
        if (IsKeyUp(KEY_W)) {
            up = false;
        }
        if (IsKeyUp(KEY_S)) {
            down = false;
        }
        if (IsKeyPressed(KEY_Y)) {
            if (debug) {
                debug = false;
            }
            else {
                debug = true;
            }
        }
}

void Player::move() {
    keyhandling();
    if (up) one.y -= int(velocity.y * GetFrameTime());
    if (down) one.y += int(velocity.y * GetFrameTime());
    if (right) one.x += int(velocity.x * GetFrameTime());
    if (left) one.x -= int(velocity.x * GetFrameTime());
    camera.target = center;
    collision.x = one.x;
    collision.y = one.y;
    four = {one.x + collision.width - 1, one.y + collision.height - 1};
    center = {one.x + collision.width / 2, one.y + collision.height / 2};
}

void Player::render() {
    DrawTexture(perso, one.x, one.y, WHITE);
    if (debug) {
        DrawRectangleLinesEx(collision, 1.0f, WHITE);
        DrawRectangle(one.x, one.y, 1, 1, BLUE);
        DrawRectangle(four.x, four.y, 1, 1, YELLOW);
        DrawRectangle(center.x, center.y, 1, 1, GREEN);
    }
}

void Player::statRender() {
    if (debug) {
        DrawText(TextFormat("X : %i", int(one.x)), 0, 0, 20, WHITE);
        DrawText(TextFormat("Y : %i", int(one.y)), 0, 25, 20, WHITE);
        DrawFPS(0, 40);
        DrawText(TextFormat("DT : %i", GetFrameTime()), 0, 60, 20, WHITE);
    }
}

Camera2D Player::rCamera() {
    return camera;
}

void Player::detectCollision(Entity entity) {
    if (CheckCollisionRecs(collision, entity.collision)) {
        std::cout << entity.four.x << " " << one.x << std::endl;
        // En haut
        if ((four.y > entity.one.y) && (four.y < entity.one.y + 4)) {
            one.y = entity.one.y - collision.height;
        }
        // En basitr
        if ((one.y < entity.four.y) && (one.y > entity.four.y - 4) && (one.x > entity.one.x - collision.width + 4)  && (four.x < entity.four.x + collision.width - 4)) {
            one.y = entity.four.y + 1;
        }
        // A droite
        if ((one.x < entity.four.x) && (one.x > entity.four.x - 4) && (one.y > entity.four.y - entity.collision.height - collision.height + 4) && (entity.four.y > one.y)) {
            one.x = entity.four.x + 1;
        }
        // A gauche
        if ((four.x > entity.one.x) && (four.x < entity.one.x + 4)) {
            one.x = entity.one.x - collision.width;
        }
        four.y = one.y + collision.height - 1;
        four.x = one.x + collision.width - 1;
        center = {one.x + collision.width / 2, one.y + collision.height / 2};
        collision.y = one.y;
        collision.x = one.x;
    }
    if (CheckCollisionPointRec(center, entity.collision)) {
        one.y += collision.height;
    }
    if (debug) {
        DrawRectangleRec(GetCollisionRec(collision, entity.collision), (Color){0, 0, 40, 110});
    }
}
