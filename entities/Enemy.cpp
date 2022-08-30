
#include "Enemy.h"

void Enemy::initVariables(Entity& player) {
    speed=100.f;
    AI=new AIcomponent(*this, player);
}

void Enemy::createAIcomponent(Entity &Self, Entity &player) {
    AI = new AIcomponent(*this, player);
}

void Enemy::initAnimations() {
    this->animationComponent->addAnimation("IDLE_DOWN",10.f,0,0,0,0,35,47);
    this->animationComponent->addAnimation("WALK_DOWN",10.f,0,0,3,0,35,47);
    this->animationComponent->addAnimation("WALK_UP",10.f,0,3,3,3,35,47);
    this->animationComponent->addAnimation("WALK_LEFT",10.f,0,1,3,1,35,47);
    this->animationComponent->addAnimation("WALK_RIGHT",10.f,0,2,3,2,35,47);
}
///getter

Enemy::Enemy(){
}

Enemy::~Enemy() {
    delete AI;
}

bool Enemy::isDead() {
    if(attributeComponent){
        return attributeComponent->isDead();
    }
}

AIcomponent *Enemy::getAi() {
    return AI;
}

