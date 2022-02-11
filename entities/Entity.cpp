//
//Base class for all entities
//TBD: make it easier to inherit

#include "Entity.h"

Entity::Entity(){
    this->initVariables();//to store important vars

}

Entity::~Entity() {
    delete this->movementComponent;
    delete this->animationComponent;
    //delete this->hitboxComponent;
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


void Entity::initVariables() {
    this->movementComponent= nullptr;
    this->animationComponent=nullptr;
}

void Entity::setPosition(float x, float y) {
        this->sprite.setPosition(x,y);
}
void Entity::setTexture(sf::Texture &texture) {
    this->sprite.setTexture(texture);
}
void Entity::createAnimationComponent(sf::Texture &textureSheet) {
    this->animationComponent=new AnimationComponent(this->sprite,textureSheet);
}

void Entity::createMovementComponent(const float maxSpeed,float acceleration,float deceleration) {
    this->movementComponent=new MovementComponent(this->sprite,maxSpeed,acceleration,deceleration);
}

void Entity::update(const float& dt ) {
    if(this->movementComponent)
        this->movementComponent->update(dt);
}

void Entity::createHitboxComponent(float offset_x,float offset_y,sf::Sprite& sprite,float width,float height) {
    this->hitboxComponent=new HitboxComponent(offset_x,offset_y,sprite,width,
                                              height);
}

