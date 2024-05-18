#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "include/nlohmann/json.hpp"

using json = nlohmann::json;

#include "raylib.h"

std::ifstream tilemap("./assets/tilemap/calypso.json");
json tilemapJson = json::parse(tilemap);

std::ifstream texturesInfo("./assets/tilemap/sheet.json");
json texturesInfoJson = json::parse(texturesInfo);

std::vector<int> vec = tilemapJson["layers"][1]["data"];

std::map<int, Texture2D> textures;

int height = tilemapJson["layers"][1]["height"];
int width = tilemapJson["layers"][1]["width"];

int x, y;

int main() {

    InitWindow(width * 16, height * 16, "Json level creation");

    for (json::iterator it = texturesInfoJson["tiles"].begin(); it != texturesInfoJson["tiles"].end(); it++) {
        std::string value = it.value()["properties"][0]["value"];
        value = "./assets/textures/" + value;
        char *cvalue = value.data();
        int index = it.value()["id"];
        textures[index + 1] = LoadTexture(cvalue);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
            for(int i = 0; i < vec.size(); i++) {
                x = i % width;
                y = i / height;
                if (textures.find(vec[i]) != textures.end()) {
                    std::cout << vec[i] << std::endl;
                    DrawTexture(textures[vec[i]], x * 16, y * 16, WHITE);
                }
            }
        EndDrawing();
    }

    CloseWindow();
}