#include "PreCompHeaders.h"
#include "Tile.h"
Tile::Tile() {
    collision=false;
    type=0;
}
Tile::Tile(unsigned x,unsigned y,float tileSizeF,sf::Texture& texture,sf::IntRect& rect,
            bool collision,short type){
    this->tile.setSize(sf::Vector2f(tileSizeF,tileSizeF));
    //tile.setFillColor(sf::Color::Green);
    tile.setPosition(x*tileSizeF,y*tileSizeF);
    //tile.setOutlineColor(sf::Color::White);
    //tile.setOutlineThickness(1.f);
    tile.setTexture(&texture);
    tile.setTextureRect(rect);
    collision=collision;
    type=type;
}

Tile::~Tile() {

}
const std::string Tile::getAsString() const {
    std::stringstream ss;
    ss<<tile.getTextureRect().left<<" "<<tile.getTextureRect().top<<" "<<collision<<" "<<type;
    return ss.str();
}
void Tile::update() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->tile);
}