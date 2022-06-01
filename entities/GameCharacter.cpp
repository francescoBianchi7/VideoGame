//
// Created by bianc on 26/12/2021.
//

#include "GameCharacter.h"
GameCharacter::GameCharacter() {
    speed=300.f;
    this->createHitboxComponent(20.f,20.f,35.f,85.f);
    this->createMovementComponent(speed);
    this->setPosition(0,0);
}
GameCharacter::GameCharacter( float x, float y, sf::Texture &textureSheet){
    this->initVariables();
    this->createMovementComponent(speed);
    this->createAnimationComponent(textureSheet);
    this->createHitboxComponent(20.f,20.f,35.f,85.f);
    this->setPosition(x,y);
    this->animationComponent->addAnimation("IDLE_DOWN",10.f,0,0,0,0,72,109);
    this->animationComponent->addAnimation("WALK_DOWN",10.f,0,0,3,0,72,109);
    this->animationComponent->addAnimation("WALK_UP",10.f,0,3,3,3,72,109);
    this->animationComponent->addAnimation("WALK_LEFT",10.f,0,1,3,1,72,109);
    this->animationComponent->addAnimation("WALK_RIGHT",10.f,0,2,3,2,72,109);
}

GameCharacter::~GameCharacter()= default;

//init function
void GameCharacter::initVariables() {
    speed=300.f;
}

void GameCharacter::initComponents(){}

void GameCharacter::update(const float &dt) {
    updateInput(dt);//updates which animation is playing and components
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

void GameCharacter::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        this->movementComponent->move(dt,0.f,-1.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        this->movementComponent->move(dt,0.f,1.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        this->movementComponent->move(dt,1.f,0.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        this->movementComponent->move(dt,-1.f,0.f);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    &!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        stopVelocity();
    }
}

