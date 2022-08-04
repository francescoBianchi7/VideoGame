//
// Created by bianc on 31/07/2022.
//

#ifndef VIDEOGAME_GUN_H
#define VIDEOGAME_GUN_H
#include "Item.h"

class Gun: public Item{
protected:
    sf::Texture wpnTexture;
    sf::IntRect wpnRect;
    sf::Sprite wpnSprite;
    sf::Vector2f muzzle;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;
    int damageMin;
    int damageMax;
public:
    Gun();
    virtual ~Gun();
    virtual void shoot()=0;
    virtual void update(sf::Vector2f& mousePosView, sf::Vector2f center)=0;
    virtual void render(sf::RenderTarget& target)=0;

};


#endif //VIDEOGAME_GUN_H
