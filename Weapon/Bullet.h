//
// Created by bianc on 01/08/2022.
//

#ifndef VIDEOGAME_BULLET_H
#define VIDEOGAME_BULLET_H

#include "PreCompHeaders.h"
class Bullet {
private:

    float range;
    float speed;

public:
    sf::CircleShape bulletShape;
    sf::Vector2f direction;
    sf::Vector2f startingPos;
    //CON & DES
    Bullet(float radius=5.f,float speed=15.f);
    virtual ~Bullet();
    //SETTER
    void setDirection(sf::Vector2f& mousePosView);
    void setStartingPosition(float x,float y);
    //GETTER
    float getDistanceTravelled() const;
    float getRange();
    //FUNCTIONS
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_BULLET_H
