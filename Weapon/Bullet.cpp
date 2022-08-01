//
// Created by bianc on 01/08/2022.
//

#include "Bullet.h"

#include <cmath>

Bullet::Bullet(float radius,float speed,sf::Vector2f startingPos) {
    this->speed=speed;
    range=100.f;
    bulletShape.setRadius(radius);
    bulletShape.setFillColor(sf::Color::Yellow);
    bulletShape.setPosition(startingPos);
}

Bullet::~Bullet() {

}
//SETTER
void Bullet::setDirection(sf::Vector2f &mousePosView) {
    direction=mousePosView/static_cast<float>(std::sqrt((mousePosView.x*mousePosView.x)+(mousePosView.y*mousePosView.y)));
}
void Bullet::setStartingPosition(sf::Vector2f position) {
    bulletShape.setPosition(position);
    this->startingPos=position;
}
//GETTER
float Bullet::getDistanceTravelled() const {
    return sqrt(pow(bulletShape.getPosition().x-startingPos.x,2)
        +pow(bulletShape.getPosition().y-startingPos.y,2));
}
//FUNCTIONS
void Bullet::update(const float &dt) {
    if(this->getDistanceTravelled()>range)
        delete this;
    else
        bulletShape.move(direction*speed);
}

void Bullet::render(sf::RenderTarget &target) {
    target.draw(bulletShape);
}

