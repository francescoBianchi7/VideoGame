//
// Created by bianc on 15/02/2022.
//
#include "PreCompHeaders.h"
#include "TileMap.h"

TileMap::TileMap() {
    this->gridSizeU=50;
    this->maxSize.x=5000;
    this->maxSize.y=5000;
    for(size_t x=0;x<this->maxSize.x;x++){
        this->map.emplace_back(std::vector<std::vector<Tile>>());
        for(size_t y=0;y<this->maxSize.y;y++){
            this->map[x].push_back(std::vector<Tile>());
            for(size_t z=0;z<this->layers;z++)
                this->map[x][y].push_back(Tile());
        }
    }
}

TileMap::~TileMap() {

}
