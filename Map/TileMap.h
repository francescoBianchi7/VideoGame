#ifndef VIDEOGAME_TILEMAP_H
#define VIDEOGAME_TILEMAP_H

#include "..\Tiles\Tile.h"
#include "..\entities\Entity.h"
#include "PreCompHeaders.h"
class TileMap {
private:
    void clear();
    std::vector<std::vector<std::vector<Tile*>>> map;
    float tileSizeF;
    int tileSizeI;
    int layers;
    sf::Vector2u mapSizeGrid;//grid
    sf::Vector2f MapSizeF;//to get limits for collisions
    sf::Texture tileTextureSheet;
    std::string textureFile;
    sf::RectangleShape collisionBox;
    //culling
    int fromX=0,toX=0,fromY=0,toY=0,layer=0;
public:
    TileMap(float tileSize,unsigned width,unsigned height,std::string texture_file);
    virtual ~TileMap();
    //getter
    const sf::Texture* getTileSheet();
    //functions
    void update();
    void render(sf::RenderTarget & target, Entity* entity=nullptr);
    void addTile(unsigned x,unsigned y,unsigned z,sf::IntRect& textureRect,bool& collision,short& type);
    void removeTile(unsigned x,unsigned y,unsigned z);
    void updateCollision(Entity* entity,const float &dt);
    //save & load
    void saveToFile(const std::string& file_name);
    void loadFromFile(const std::string &file_name);
};


#endif //VIDEOGAME_TILEMAP_H
