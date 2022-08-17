#include "Tile.h"
Tile::Tile() {
 collision= false;
 type=0;
}
Tile::Tile(short type,unsigned pos_grid_x,unsigned pos_grid_y,float tileSizeF,sf::Texture& texture,sf::IntRect& rect,
           bool collision){
    tile.setSize(sf::Vector2f(tileSizeF,tileSizeF));
    //tile.setFillColor(sf::Color::Green);
    tile.setPosition(static_cast<float>(pos_grid_x)*tileSizeF,static_cast<float>(pos_grid_y)*tileSizeF);
    tile.setTexture(&texture);
    tile.setTextureRect(rect);

    this->collision=collision;
    this->type=type;
}

Tile::~Tile() {

}
//GETTER
const sf::Vector2f &Tile::getPosition()const {
    return this->tile.getPosition();
}
const bool &Tile::getCollision() const{
    return this->collision;
}
const short &Tile::getType() const {
    return this->type;
}
sf::FloatRect Tile::getGlobalBounds() const{
    return this->tile.getGlobalBounds();
}
//SETTER
void Tile::setCollision() {
    this->collision=true;
}
//FUNCTIONS
bool Tile::intersects(sf::FloatRect bounds) const {
    return this->tile.getGlobalBounds().intersects(bounds);
}
