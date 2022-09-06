#ifndef VIDEOGAME_AICOMPONENT_H
#define VIDEOGAME_AICOMPONENT_H

#include "..\entities\Entity.h"

class AIcomponent {
private:
    Entity& entity;
    Entity& self;
    float dir_x=0,dir_y=0;
    sf::Int32 attackTimerMax;
    sf::Clock attackTimer;
    sf::Clock keepCurrentDirectionTimer;
    bool changeDirection;
public:
    AIcomponent(Entity& self, Entity& entity);
    ~AIcomponent();

    bool getDirectionTimer() const;
    bool getDamageTimer() const;
    void resetDirectionTimer();
    void resetDamageTimer();
    bool doDamage(const float& dt);
    sf::Vector2f calculateDistance();
    void moveRandomdirection(const float &dt);
    void update(const float& dt);
};


#endif //VIDEOGAME_AICOMPONENT_H
