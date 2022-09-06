#ifndef VIDEOGAME_ENEMY_H
#define VIDEOGAME_ENEMY_H
#include "Entity.h"
#include "../Tiles/EnemySpawner.h"
#include "../Components/AIcomponent.h"
#include "../Components/AttributeComponent.h"
class Enemy: public Entity {
private:
    float speed;
    int hp;
    //EnemySpawner& enemySpawner;
    //initializers
    AIcomponent *AI;
    void initVariables();
    void initAnimations();
public:
    Enemy();
    virtual ~Enemy();
    ///initializer
    void createAIcomponent(Entity& Self,Entity& player);
    ///getter
    virtual int getHp()=0;
    AIcomponent* getAi();
    ///functions
    bool isDead();
    virtual void loseHP(const int dmg)=0;
    virtual void update(const float &dt, sf::Vector2f mousePosView)=0;
    virtual void render(sf::RenderTarget &target, const bool show_hitbox)=0;
};


#endif //VIDEOGAME_ENEMY_H
