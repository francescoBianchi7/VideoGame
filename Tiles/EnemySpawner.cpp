//
// Created by bianc on 11/08/2022.
//

#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(unsigned pos_grid_x,unsigned pos_grid_y,float tileSizeF,
                           sf::Texture& texture,sf::IntRect& rect,float grid_size, int type, int amount,int time_to_spawn)
                           : Tile(pos_grid_x, pos_grid_y,tileSizeF, texture, rect, false,tileTypes::ENEMYSPAWNER) {
    shape.setSize(sf::Vector2f(grid_size,grid_size));
    shape.setFillColor(sf::Color::White);

    this->Enemytype=type;
    this->enemyAmount=amount;
    this->timeToSpawn=time_to_spawn;

}

EnemySpawner::~EnemySpawner() {

}
//FUNCTIONS
void EnemySpawner::spawn() {

}

void EnemySpawner::clear() {

}

void EnemySpawner::update(const float &dt) {

}

void EnemySpawner::render(sf::RenderTarget &target) {
    target.draw(shape);
}
