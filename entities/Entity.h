//
// Created by bianc on 05/12/2021.
//

#ifndef VIDEOGAME_ENTITY_H
#define VIDEOGAME_ENTITY_H

#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/HitboxComponent.h"

class Entity {
private:
    void initVariables();
protected:
    sf::Sprite sprite;

    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
    HitboxComponent* hitboxComponent;

public:
    Entity();
    virtual ~Entity();
    //init
    virtual void setPosition(float x,float y);
    void setTexture(sf::Texture& texture);
    void createHitboxComponent(float offset_x,float offset_y,sf::Sprite& sprite,float width,float height);
    void createMovementComponent(float maxSpeed,float acceleration,float deceleration);
    void createAnimationComponent(sf::Texture &textureSheet);

    virtual void move(const float&dt,float x,float y);

    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);

};


#endif //VIDEOGAME_ENTITY_H
