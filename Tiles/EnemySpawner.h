#ifndef VIDEOGAME_ENEMYSPAWNER_H
#define VIDEOGAME_ENEMYSPAWNER_H

#include "..\headers\PreCompHeaders.h"
#include "Tile.h"
class EnemySpawner: public Tile{
private:
    sf::Vector2f gridPosition;
    bool spawned;
    bool firstSpawn=true;
    int enemytype;
    int enemyAmount;
    int enemyCounter;
    int timeToSpawn;
    float maxDistance;//prob not needed
    sf::Clock enemySpawnTimer;

public:
    EnemySpawner(unsigned pos_grid_x,unsigned pos_grid_y,float tileSizeF,sf::Texture& texture,sf::IntRect& rect, int enemy_type, int amount,int time_to_spawn);
    virtual ~EnemySpawner();
    ///getter & setter
    void setSpawned(const bool spawned);
    bool getSpawned();
    bool getSpawnTimer();
    ///other functions
    void spawn();
    void clear();//enemy spawner keeps track of enemies
    std::string getAsString() const;
    void increaseEnemyCounter();
    void decreaseEnemyCounter();

    virtual void update();
    void render(sf::RenderTarget& target);

};


#endif //VIDEOGAME_ENEMYSPAWNER_H
