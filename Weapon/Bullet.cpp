//
// Created by bianc on 01/08/2022.
//

#include "Bullet.h"

#include <cmath>

Bullet::Bullet(float radius,float speed) {
    this->speed=speed;
    range=1000.f;
    bulletShape.setRadius(radius);
    bulletShape.setFillColor(sf::Color::Yellow);
    //bulletShape.setPosition(startingPos);
    dmg=3;
}

Bullet::~Bullet() {

}
//SETTER
void Bullet::setDirection(sf::Vector2f &mousePosView) {
    direction=mousePosView/static_cast<float>(std::sqrt((mousePosView.x*mousePosView.x)+(mousePosView.y*mousePosView.y)));
}
void Bullet::setStartingPosition(float x,float y) {
    bulletShape.setPosition(x,y);
    this->startingPos=sf::Vector2f(x,y);
}
//GETTER
int Bullet::getDmg() const {
    return this->dmg;
}
sf::Vector2f Bullet::getPosition() {
    return bulletShape.getPosition();
}


float Bullet::getDistanceTravelled() const {
    return sqrt(pow(bulletShape.getPosition().x-startingPos.x,2)
        +pow(bulletShape.getPosition().y-startingPos.y,2));
}
//FUNCTIONS
void Bullet::update(const float &dt) {
    //if(this->getDistanceTravelled()>range)
        //delete this;
    //else
        bulletShape.move(direction*speed);
}

void Bullet::render(sf::RenderTarget &target) {
    target.draw(bulletShape);
}

float Bullet::getRange() {
    return range;
}

void Bullet::deleteBullet() {
}
