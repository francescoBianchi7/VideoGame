//
// Created by bianc on 15/08/2022.
//

#include "BaldZombie.h"
void BaldZombie::initVariables() {
    speed=100.f;
}

void BaldZombie::initAnimations() {
    this->animationComponent->addAnimation("IDLE_DOWN",10.f,0,0,0,0,35,47);
    this->animationComponent->addAnimation("WALK_DOWN",10.f,0,0,3,0,35,47);
    this->animationComponent->addAnimation("WALK_UP",10.f,0,3,3,3,35,47);
    this->animationComponent->addAnimation("WALK_LEFT",10.f,0,1,3,1,35,47);
    this->animationComponent->addAnimation("WALK_RIGHT",10.f,0,2,3,2,35,47);
}

BaldZombie::BaldZombie(float x, float y, sf::Texture &textureSheet)
        : Enemy() {
    initVariables();
    createMovementComponent(speed);
    createAnimationComponent(textureSheet);
    initAnimations();
    createHitboxComponent(8.f,6.f,30.f,42.f);
    setPosition(x,y);

}

BaldZombie::~BaldZombie() {

}

void BaldZombie::update(const float &dt,sf::Vector2f mousePosView) {
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
}

void BaldZombie::render(sf::RenderTarget &target, const bool show_hitbox) {
    target.draw(sprite);
    if(show_hitbox)
        hitboxComponent->render(target);
}