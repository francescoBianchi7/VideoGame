//
// Created by bianc on 27/12/2021.
//
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,float speed)
: sprite(sprite), speed(speed){}

MovementComponent::~MovementComponent() = default;
//
//GETTER & SETTER
//
bool MovementComponent::isMoving() const {
    if(velocity.x==0.f && velocity.y==0.f)
        return false;
    else
        return true;
}
const float& MovementComponent::getVelocityX() const{
    return this->velocity.x;
}
const float& MovementComponent::getVelocityY() const{
    return this->velocity.y;
}
const sf::Vector2f &MovementComponent::getVelocity() {
    return this->velocity;
}
const float &MovementComponent::getSpeed() const {
    return this->speed;
}

void MovementComponent::stopVelocity()
{/* Resets the velocity to 0.*/
    this->velocity.x = 0.f;
    this->velocity.y = 0.f;
}
void MovementComponent::stopVelocityX() {
    /* collisions*/
    this->velocity.x=0.f;
}
void MovementComponent::stopVelocityY() {
    /* collisions*/
    this->velocity.y=0.f;
}

//updating
void MovementComponent::update(const float &dt) {
    sprite.move(velocity * dt); //Uses velocity
}
//accelerates
void MovementComponent::move(const float& dt,float dir_x, float dir_y) {
    velocity.x= speed * dir_x;
    velocity.y= speed * dir_y;
}

void MovementComponent::updateSpeed(int speed) {
    this->speed=speed;
}
