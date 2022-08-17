#ifndef VIDEOGAME_ENEMYSPAWNER_H
#define VIDEOGAME_ENEMYSPAWNER_H

#include "..\headers\PreCompHeaders.h"
#include "Tile.h"
class EnemySpawner: public Tile{
private:
    sf::Vector2f gridPosition;
    bool spawned;
    int enemytype;
    int enemyAmount;
    int timeToSpawn;
    float maxDistance;//prob not needed


public:
    EnemySpawner(unsigned pos_grid_x,unsigned pos_grid_y,float tileSizeF,sf::Texture& texture,sf::IntRect& rect, int enemy_type, int amount,int time_to_spawn);
    virtual ~EnemySpawner();
    ///getter & setter
    void setSpawned(const bool spawned);
    bool getSpawned();
    ///other functions
    void spawn();
    void clear();//enemy spawner keeps track of enemies
    std::string getAsString() const;

    virtual void update();
    void render(sf::RenderTarget& target);

};


#endif //VIDEOGAME_ENEMYSPAWNER_H
