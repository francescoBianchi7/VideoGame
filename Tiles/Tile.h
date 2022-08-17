#ifndef VIDEOGAME_TILE_H
#define VIDEOGAME_TILE_H

#include "GUI.h"
#include "PreCompHeaders.h"
enum tileTypes{DEFAULT=0,SLOWING, ENEMYSPAWNER};

class Tile {
private:
protected:
    sf::RectangleShape tile;
    bool collision;
    short type;//tile Type

public:
    Tile();
    Tile(short type,unsigned pos_grid_x,unsigned pos_grid_y,float tileSizeF,sf::Texture& texture,sf::IntRect& rect,bool collision);
    virtual ~Tile();

    //getter
    const sf::Vector2f& getPosition() const;
    const bool &getCollision() const;
    const short& getType() const;
    sf::FloatRect getGlobalBounds()const;
    //setter
    void setCollision();
    //functions+
    bool intersects(sf::FloatRect bounds)const;

    virtual std::string getAsString() const=0;
    virtual void update()=0;
    virtual void render(sf::RenderTarget& target)=0;
};


#endif //VIDEOGAME_TILE_H
