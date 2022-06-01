//
// Created by bianc on 05/12/2021.
//

#ifndef VIDEOGAME_ENTITY_H
#define VIDEOGAME_ENTITY_H
#include "PreCompHeaders.h"
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
    //INITIALIZERS
    virtual void setTexture(sf::Texture& texture);
    void createHitboxComponent(float offset_x,float offset_y,float width,float height);
    void createMovementComponent(float speed);
    void createAnimationComponent(sf::Texture &textureSheet);
    //Getter
    virtual const sf::Vector2f& getPosition() const;
    virtual sf::Vector2i getGridPosition(const int tileSizeI);
    virtual sf::FloatRect getGlobalBounds();
    virtual sf::FloatRect getNextPositionBounds(const float &dt) const;
    virtual const sf::Vector2f& getVelocity();
    virtual const float& getPositionX();
    virtual const float& getPositionY();
    //SETTER
    virtual void setPosition(float x,float y);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();
    //FUNCTIONS
    virtual void move(const float&dt,float x,float y);
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget& target);

};


#endif //VIDEOGAME_ENTITY_H
