//
// Created by bianc on 15/02/2022.
//

#ifndef VIDEOGAME_TILEMAP_H
#define VIDEOGAME_TILEMAP_H

#include "..\Tiles\Tile.h"
class TileMap {
private:
    std::vector<std::vector<std::vector<Tile>>> map;
    unsigned gridSizeU;
    unsigned layers;
    sf::Vector2u maxSize;
public:
    TileMap();
    virtual ~TileMap();
};


#endif //VIDEOGAME_TILEMAP_H
