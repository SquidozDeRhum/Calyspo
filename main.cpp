#include <iostream>
#include "raylib.h"
#include "box2d/box2d.h"

#include "include/entity.hpp"
#include "include/player.hpp"

const int screenWidth(400);

const int screenHeight(400);

const int frameRate(60);

const float RATIO(32.0f);

int main() {

    bool debug = false;

    SetTargetFPS(frameRate);

    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    Player feur(world, 200, 200, 20, 20, false);
    Entity ground(world, 200, 390, 200, 20);

    InitWindow(screenWidth, screenHeight, "Basic window");
    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(Color{127, 127, 127, 0});
            feur.render();
            feur.inputHandling();
            ground.render();
            if (debug) {

            }
        EndDrawing();
        world.Step(1.0f/frameRate, 6, 2);
    }

    CloseWindow();

    return 0;
}