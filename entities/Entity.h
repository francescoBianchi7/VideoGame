//
// Created by bianc on 05/12/2021.
//

#ifndef VIDEOGAME_ENTITY_H
#define VIDEOGAME_ENTITY_H
#include "ctime"
#include "iostream"
#include "../Components/MovementComponent.h"
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

class Entity {
private:
    void initVariables();
protected:
    //to test if it worked properly,later every entity it's gonna have
    //its own class


    sf::Sprite sprite;

    MovementComponent* movementComponent;
public:
    Entity();
    virtual ~Entity();
    //init
    virtual void setPosition(float x,float y);
    void setTexture(sf::Texture& texture);
    void createMovementComponent(float maxVelocity);


    virtual void move(const float&dt,float x,float y);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target);

};


#endif //VIDEOGAME_ENTITY_H
