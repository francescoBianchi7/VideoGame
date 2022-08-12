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
    EnemySpawner& enemySpawner;
    //initializers
    void initVariables();
    void initAnimations();
public:
    Enemy(EnemySpawner& enemySpawner, float x, float y, sf::Texture &textureSheet);
    virtual ~Enemy();

    //functions
    void update(const float &dt, sf::Vector2f mousePosView);
    void render(sf::RenderTarget &target, const bool show_hitbox);
};


#endif //VIDEOGAME_ENEMY_H
