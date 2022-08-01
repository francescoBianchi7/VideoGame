//
// Created by bianc on 01/08/2022.
//

#ifndef VIDEOGAME_BULLET_H
#define VIDEOGAME_BULLET_H

#include "PreCompHeaders.h"
class Bullet {

    sf::CircleShape bulletShape;
    sf::Vector2f direction;
    sf::Vector2f startingPos;
    float range;
    float speed;

public:
    //CON & DES
    Bullet(float radius,float speed,sf::Vector2f startingPos);
    virtual ~Bullet();
    //SETTER
    void setDirection(sf::Vector2f& mousePosView);
    void setStartingPosition(sf::Vector2f position);
    //GETTER
    float getDistanceTravelled() const;
    //FUNCTIONS
    void update(const float& dt);
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_BULLET_H
