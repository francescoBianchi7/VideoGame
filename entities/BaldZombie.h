
#ifndef VIDEOGAME_BALDZOMBIE_H
#define VIDEOGAME_BALDZOMBIE_H

#include "Enemy.h"

class BaldZombie: public Enemy {
    int hp;
    int maxHp;
    float speed;
    void initVariables();
    void initAnimations();
    void initGUI();

    sf::RectangleShape hpBar;
public:
    BaldZombie(float x, float y, sf::Texture &textureSheet,Entity& player);
    virtual ~BaldZombie();

    int getHp();
    //functions
    void loseHP(const int dmg) override;
    void update(const float &dt, sf::Vector2f mousePosView) override;
    void updateAnimation(const float &dt);
    void render(sf::RenderTarget &target, const bool show_hitbox) override;
};


#endif //VIDEOGAME_BALDZOMBIE_H
