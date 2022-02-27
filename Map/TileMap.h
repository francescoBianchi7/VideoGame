#ifndef VIDEOGAME_TILEMAP_H
#define VIDEOGAME_TILEMAP_H

#include "..\Tiles\Tile.h"
class TileMap {
private:
    void clear();
    std::vector<std::vector<std::vector<Tile*>>> map;
    float tileSizeF;
    unsigned tileSizeU;
    unsigned layers;
    sf::Vector2u mapSize;
    sf::Texture tileTextureSheet;
    std::string textureFile;
public:
    TileMap(unsigned tileSize,unsigned width,unsigned height,std::string texture_file);
    virtual ~TileMap();

    const sf::Texture* getTileSheet();

    void update();
    void render(sf::RenderTarget & target);

    void addTile(unsigned x,unsigned y,unsigned z,sf::IntRect& textureRect);
    void removeTile(unsigned x,unsigned y,unsigned z);
    void saveToFile(const std::string file_name);
    void loadFromFile(const std::string file_name);
};


#endif //VIDEOGAME_TILEMAP_H
