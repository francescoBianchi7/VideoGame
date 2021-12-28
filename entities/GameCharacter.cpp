//
// Created by bianc on 26/12/2021.
//

#include "GameCharacter.h"

GameCharacter::GameCharacter(float x, float y,sf::Texture& texture) {
    this->initVariables();
    this->initComponents();

    this->setTexture(texture);
    this->setPosition(x,y);
}

GameCharacter::~GameCharacter() {

}

//init function
void GameCharacter::initVariables() {

}

void GameCharacter::initComponents() {
    this->createMovementComponent(300.f);
}
