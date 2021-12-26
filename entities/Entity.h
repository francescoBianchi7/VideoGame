//
// Created by bianc on 05/12/2021.
//

#ifndef VIDEOGAME_ENTITY_H
#define VIDEOGAME_ENTITY_H
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

class Entity {
private:

protected:
    //to test if it worked properly,later every entity it's gonna have
    //its own class
    sf::RectangleShape shape;
    float moveSpeed;
    sf::Shape* tempshape;

public:
    Entity();

    virtual ~Entity();

    virtual void move(const float&dt,float x,float y);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target);

};


#endif //VIDEOGAME_ENTITY_H
