
#include "Enemy.h"

void Enemy::initVariables() {
    speed=100.f;
}

void Enemy::initAnimations() {
    this->animationComponent->addAnimation("IDLE_DOWN",10.f,0,0,0,0,35,47);
    this->animationComponent->addAnimation("WALK_DOWN",10.f,0,0,3,0,35,47);
    this->animationComponent->addAnimation("WALK_UP",10.f,0,3,3,3,35,47);
    this->animationComponent->addAnimation("WALK_LEFT",10.f,0,1,3,1,35,47);
    this->animationComponent->addAnimation("WALK_RIGHT",10.f,0,2,3,2,35,47);
}

Enemy::Enemy(){
}

Enemy::~Enemy() {

}
