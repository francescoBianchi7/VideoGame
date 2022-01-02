//
// Created by bianc on 27/12/2021.
//

#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite,float maxSpeed,float acceleration,float deceleration)
:sprite(sprite),maxSpeed(maxSpeed),acceleration(acceleration),deceleration(deceleration){}

MovementComponent::~MovementComponent() {}

void MovementComponent::update(const float &dt) {
    if (this->velocity.x > 0.f) //Check for positive x
        {
        //Max velocity check
        if (this->velocity.x > this->maxSpeed)
            this->velocity.x = this->maxSpeed;
        //Deceleration
        this->velocity.x -= deceleration;
        if (this->velocity.x < 0.f)
            this->velocity.x = 0.f;
        }
    else if(this->velocity.x < 0.f) //Check for negative x
        {
        //Max velocity check
        if (this->velocity.x < -this->maxSpeed)
            this->velocity.x = -this->maxSpeed;
        //Deceleration
        this->velocity.x += deceleration ;
        if (this->velocity.x > 0.f)
            this->velocity.x = 0.f;
        }
    if (this->velocity.y > 0.f) //Check for positive y
        {
        //Max velocity check
        if (this->velocity.y > this->maxSpeed)
            this->velocity.y = this->maxSpeed;
        //Deceleration
        this->velocity.y -= deceleration;
        if (this->velocity.y < 0.f)
            this->velocity.y = 0.f;
        }
    else if (this->velocity.y < 0.f) //Check for negative y
        {
        //Max velocity check
        if (this->velocity.y < -this->maxSpeed)
            this->velocity.y = -this->maxSpeed;
        //Deceleration
        this->velocity.y += deceleration;
        if (this->velocity.y > 0.f)
            this->velocity.y = 0.f;
        }
    //Final move
    this->sprite.move(this->velocity * dt); //Uses velocity
}

void MovementComponent::move(const float& dt,float dir_x, float dir_y) {
    this->velocity.x+=this->acceleration*dir_x;
    this->velocity.y+=this->acceleration*dir_y;
}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->velocity;
}
const float &MovementComponent::getSpeed() const {
    return this->maxSpeed;
}

bool MovementComponent::getState(short unsigned state) const {
    switch(state){
    case IDLE:
        if (this->velocity.x == 0.f && this->velocity.y == 0.f)
            return true;
        break;
        case MOVING:
            if (this->velocity.x != 0.f || this->velocity.y != 0.f)
                return true;
            break;
            case MOVING_LEFT:
                if (this->velocity.x < 0.f)
                    return true;
                break;
                case MOVING_RIGHT:
                    if (this->velocity.x > 0.f)
                        return true;
                    break;
                    case MOVING_UP:
                        if (this->velocity.y < 0.f)
                            return true;
                        break;
                        case MOVING_DOWN:
                            if (this->velocity.y > 0.f)
                                return true;
                            break;
                            default:
                                return false;
    }
    return false;
}

void MovementComponent::stopVelocity()
{
    /* Resets the velocity to 0.*/
    this->velocity.x = 0.f;
    this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX() {
    this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY() {
    this->velocity.y = 0.f;
}
