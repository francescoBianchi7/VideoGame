#include "PreCompHeaders.h"
#include "Tile.h"
Tile::Tile() {
 collision= false;
 type=0;
}
Tile::Tile(unsigned x,unsigned y,float tileSizeF,sf::Texture& texture,sf::IntRect& rect,
            bool collision,short type){
    this->tile.setSize(sf::Vector2f(tileSizeF,tileSizeF));
    //tile.setFillColor(sf::Color::Green);
    tile.setPosition(static_cast<float>(x)*tileSizeF,static_cast<float>(y)*tileSizeF);
    //tile.setOutlineColor(sf::Color::White);
    //tile.setOutlineThickness(1.f);
    tile.setTexture(&texture);
    tile.setTextureRect(rect);
    this->collision=collision;
    this->type=type;
}

Tile::~Tile() {

}
const sf::Vector2f &Tile::getPosition()const {
    return this->tile.getPosition();
}
const bool &Tile::getCollision() const{
    return this->collision;
}
bool Tile::intersects(sf::FloatRect bounds) const {
    return this->tile.getGlobalBounds().intersects(bounds);
}
std::string Tile::getAsString() const {
    std::stringstream ss;
    ss<<tile.getTextureRect().left<<" "<<tile.getTextureRect().top<<" "<<this->collision<<" "<<this->type;
    return ss.str();
}
void Tile::update() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->tile);
}

sf::FloatRect Tile::getGlobalBounds() const{
    return this->tile.getGlobalBounds();
}
