//
// Created by bianc on 15/02/2022.
//

#ifndef VIDEOGAME_TILE_H
#define VIDEOGAME_TILE_H

#include "GUI.h"

enum tileTypes{DEFAULT=0,SLOWING};

class Tile {
private:
protected:
    sf::RectangleShape tile;
    bool collision;
    short type;//tile Type
public:
    Tile();
    Tile(unsigned x,unsigned y,float tileSizeF,sf::Texture& texture,sf::IntRect& rect,bool collision=false,short type=tileTypes::DEFAULT);
    virtual ~Tile();

    //functions+
    const std::string getAsString() const;
    void update();
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_TILE_H
