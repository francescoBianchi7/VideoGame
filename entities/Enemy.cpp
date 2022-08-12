
#include "Enemy.h"

void Enemy::initVariables() {
    speed=100.f;
}

void Enemy::initAnimations() {
    this->animationComponent->addAnimation("IDLE_DOWN",10.f,0,0,0,0,72,109);
    this->animationComponent->addAnimation("WALK_DOWN",10.f,0,0,3,0,72,109);
    this->animationComponent->addAnimation("WALK_UP",10.f,0,3,3,3,72,109);
    this->animationComponent->addAnimation("WALK_LEFT",10.f,0,1,3,1,72,109);
    this->animationComponent->addAnimation("WALK_RIGHT",10.f,0,2,3,2,72,109);
}

Enemy::Enemy( EnemySpawner& enemySpawner, float x, float y, sf::Texture &textureSheet):enemySpawner(enemySpawner) {
    initVariables();
    createMovementComponent(speed);
    createAnimationComponent(textureSheet);
    initAnimations();
    createHitboxComponent(20.f,20.f,35.f,85.f);
    setPosition(x,y);

}

Enemy::~Enemy() {

}

void Enemy::update(const float &dt,sf::Vector2f mousePosView) {
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

void Enemy::render(sf::RenderTarget &target, const bool show_hitbox) {
    target.draw(sprite);
    if(show_hitbox)
        hitboxComponent->render(target);
}
