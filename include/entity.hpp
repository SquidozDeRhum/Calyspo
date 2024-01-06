#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "./raylib.h"

class Entity {
    public:
        Entity();
        Entity(float x, float y,int height, int width);
        void render();
        Rectangle collision;
        Vector2 one, four;
};

#endif // ENTITY_HPP