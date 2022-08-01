//
// Created by bianc on 31/07/2022.
//

#ifndef VIDEOGAME_RIFLE_H
#define VIDEOGAME_RIFLE_H


#include "Gun.h"
#include "Bullet.h"

class Rifle: public Gun {
public:
    //CON & DES
    Rifle();
    //GETTER & SETTER
    const sf::Vector2f& getMuzzlePosition() const;
    //FUNCTION
    void shoot(sf::Vector2f&mousePosView,const float& dt);
    void update(sf::Vector2f& mousePosView,sf::Vector2f center) override;
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_RIFLE_H
