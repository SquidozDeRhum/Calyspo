#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>

#include "../include/nlohmann/json.hpp"

using json = nlohmann::json;

#include "raylib.h"
#include "box2d/box2d.h"
#include "../include/entity.hpp"

std::vector<Entity> levelLoading(std::string level, b2World & world) {

    std::string path =  "./assets/tilemaps/" + level + "/";

    std::cout << path + "calypso.json" << std::endl;

    std::ifstream tilemap(path + "calypso.json");
    json tilemapJson = json::parse(tilemap);

    std::ifstream texturesInfo(path + "sheet.json");
    json texturesInfoJson = json::parse(texturesInfo);

    std::vector<int> vec = tilemapJson["layers"][1]["data"];

    std::map<int, Texture2D> textures;

    int height = tilemapJson["layers"][1]["height"];
    int width = tilemapJson["layers"][1]["width"];

    std::vector<Entity> entities;

    for (json::iterator it = texturesInfoJson["tiles"].begin(); it != texturesInfoJson["tiles"].end(); it++) {
        std::string value = it.value()["properties"][0]["value"];
        value = "./assets/textures/" + value;
        char *cvalue = value.data();
        int index = it.value()["id"];
        textures[index + 1] = LoadTexture(cvalue);
    }

    for(int i = 0; i < vec.size(); i++) {
        int x = i % width * 16;
        int y = i / height * 16;
        if (textures.find(vec[i]) != textures.end()) {
            entities.push_back(Entity(world, x, y, 16, 16, textures[vec[i]]));
        }
    }

    return entities;
}