#ifndef VIDEOGAME_ENTITY_H
#define VIDEOGAME_ENTITY_H
#include "PreCompHeaders.h"
#include "../Components/MovementComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/HitboxComponent.h"
#include "../Components/AttributeComponent.h"

class Entity {
private:
    void initVariables();
protected:
    sf::Sprite sprite;

    MovementComponent* movementComponent;
    AnimationComponent* animationComponent;
    HitboxComponent* hitboxComponent;
    AttributeComponent* attributeComponent;
public:
    Entity();
    virtual ~Entity();
    //INITIALIZERS
    virtual void setTexture(sf::Texture& texture);
    void createHitboxComponent(float offset_x,float offset_y,float width,float height);
    void createMovementComponent(float speed);
    void createAnimationComponent(sf::Texture &textureSheet);
    void createAttributeComponent(int level,bool player);
    //Getter
    virtual const sf::Vector2f& getPosition() const;
    virtual sf::Vector2f getCenter() const;
    virtual sf::Vector2i getGridPosition(const int tileSizeI);
    virtual sf::FloatRect getGlobalBounds();
    virtual sf::FloatRect getNextPositionBounds(const float &dt) const;
    virtual const sf::Vector2f& getVelocity();
    virtual const float& getPositionX();
    virtual const float& getPositionY();
    virtual MovementComponent* getMovementComponent();
    virtual AttributeComponent* getAttributeComponent();
    virtual HitboxComponent* getHitboxComponent();
    //SETTER
    virtual void setPosition(float x,float y);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();
    //FUNCTIONS
    virtual void move(const float&dt,float x,float y);
    void moveRight(const float &dt);
    void moveLeft(const float &dt);
    void moveUp(const float &dt);
    void moveDown(const float &dt);
    virtual void update(const float& dt, sf::Vector2f mouseposView)=0;
    void update(const float& dt);
    virtual void render(sf::RenderTarget& target,const bool showHitbox=false)=0;

    virtual const float getSpriteDistance(const Entity& entity) const;
    virtual const sf::Vector2f getSpriteCenter() const;
};


#endif //VIDEOGAME_ENTITY_H
