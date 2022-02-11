//
// Created by bianc on 26/12/2021.
//

#ifndef VIDEOGAME_GAMECHARACTER_H
#define VIDEOGAME_GAMECHARACTER_H


#include "Entity.h"

class GameCharacter: public Entity {
private:
    //variables

    void initVariables();
    void initComponents();//each entity it's gonna have it's own
public:

    GameCharacter(float x, float y, sf::Texture &textureSheet);
    virtual ~GameCharacter();
    void update(const float& dt);
};


#endif //VIDEOGAME_GAMECHARACTER_H
