//
// Created by bianc on 26/12/2021.
//
#include "PreCompHeaders.h"
#include "GameCharacter.h"

GameCharacter::GameCharacter( float x, float y, sf::Texture &textureSheet){
    this->initVariables();
    this->createMovementComponent(140.f,20.f,3.f);
    this->createAnimationComponent(textureSheet);
    this->createHitboxComponent(20.f,20.f,this->sprite,35.f,75.f);
    this->setPosition(x,y);
    this->animationComponent->addAnimation("IDLE_DOWN",10.f,0,0,0,0,71,109);
    this->animationComponent->addAnimation("WALK_DOWN",10.f,0,0,3,0,72,109);
    this->animationComponent->addAnimation("WALK_UP",10.f,0,3,3,3,72,107);
    this->animationComponent->addAnimation("WALK_LEFT",10.f,0,1,3,1,72,109);
    this->animationComponent->addAnimation("WALK_RIGHT",10.f,0,2,3,2,72,107);
}

GameCharacter::~GameCharacter() {

}

//init function
void GameCharacter::initVariables() {

}

void GameCharacter::initComponents() {
}

void GameCharacter::update(const float &dt) {
    if(this->movementComponent->getState(IDLE)){
        this->animationComponent->play("IDLE_DOWN",dt);
    }
    else if(this->movementComponent->getState(MOVING_DOWN))
        this->animationComponent->play("WALK_DOWN",dt);
    else if(this->movementComponent->getState(MOVING_UP))
        this->animationComponent->play("WALK_UP",dt);
    else if(this->movementComponent->getState(MOVING_LEFT))
        this->animationComponent->play("WALK_LEFT",dt);
    else if(this->movementComponent->getState(MOVING_RIGHT))
        this->animationComponent->play("WALK_RIGHT",dt);
    this->movementComponent->update(dt);

    this->hitboxComponent->update();
}

