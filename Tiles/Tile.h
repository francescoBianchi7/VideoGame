//
// Created by bianc on 15/02/2022.
//

#ifndef VIDEOGAME_TILE_H
#define VIDEOGAME_TILE_H

#include "GUI.h"
#include "PreCompHeaders.h"
enum tileTypes{DEFAULT=0,SLOWING,ENEMYSPAWNER};

class Tile {
private:
protected:
    sf::RectangleShape tile;
    bool collision;
    short type;//tile Type
public:
    Tile();
    Tile(unsigned pos_grid_x,unsigned pos_grid_y,float tileSizeF,sf::Texture& texture,sf::IntRect& rect,bool collision=false,short type=tileTypes::DEFAULT);
    virtual ~Tile();

    //getter
    const sf::Vector2f& getPosition() const;
    const bool &getCollision() const;
    sf::FloatRect getGlobalBounds()const;
    bool intersects(sf::FloatRect bounds)const;
    std::string getAsString() const;
    void setCollision();
    //functions+
    virtual void update();
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_TILE_H
