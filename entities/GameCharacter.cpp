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
    initVariables();
    createMovementComponent(speed);
    createAnimationComponent(textureSheet);
    createHitboxComponent(20.f,20.f,35.f,85.f);
    setPosition(x,y);
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
Rifle GameCharacter::getWeapon() {
    return rifle;
}
void GameCharacter::initComponents(){}
void GameCharacter::update(const float &dt,sf::Vector2f mouseposView) {
   //updates which animation is playing and components
    movementComponent->update(dt);
    if(!movementComponent->isMoving())
        animationComponent->play("IDLE_DOWN",dt);
    else if(movementComponent->getVelocityX()>0.f)
        animationComponent->play("WALK_RIGHT",dt);
    else if(movementComponent->getVelocityX()<0.f)
        animationComponent->play("WALK_LEFT",dt);
    else if(movementComponent->getVelocityY()<0.f)
        animationComponent->play("WALK_UP",dt);
    else if(movementComponent->getVelocityY()>0.f)
        animationComponent->play("WALK_DOWN",dt);
    hitboxComponent->update();
    rifle.update(mouseposView,getCenter());
}
void GameCharacter::render(sf::RenderTarget &target, const bool show_hitbox) {
    target.draw(sprite);
    rifle.render(target);
    if(show_hitbox)
        hitboxComponent->render(target);
}
/*void GameCharacter::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key(keybinds.at("M))){
        movementComponent->move(dt,0.f,-1.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        movementComponent->move(dt,0.f,1.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        movementComponent->move(dt,1.f,0.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        movementComponent->move(dt,-1.f,0.f);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    &!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        stopVelocity();
    }
}*/

//this function are used for testing purposes
//during the testing, the updateInput function is unusable
//because Keyboard cannot be pressed.
void GameCharacter::moveLeft(const float &dt) {
    movementComponent->move(dt,-1.f,0.f);
    movementComponent->update(dt);
}
void GameCharacter::moveRight(const float &dt) {
    movementComponent->move(dt,1.f,0.f);
    movementComponent->update(dt);
}
void GameCharacter::moveUp(const float &dt) {
    movementComponent->move(dt,0.f,-1.f);
    movementComponent->update(dt);
}
void GameCharacter::moveDown(const float &dt) {
    movementComponent->move(dt,0.f,1.f);
    movementComponent->update(dt);
}
