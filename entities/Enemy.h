//
// Created by bianc on 08/08/2022.
//

#ifndef VIDEOGAME_ENEMY_H
#define VIDEOGAME_ENEMY_H
#include "Entity.h"
#include "../Tiles/EnemySpawner.h"

class Enemy: public Entity {
private:
    float speed;
    //EnemySpawner& enemySpawner;
    //initializers
    void initVariables();
    void initAnimations();
public:
    Enemy();
    virtual ~Enemy();

    //functions
    virtual void update(const float &dt, sf::Vector2f mousePosView)=0;
    virtual void render(sf::RenderTarget &target, const bool show_hitbox)=0;
};


#endif //VIDEOGAME_ENEMY_H
