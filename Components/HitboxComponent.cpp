#include "PreCompHeaders.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(float offset_x, float offset_y, sf::Sprite &sprite, float width, float height)
:sprite(sprite),offsetX(offset_x),offsetY(offset_y) {

    this->nextPosition.left=0.f;
    this->nextPosition.top=0.f;
    this->nextPosition.width=width;
    this->nextPosition.height=height;
    this->hitbox.setPosition(sprite.getPosition().x+offset_x,sprite.getPosition().y+offset_y);
    this->hitbox.setSize(sf::Vector2f(width,height));
    this->hitbox.setFillColor(sf::Color::Transparent);
    this->hitbox.setOutlineThickness(-1.f);
    this->hitbox.setOutlineColor(sf::Color::Red);
}

HitboxComponent::~HitboxComponent() {

}
//GETTER
const sf::FloatRect &HitboxComponent::getNextPosition(const sf::Vector2f &velocity) {
    this->nextPosition.left=this->hitbox.getPosition().x+velocity.x;
    this->nextPosition.top=this->hitbox.getPosition().y+velocity.y;
    return this->nextPosition;
}

const sf::Vector2f &HitboxComponent::getPosition() {
    return this->hitbox.getPosition();
}
sf::FloatRect HitboxComponent::getGlobalBounds() const {
    return this->hitbox.getGlobalBounds();
}
//SETTER
void HitboxComponent::setPosition(const sf::Vector2f& position) {
    this->hitbox.setPosition(position);
    this->sprite.setPosition(position.x-offsetX,position.y-offsetY);
}
void HitboxComponent::setPosition(float x, float y) {
    this->hitbox.setPosition(x,y);
    this->sprite.setPosition(x-offsetX,y-offsetY);
}
//FUNCTIONS
//keeps hitbox on player sprite
void HitboxComponent::update() {
    this->hitbox.setPosition(sprite.getPosition().x+offsetX,sprite.getPosition().y+offsetY);
}
//renders hitbox rect
void HitboxComponent::render(sf::RenderTarget &target) {
    target.draw(this->hitbox);
}
//checks if 2 hitbox intersect
bool HitboxComponent::checkIntersect(const sf::FloatRect& rect) {
    return this->hitbox.getGlobalBounds().intersects(rect);
}

