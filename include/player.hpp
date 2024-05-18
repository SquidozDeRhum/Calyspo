#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "box2d/box2d.h"
#include "raylib.h"
#include "entity.hpp"

class Player : public Entity {
    public:
        void positionProcess();
        using Entity::Entity;
    private:
        b2Vec2 velocity;
};


#endif // PLAYER_HPP