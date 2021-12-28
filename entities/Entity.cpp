//
//Base class for all entities
//TBD: make it easier to inherit

#include "Entity.h"

Entity::Entity() {
    this->initVariables();//to store important vars

}

Entity::~Entity() {

}

void Entity::move(const float&dt,float dir_x, float dir_y) {
    if(this->movementComponent){
        this->movementComponent->move(dt,dir_x,dir_y);
    }
}

void Entity::render(sf::RenderTarget* target) {
    target->draw(sprite);
}

void Entity::update(const float& dt) {
}

void Entity::setTexture(sf::Texture& texture) {
    this->sprite.setTexture(texture);
}

void Entity::initVariables() {
    this->movementComponent= nullptr;

}

void Entity::setPosition(float x, float y) {
        this->sprite.setPosition(x,y);
}

void Entity::createMovementComponent(const float maxVelocity) {
    this->movementComponent=new MovementComponent(this->sprite,maxVelocity);
}

