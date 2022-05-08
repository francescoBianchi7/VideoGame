//
// Created by bianc on 27/12/2021.
//
#include "PreCompHeaders.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,float speed)
: sprite(sprite), speed(speed){}

MovementComponent::~MovementComponent() {}
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
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        move(dt,0.f, -1.f);
        sprite.move(0.f, -speed * dt);
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        move(dt,0.f, 1.f);
        sprite.move(0.f, speed * dt);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        move(dt,-1.f, 0.f);
        sprite.move(-speed * dt, 0.f);

    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        move(dt,1.f, 0.f);
        sprite.move(speed * dt, 0.f);

    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    &!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        stopVelocity();
    }
    //Final move
    //this->sprite.move(this->velocity * dt); //Uses velocity
}
//accelerates
void MovementComponent::move(const float& dt,float dir_x, float dir_y) {
    this->velocity.x= this->speed * dir_x;
    this->velocity.y= this->speed * dir_y;
}
