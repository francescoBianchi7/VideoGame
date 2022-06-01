//
//Base class for all entities
#include "Entity.h"

Entity::Entity(){
    this->initVariables();//to store important vars
}

Entity::~Entity() {
    delete this->movementComponent;
    delete this->animationComponent;
    delete this->hitboxComponent;
}
//INITIALIZERS
void Entity::initVariables() {
    this->movementComponent=nullptr;
    this->animationComponent=nullptr;
    this->hitboxComponent=nullptr;
}

void Entity::createAnimationComponent(sf::Texture &textureSheet) {
    this->animationComponent=new AnimationComponent(this->sprite,textureSheet);
}
void Entity::createMovementComponent(const float speed) {
    this->movementComponent=new MovementComponent(this->sprite,speed);
}
void Entity::createHitboxComponent(float offset_x,float offset_y,float width,float height) {
    this->hitboxComponent=new HitboxComponent(offset_x,offset_y,sprite,width,
                                              height);
}
//GETTER
const sf::Vector2f &Entity::getPosition() const{
    if(this->hitboxComponent)
        return this->hitboxComponent->getPosition();
    return this->sprite.getPosition();
}
const float &Entity::getPositionX() {
    if(this->hitboxComponent)
        return this->hitboxComponent->getPosition().x;
    return this->sprite.getPosition().x;
}
const float &Entity::getPositionY() {
    if(this->hitboxComponent)
        return this->hitboxComponent->getPosition().y;
    return this->sprite.getPosition().y;
}

sf::Vector2i Entity::getGridPosition(const int tileSizeI) {
    /* returns position base on tile*/
    if(this->hitboxComponent)
        return {static_cast<int>(this->hitboxComponent->getPosition().x)/tileSizeI,
                            static_cast<int>(this->hitboxComponent->getPosition().y)/tileSizeI};
    return {static_cast<int>(this->sprite.getPosition().x)/tileSizeI,
                        static_cast<int>(this->sprite.getPosition().y)/tileSizeI};
}
sf::FloatRect Entity::getNextPositionBounds(const float &dt) const{
    if(hitboxComponent && movementComponent)
        return hitboxComponent->getNextPosition(this->movementComponent->getVelocity(),dt);
    return {1.f,1.f,1.f,1.f};
}
sf::FloatRect Entity::getGlobalBounds() {
    if(this->hitboxComponent)
        return hitboxComponent->getGlobalBounds();
    else
        return sprite.getGlobalBounds();
}
//SETTER
void Entity::setPosition(const float x,const float y) {
    if(this->hitboxComponent)
        this->hitboxComponent->setPosition(x,y);
    else
        this->sprite.setPosition(x,y);
}
void Entity::setTexture(sf::Texture &texture) {
    this->sprite.setTexture(texture);
}
void Entity::stopVelocityY() {
    if(this->movementComponent)
        this->movementComponent->stopVelocityY();
}
void Entity::stopVelocityX() {
    if(this->movementComponent)
        this->movementComponent->stopVelocityX();
}
void Entity::stopVelocity() {
    if(this->movementComponent)
        this->movementComponent->stopVelocity();
}
//FUNCTIONS

void Entity::update(const float& dt ) {
    if(this->movementComponent)
        this->movementComponent->update(dt);
}
void Entity::move(const float&dt,float dir_x, float dir_y) {
    if(this->movementComponent){
        this->movementComponent->move(dt,dir_x,dir_y);//sets velocity
    }
}
void Entity::render(sf::RenderTarget& target) {
    target.draw(sprite);
    if(this->hitboxComponent)
        this->hitboxComponent->render(target);
}

const sf::Vector2f &Entity::getVelocity() {
    return movementComponent->getVelocity();
}



