//
// Created by bianc on 11/08/2022.
//

#ifndef VIDEOGAME_ENEMYSPAWNER_H
#define VIDEOGAME_ENEMYSPAWNER_H

#include "..\headers\PreCompHeaders.h"
#include "Tile.h"
class EnemySpawner: public Tile{
private:
    sf::RectangleShape shape;
    sf::Vector2f gridPosition;
    int Enemytype;
    int enemyAmount;
    int timeToSpawn;
    float maxDistance;//prob not needed


public:
    EnemySpawner(unsigned pos_grid_x,unsigned pos_grid_y,float tileSizeF,sf::Texture& texture,sf::IntRect& rect,float grid_size, int type, int amount,int time_to_spawn);
    virtual ~EnemySpawner();

    void spawn();
    void clear();//enemy spawner keeps track of enemies

    void update(const float &dt);
    void render(sf::RenderTarget& target);

};


#endif //VIDEOGAME_ENEMYSPAWNER_H
