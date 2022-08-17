#ifndef VIDEOGAME_DEFAULTTILE_H
#define VIDEOGAME_DEFAULTTILE_H
#include "Tile.h"

class DefaultTile: public Tile {
    private:
    protected:
    public:
        DefaultTile(short type, unsigned pos_grid_x,unsigned pos_grid_y,float tileSizeF,sf::Texture& texture,
                    sf::IntRect& rect,bool collision=false);
        virtual ~DefaultTile();
        //getter
        virtual std::string getAsString() const;
        //functions+
        virtual void update();
        void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_DEFAULTTILE_H
