#include <iostream>
#include <vector>
#include "./include/raylib.h"
#include "player.hpp"

int main() {
    std::srand(time(0));
    std::vector<Rectangle> rd(30);
    for (int i(0); i< rd.size(); i++) {
        rd[i] = (Rectangle){int(std::rand() % 500), int(std::rand() % 500), 50, 50};
    }
    InitWindow(600, 600, "First release of Calypso");
    Camera2D camera;
    camera = {0};
    camera.offset = (Vector2){300, 300};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    Player player(camera);
    SetTargetFPS(60);
    Rectangle rec2{500, 500, 50, 50};
    Texture2D grass(LoadTexture(".\\grass.png"));    
    std::cout << GetWorkingDirectory() << std::endl;
    while (!WindowShouldClose()) {
        camera = player.rCamera();
        BeginDrawing();
            ClearBackground(BLACK);
            BeginMode2D(camera);
                for (int i(-1024); i < 1024; i += 32) {
                    for (int p(-1024); p < 1024; p += 32) {
                        DrawTexture(grass, i, p, WHITE);
                    }
                }
                for (int i(0); i< rd.size(); i++) {
                    DrawRectangleRec(rd[i], WHITE);
                    player.detectCollision(rd[i]);
                }
                DrawRectangleRec(rec2, WHITE);
                player.render();
                player.detectCollision(rec2);
            EndMode2D();
            player.statRender();
        EndDrawing();
        player.move();
    }
    CloseWindow();

    return 0;
}