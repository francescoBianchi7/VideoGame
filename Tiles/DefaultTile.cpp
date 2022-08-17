//
// Created by bianc on 16/08/2022.
//

#include "DefaultTile.h"

DefaultTile::DefaultTile(short type,unsigned posGridX, unsigned posGridY, float tileSizeF, sf::Texture &texture,
                         sf::IntRect &rect, bool collision):
                         Tile(type,posGridX, posGridY, tileSizeF, texture,
                                                                               rect, collision){
    tile.setSize(sf::Vector2f(tileSizeF,tileSizeF));
    tile.setFillColor(sf::Color::White);

}

DefaultTile::~DefaultTile() {

}

std::string DefaultTile::getAsString() const {
    std::stringstream ss;
    ss<<type << " " <<tile.getTextureRect().left<<" "<<tile.getTextureRect().top<<" "<<collision;
    return ss.str();
}
void DefaultTile::update() {

}
void DefaultTile::render(sf::RenderTarget &target) {
    target.draw(tile);
}
