//
// Created by bianc on 26/12/2021.
//

#ifndef VIDEOGAME_GAMECHARACTER_H
#define VIDEOGAME_GAMECHARACTER_H


#include "Entity.h"

class GameCharacter: public Entity {
private:
    //variables
    float speed;
    void initVariables();
    void initComponents();//each entity it's going ot have his own
public:
    GameCharacter();
    GameCharacter(float x, float y, sf::Texture &textureSheet);
    ~GameCharacter() override;
    void moveRight(const float &dt);
    void moveLeft(const float &dt);
    void moveUp(const float &dt);
    void moveDown(const float &dt);
    void update(const float& dt) override;
    void updateInput(const float & dt);
};


#endif //VIDEOGAME_GAMECHARACTER_H
