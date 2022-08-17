
#ifndef VIDEOGAME_BALDZOMBIE_H
#define VIDEOGAME_BALDZOMBIE_H

#include "Enemy.h"

class BaldZombie:public Enemy {
    float speed;
    void initVariables();
    void initAnimations();
public:
    BaldZombie(float x, float y, sf::Texture &textureSheet);
    virtual ~BaldZombie();

    //functions
    void update(const float &dt, sf::Vector2f mousePosView) override;
    void render(sf::RenderTarget &target, const bool show_hitbox) override;
};


#endif //VIDEOGAME_BALDZOMBIE_H
