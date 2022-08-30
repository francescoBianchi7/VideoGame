#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(unsigned pos_grid_x,unsigned pos_grid_y,float tileSizeF,
                           sf::Texture& texture,sf::IntRect& rect,
                           int enemy_type, int amount,int time_to_spawn)
                           : Tile(tileTypes::ENEMYSPAWNER,pos_grid_x, pos_grid_y,tileSizeF, texture, rect, false) {

    tile.setFillColor(sf::Color(0,0,255,50));
    this->enemytype=enemy_type;
    enemySpawnTimer.restart();
    enemyAmount=amount;
    this->timeToSpawn = time_to_spawn;
    spawned = true;
}

EnemySpawner::~EnemySpawner() {

}
/// getter & setter
void EnemySpawner::setSpawned(const bool spawned) {
    this->spawned=spawned;
}
bool EnemySpawner::getSpawned() {
    return spawned;
}
bool EnemySpawner::getSpawnTimer() {
    if (enemySpawnTimer.getElapsedTime().asSeconds() >= timeToSpawn || firstSpawn){
        enemySpawnTimer.restart();
        firstSpawn = false;
        return true;
    }
    return false;
}
///FUNCTIONS
void EnemySpawner::spawn() {

}

void EnemySpawner::clear() {

}

std::string EnemySpawner::getAsString() const {
    std::stringstream ss;
    ss<<this->type<<" "<<tile.getTextureRect().left<<" "<<tile.getTextureRect().top<<" "<<
    enemytype<<" "<<enemyAmount<<" "<<timeToSpawn;
    return ss.str();
}

void EnemySpawner::update() {
}

void EnemySpawner::render(sf::RenderTarget &target) {
    target.draw(tile);
}

void EnemySpawner::increaseEnemyCounter()
{
    if (enemyCounter < enemyAmount)
        ++enemyCounter;
}

void EnemySpawner::decreaseEnemyCounter()
{
    if (enemyCounter > 0)
        --enemyCounter;
}

