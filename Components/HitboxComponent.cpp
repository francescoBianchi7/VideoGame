//
// Created by bianc on 10/02/2022.
//
#include "PreCompHeaders.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(float offset_x, float offset_y, sf::Sprite &sprite, float width, float height)
:sprite(sprite),offsetX(offset_x),offsetY(offset_y) {
    this->hitbox.setPosition(sprite.getPosition().x+offset_x,sprite.getPosition().y+offset_y);
    this->hitbox.setSize(sf::Vector2f(width,height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(1.f);
    this->hitbox.setOutlineColor(sf::Color::Red);
}


HitboxComponent::~HitboxComponent() {

}

void HitboxComponent::update() {
    this->hitbox.setPosition(sprite.getPosition().x+offsetX,sprite.getPosition().y+offsetY);
}

void HitboxComponent::render(sf::RenderTarget &target) {
    target.draw(this->hitbox);

}

bool HitboxComponent::checkIntersect(const sf::FloatRect& rect) {
    return this->hitbox.getGlobalBounds().intersects(rect);
}

