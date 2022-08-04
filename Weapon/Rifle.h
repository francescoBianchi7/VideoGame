//
// Created by bianc on 31/07/2022.
//

#ifndef VIDEOGAME_RIFLE_H
#define VIDEOGAME_RIFLE_H


#include "Gun.h"
#include "Bullet.h"

class Rifle: public Gun {
private:
    sf::Clock timeSinceLastShot;
    float burstTime;
    int shotcounter;
    bool burst;
    bool hasShot;
    sf::Time shotIntermission=sf::seconds(0.3f);
public:
    //CON & DES
    Rifle();
    //GETTER & SETTER
    void setAimDirection(sf::Vector2f& mousePosView);
    sf::Vector2f getMuzzlePos();
    sf::Vector2f& getAimDirectionNorm();
    //FUNCTION
    bool canShoot() const;
    void shoot();
    void update(sf::Vector2f& mousePosView,sf::Vector2f center) override;
    void updateBurst();
    void updateShotCounter();
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_RIFLE_H
