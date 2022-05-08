//
// Created by bianc on 26/12/2021.
//
#include "PreCompHeaders.h"
#include "GameCharacter.h"

GameCharacter::GameCharacter( float x, float y, sf::Texture &textureSheet){
    this->initVariables();
    this->createMovementComponent(300.f);
    this->createAnimationComponent(textureSheet);
    this->createHitboxComponent(20.f,20.f,this->sprite,35.f,85.f);
    this->setPosition(x,y);
    this->animationComponent->addAnimation("IDLE_DOWN",10.f,0,0,0,0,71,109);
    this->animationComponent->addAnimation("WALK_DOWN",10.f,0,0,3,0,72,109);
    this->animationComponent->addAnimation("WALK_UP",10.f,0,3,3,3,72,107);
    this->animationComponent->addAnimation("WALK_LEFT",10.f,0,1,3,1,72,109);
    this->animationComponent->addAnimation("WALK_RIGHT",10.f,0,2,3,2,72,107);
}

GameCharacter::~GameCharacter() {}

//init function
void GameCharacter::initVariables() {
}

void GameCharacter::initComponents() {
}

void GameCharacter::update(const float &dt) {//updates which animation is playing and components
    this->movementComponent->update(dt);
    if(!movementComponent->isMoving())
        this->animationComponent->play("IDLE_DOWN",dt);
    else if(movementComponent->getVelocityX()>0.f)
        this->animationComponent->play("WALK_RIGHT",dt);
    else if(movementComponent->getVelocityX()<0.f)
        this->animationComponent->play("WALK_LEFT",dt);
    else if(movementComponent->getVelocityY()<0.f)
        this->animationComponent->play("WALK_UP",dt);
    else if(movementComponent->getVelocityY()>0.f)
        this->animationComponent->play("WALK_DOWN",dt);
    this->hitboxComponent->update();
}

