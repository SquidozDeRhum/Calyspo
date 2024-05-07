#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "box2d/box2d.h"
#include "raylib.h"

class Entity{
    protected:
        b2BodyDef bd;
        b2Body *body;
        b2PolygonShape shape;
        b2FixtureDef fd;
        b2Vec2 velocity;

        float m_width;
        float m_height;
        
    public:
        Entity(b2World & world, float x, float y, float width, float height, bool staticbody = true);
        void render();
        Vector2 getRaylibPos();
};

#endif // ENTITY_HPP