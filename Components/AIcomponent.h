#ifndef VIDEOGAME_AICOMPONENT_H
#define VIDEOGAME_AICOMPONENT_H

#include "..\entities\Entity.h"

class AIcomponent {
private:
    Entity& entity;
    Entity& self;

public:
    AIcomponent(Entity& self, Entity& entity);
    ~AIcomponent();

    sf::Vector2f calculateDistance();
    static sf::Vector2f moveRandomdirection();
    void update(const float& dt);
};


#endif //VIDEOGAME_AICOMPONENT_H
