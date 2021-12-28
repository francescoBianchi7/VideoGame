//
// Created by bianc on 27/12/2021.
//

#ifndef VIDEOGAME_MOVEMENTCOMPONENT_H
#define VIDEOGAME_MOVEMENTCOMPONENT_H

#include "ctime"
#include "iostream"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

class MovementComponent {
private:
    sf::Sprite& sprite;

    float maxVelocity;
    sf::Vector2f velocity;// speed and direction
    sf::Vector2f acceleration;
    sf::Vector2f deceleration;

public:
    MovementComponent(sf::Sprite& sprite,float maxVelocity);
    virtual ~MovementComponent();

    const sf::Vector2f& getVelocity() const;

    void move(const float &dt,float dir_x,float dir_y);
    void update(const float& dt);
};


#endif //VIDEOGAME_MOVEMENTCOMPONENT_H
