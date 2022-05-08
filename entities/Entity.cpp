//
//Base class for all entities
//TBD: make it easier to inherit
#include "PreCompHeaders.h"
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
}

void Entity::createAnimationComponent(sf::Texture &textureSheet) {
    this->animationComponent=new AnimationComponent(this->sprite,textureSheet);
}
void Entity::createMovementComponent(const float speed) {
    this->movementComponent=new MovementComponent(this->sprite,speed);
}
void Entity::createHitboxComponent(float offset_x,float offset_y,sf::Sprite& sprite,float width,float height) {
    this->hitboxComponent=new HitboxComponent(offset_x,offset_y,sprite,width,
                                              height);
}
//GETTER
const sf::Vector2f &Entity::getPosition() const{
    if(this->hitboxComponent)
        return this->hitboxComponent->getPosition();

    return this->sprite.getPosition();
}
sf::Vector2u Entity::getGridPosition(const unsigned tileSizeU) {
    /* returns position base on tile*/
    if(this->hitboxComponent)
        return sf::Vector2u(static_cast<unsigned>(this->hitboxComponent->getPosition().x)/tileSizeU,
                            static_cast<unsigned>(this->hitboxComponent->getPosition().y)/tileSizeU);
    return sf::Vector2u(static_cast<unsigned>(this->sprite.getPosition().x)/tileSizeU,
                        static_cast<unsigned>(this->sprite.getPosition().y)/tileSizeU);;
}
const sf::FloatRect &Entity::getNextPositionBounds(const float &dt){
    if(hitboxComponent && movementComponent)
        return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity()*dt);
    return sf::FloatRect();
}
sf::FloatRect Entity::getGlobalBounds() {
    if(this->hitboxComponent)
        return this->hitboxComponent->getGlobalBounds();
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

