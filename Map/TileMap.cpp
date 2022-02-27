//
// Created by bianc on 15/02/2022.
//
#include "PreCompHeaders.h"
#include "TileMap.h"
void TileMap::clear() {
    for(size_t x=0;x<this->mapSize.x;x++){
        for(size_t y=0;y<this->mapSize.y;y++){
            for(size_t z=0;z<this->layers;z++){
                delete map[x][y][z];
                map[x][y][z]= nullptr;
            }
            map[x][y].clear();
        }
        map[x].clear();
    }
    map.clear();
}

TileMap::TileMap(unsigned tileSize,unsigned width,unsigned height,std::string texture_file) {
    tileSizeF=tileSize;
    tileSizeU=static_cast<unsigned>(tileSizeF);
    mapSize.x=width;
    mapSize.y=height;
    layers=1;
    map.resize(mapSize.x,std::vector<std::vector<Tile*>>());
    textureFile=texture_file;
    //prob gonna be changed later really inefficient
    for(size_t x=0;x<this->mapSize.x;x++){
        for(size_t y=0;y<this->mapSize.y;y++){
            map[x].resize(mapSize.y,std::vector<Tile*>());
            for(size_t z=0;z<this->layers;z++){
                map[x][y].resize(layers, nullptr);
            }
        }
    }
    if(!tileTextureSheet.loadFromFile(texture_file))
        std::cout<<"ERROR::TILEMAP::FAILED TO LOAD TILETEXTURESHEET"<<texture_file<<"\n";
}

TileMap::~TileMap() {
    for(size_t x=0;x<this->mapSize.x;x++){
        for(size_t y=0;y<this->mapSize.y;y++){
            for(size_t z=0;z<this->layers;z++){
                delete map[x][y][z];
            }
        }
    }
}
//getter
const sf::Texture *TileMap::getTileSheet() {
    return &this->tileTextureSheet;
}

void TileMap::update() {}

void TileMap::render(sf::RenderTarget & target) {
    for(auto &x: this->map ){
        for(auto &y:x){
            for(auto *z:y){
                if(z)//if this is not null i render, helps with memory
                    z->render(target);
            }
        }
    }
}
void TileMap::addTile(unsigned x,unsigned y,unsigned z,sf::IntRect& textureRect) {
    //adds a tile where the mouse is,if the mouse is inside the array
    if(x<mapSize.x && x>=0 && y<mapSize.y && y>=0 && z<layers && z>=0){
        if(map[x][y][z]== nullptr){
            map[x][y][z]=new Tile(x,y,tileSizeF,tileTextureSheet,textureRect);
            std::cout<<"DEBUG::ADDED TILE";
        }
    }
}
void TileMap::removeTile(unsigned x,unsigned y,unsigned z) {
//remove if a tile if present
    if(x<mapSize.x && x>=0 && y<mapSize.y && y>=0 && z<layers && z>=0){
        if(map[x][y][z]!= nullptr){//can remove
            delete map[x][y][z];
            map[x][y][z]= nullptr;
            std::cout<<"DEBUG::REMOVED TILE";
        }
    }
}

void TileMap::saveToFile(const std::string file_name) {
//saves the tile maps to a text file
// Format: Size x,y tileSize
//pos x,y textureRect type
    std::ofstream out_file;
    out_file.open(file_name);
    if(out_file.is_open()){
        out_file<<mapSize.x<<" "<<mapSize.y<<"\n"
        <<tileSizeU<<"\n"
        <<layers<<"\n"
        <<textureFile<<"\n";
        for(size_t x=0;x<this->mapSize.x;x++){
            for(size_t y=0;y<this->mapSize.y;y++){
                for(size_t z=0;z<this->layers;z++){
                    if(this->map[x][y][z])
                        out_file<<x<<" "<<y<<" "<<z<<" "<<this->map[x][y][z]->getAsString()<<" ";//MAKE sure last space isn't saved
                }
            }
            std::cout<<"saved";
        }
    }else{
        std::cout<<"ERROR::COULD NOT SAVE FILE,"<<file_name;
    }
    out_file.close();
}

void TileMap::loadFromFile(const std::string file_name) {
    std::ifstream in_file;
    in_file.open(file_name);
    if(in_file.is_open()){
        sf::Vector2u size;
        unsigned tileSize=0;
        unsigned layers=0;
        std::string texture_file="";
        unsigned x=0;
        unsigned y=0;
        unsigned z=0;
        unsigned trX=0;
        unsigned trY=0;
        bool collision=false;
        short type=0;
        //basics
        in_file>> size.x >> size.y >> tileSize >> layers >> texture_file;
        //tiles
        tileSizeF=static_cast<float> (tileSize);
        tileSizeU=tileSize;
        mapSize.x=size.x;
        mapSize.y=size.y;
        layers=layers;
        textureFile=texture_file;
        this->clear();
        map.resize(mapSize.x,std::vector<std::vector<Tile*>>());
        for(size_t x=0;x<this->mapSize.x;x++){
            for(size_t y=0;y<this->mapSize.y;y++){
                map[x].resize(mapSize.y,std::vector<Tile*>());
                for(size_t z=0;z<this->layers;z++){
                    map[x][y].resize(layers, nullptr);
                }
            }
        }
        if(!tileTextureSheet.loadFromFile(texture_file))
            std::cout<<"Error";
        while(in_file>> x>> y>> z>> trX>> trY>>collision>>type){
            sf::IntRect textureRect=sf::IntRect(static_cast<int>(trX),static_cast<int>(trY),
                                                static_cast<int>(tileSizeU),static_cast<int>(tileSizeU));
            this->map[x][y][z]=new Tile(x,y,this->tileSizeF,tileTextureSheet,
                                        textureRect,collision,type);
            }
    }else{
        std::cout<<"ERROR::COULD NOT LOAD FROM FILE,"<<file_name;
    }
    in_file.close();
}