//
// Created by bianc on 27/12/2021.
//

#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,float maxVelocity) :sprite(sprite),maxVelocity(maxVelocity){

}

MovementComponent::~MovementComponent() {

}

void MovementComponent::update(const float &dt) {

}

void MovementComponent::move(const float& dt,float dir_x, float dir_y) {
    this->velocity.x=this->maxVelocity*dir_x;
    this->velocity.y=this->maxVelocity*dir_y;
    this->sprite.move(this->velocity*dt);
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->velocity;
}
