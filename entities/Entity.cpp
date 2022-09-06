//
//Base class for all entities
#include "Entity.h"

Entity::Entity(){
    initVariables();//to store important vars
}

Entity::~Entity() {
    delete this->movementComponent;
    delete this->animationComponent;
    delete this->hitboxComponent;
    delete this->attributeComponent;
}
//INITIALIZERS
void Entity::initVariables() {
    this->movementComponent=nullptr;
    this->animationComponent=nullptr;
    this->hitboxComponent=nullptr;
    this->attributeComponent= nullptr;
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
void Entity::createAttributeComponent(int K, bool player) {
    this->attributeComponent=new AttributeComponent(K, player);
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
MovementComponent* Entity::getMovementComponent() {
    return movementComponent;
}
HitboxComponent* Entity::getHitboxComponent() {
    return hitboxComponent;
}
AttributeComponent* Entity::getAttributeComponent() {
    return this->attributeComponent;
}
sf::Vector2f Entity::getCenter() const
{
    if (hitboxComponent)
        return hitboxComponent->getPosition() +sf::Vector2f(hitboxComponent->getGlobalBounds().width / 2.f,
                                            hitboxComponent->getGlobalBounds().height / 2.f);

    return sprite.getPosition() + sf::Vector2f(sprite.getGlobalBounds().width / 2.f,
                                sprite.getGlobalBounds().height / 2.f);
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

void Entity::update(const float& dt,sf::Vector2f mouseposView ) {
    if(movementComponent)
        movementComponent->update(dt);
}
void Entity::update(const float& dt) {
    if(movementComponent)
        movementComponent->update(dt);
}
void Entity::move(const float&dt,float dir_x, float dir_y) {
    if(movementComponent){
        movementComponent->move(dt,dir_x,dir_y);//sets velocity
    }
}
void Entity::moveLeft(const float &dt) {
    movementComponent->move(dt,-1.f,0.f);
}
void Entity::moveRight(const float &dt) {
    movementComponent->move(dt,1.f,0.f);
}
void Entity::moveUp(const float &dt) {
    movementComponent->move(dt,0.f,-1.f);
}
void Entity::moveDown(const float &dt) {
    movementComponent->move(dt,0.f,1.f);
}

void Entity::render(sf::RenderTarget& target,const bool showHitbox) {
    target.draw(sprite);
    if(hitboxComponent && showHitbox)
        hitboxComponent->render(target);
}

const sf::Vector2f &Entity::getVelocity() {
    return movementComponent->getVelocity();
}
const sf::Vector2f Entity::getSpriteCenter() const
{
    return sprite.getPosition() +
    sf::Vector2f
    (sprite.getGlobalBounds().width / 2.f,sprite.getGlobalBounds().height / 2.f);;
}
const float Entity::getSpriteDistance(const Entity& entity) const
{
    return sqrt(pow(this->getSpriteCenter().x - entity.getSpriteCenter().x, 2) + pow(this->getSpriteCenter().y - entity.getSpriteCenter().y, 2));
}




