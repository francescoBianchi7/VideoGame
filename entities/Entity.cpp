//
// Created by bianc on 05/12/2021.
//

#include "Entity.h"
//Base class for all entities
Entity::Entity() {
    this->shape.setSize(sf::Vector2f(50.f,50.f));
    this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition(100.f,100.f);
    this->moveSpeed=100.f;
}

Entity::~Entity() {

}

void Entity::move(const float&dt,const float dir_x, const float dir_y) {
    this->shape.move(dir_x*this->moveSpeed*dt,dir_y*this->moveSpeed*dt);
}

void Entity::render(sf::RenderTarget* target) {
    target->draw(this->shape);
}

void Entity::update(const float& dt) {


}

