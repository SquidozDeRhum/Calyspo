#include "raylib.h"

class Player {
    public:
        Player(Camera2D & cam);
        void keyhandling();
        void move();
        void render();
        void statRender();
        void detectCollision(Rectangle entity);
        Camera2D rCamera();
    private:
        Texture2D perso;
        float m_x, m_y;
        int vspeed, hspeed;
        bool up, down, right, left, debug;
        Camera2D camera;
        Rectangle collision;
};

Player::Player(Camera2D & cam) : m_x(0), m_y(0), vspeed(200), hspeed(200), camera(cam), debug(false){
    perso = LoadTexture("./character.png");
    camera.target = (Vector2){m_x, m_y};
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
    if (up) m_y += int(-vspeed * GetFrameTime());
    if (down) m_y += int(vspeed * GetFrameTime());
    if (right) m_x += int(hspeed * GetFrameTime());
    if (left) m_x += int(-hspeed * GetFrameTime());
    camera.target = (Vector2){m_x, m_y};
    collision.x = m_x;
    collision.y = m_y;
}

void Player::render() {
    DrawTexture(perso, m_x, m_y, WHITE);
    if (debug) {
        DrawRectangleLinesEx(collision, 2.0f, WHITE);
    }
}

void Player::statRender() {
    if (debug) {
        DrawText(TextFormat("X : %i", int(m_x)), 0, 0, 20, WHITE);
        DrawText(TextFormat("Y : %i", int(m_y)), 0, 25, 20, WHITE);
        DrawFPS(0, 40);
        DrawText(TextFormat("DT : %i", GetFrameTime()), 0, 60, 20, WHITE);
        DrawText(TextFormat("Dowm : %i", down), 0, 85, 20, WHITE);
    }
}

Camera2D Player::rCamera() {
    return camera;
}

void Player::detectCollision(Rectangle entity) {
    if (down && CheckCollisionRecs(collision, entity) && collision.y < entity.y){
        vspeed = 0;
    }
    else if (up && CheckCollisionRecs(collision, entity) && collision.y > entity.y){
        vspeed = 0;
    }
    else {
        vspeed = 200;
    }
    if (right && CheckCollisionRecs(collision, entity) && collision.x < entity.x){
        hspeed = 0;
    }
    else if (left && CheckCollisionRecs(collision, entity) && collision.x > entity.x){
        hspeed = 0;
    }
    else {
        hspeed = 200;
    }
    if (debug) {
        DrawRectangleRec(GetCollisionRec(collision, entity), (Color){0, 0, 40, 120});
    }
}