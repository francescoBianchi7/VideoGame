#ifndef VIDEOGAME_TILEMAP_H
#define VIDEOGAME_TILEMAP_H

#include "..\entities\BaldZombie.h"
#include "PreCompHeaders.h"
#include "..\Tiles\EnemySpawner.h"
#include "..\Tiles\DefaultTile.h"

class TileMap {
private:
    void clear();
    std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
    float tileSizeF;
    int tileSizeI;
    int layers;
    sf::Vector2i mapSizeGrid;//grid
    sf::Vector2f mapSizeF;//to get limits for World bound collisions
    sf::Texture tileTextureSheet;
    std::string textureFile;
    sf::RectangleShape collisionBox;
    sf::RectangleShape spawnerTileBox;
    //culling
    int fromX=0,toX=0,fromY=0,toY=0,layer=0;
public:
    TileMap(float tileSize,unsigned width,unsigned height,std::string texture_file);
    virtual ~TileMap();
    //getter
    const sf::Texture* getTileSheet();
    sf::Vector2i getMapSizeI() const;
    sf::Vector2f getMapSizeF() const;
    int getLayerSize(int x,int y, int layer) const;
    bool tileEmpty(int x,int y,int z);

    //functions
    void addTile(unsigned x,unsigned y,unsigned z,sf::IntRect& textureRect,bool& collision,short& type);
    void addTile(unsigned x,unsigned y,unsigned z,sf::IntRect& textureRect,int enemy_type,int enemy_amount,int enemy_tts);

    void removeTile(unsigned x,unsigned y,unsigned z);

    void render(sf::RenderTarget & target,sf::Vector2i gridPosition,bool showCollision=false);
    void updateTileCollision(Entity* entity, const float &dt);
    void updateWorldBoundsCollision(Entity* entity, const float &dt) const;
    void updateTiles(Entity* entity, const float &dt,std::vector<Enemy*>& activeEnemies,std::map<std::string, sf::Texture>& textures);
    void update(Entity* entity, const float &dt);
    //save & load
    void saveToFile(const std::string& file_name);
    void loadFromFile(const std::string &file_name);
};


#endif //VIDEOGAME_TILEMAP_H
