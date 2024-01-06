#include <iostream>
#include "../include/player.hpp"
#include "../include/raylib.h"
#include "../include/entity.hpp"

Player::Player(Camera2D & cam) : m_x(0), m_y(0), velocity{200, 200}, camera(cam), debug(false), one{m_x, m_y}, four{m_x + collision.width - 1, m_y + collision.height - 1}, center{m_x + collision.width / 2, m_y + collision.height / 2}, up(false), down(false), right(false), left(false) {
    perso = LoadTexture("./assets/character.png");
    camera.target = center;
    collision = (Rectangle){m_x, m_y, 32, 32};
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
    if (up) m_y -= int(velocity.y * GetFrameTime());
    if (down) m_y += int(velocity.y * GetFrameTime());
    if (right) m_x += int(velocity.x * GetFrameTime());
    if (left) m_x -= int(velocity.x * GetFrameTime());
    camera.target = center;
    collision.x = m_x;
    collision.y = m_y;
    one = {m_x, m_y};
    four = {m_x + collision.width - 1, m_y + collision.height - 1};
    center = {m_x + collision.width / 2, m_y + collision.height / 2};
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
        DrawText(TextFormat("X : %i", int(m_x)), 0, 0, 20, WHITE);
        DrawText(TextFormat("Y : %i", int(m_y)), 0, 25, 20, WHITE);
        DrawFPS(0, 40);
        DrawText(TextFormat("DT : %i", GetFrameTime()), 0, 60, 20, WHITE);
    }
}

Camera2D Player::rCamera() {
    return camera;
}

void Player::detectCollision(Entity entity) {
    if (CheckCollisionRecs(collision, entity.collision)) {
        // En haut
        if ((four.y > entity.one.y) && (four.y < entity.one.y + 4)) {
            m_y = entity.one.y - collision.height;
            check = true;
        }
        // En bas
        if ((one.y < entity.four.y) && (one.y > entity.four.y - 4)) {
            m_y = entity.four.y + 1;
            check = true;
        }
        // A droite
        if ((one.x < entity.four.x) && (one.x > entity.four.x - 4)) {
            m_x = entity.four.x + 1;
            check = true;
        }
        // A gauche
        if ((four.x > entity.one.x) && (four.x < entity.one.x + 4)) {
            m_x = entity.one.x - collision.width;
            check = true;
        }
    }
    if (CheckCollisionPointRec(center, entity.collision)) {
        m_y += collision.height;
    }
    if (debug) {
        DrawRectangleRec(GetCollisionRec(collision, entity.collision), (Color){0, 0, 40, 110});
        std::cout << "Collision : " << CheckCollisionRecs(collision, entity.collision) << std::endl;
    }
}
