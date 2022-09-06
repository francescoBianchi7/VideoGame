#ifndef VIDEOGAME_GAMECHARACTER_H
#define VIDEOGAME_GAMECHARACTER_H


#include "Entity.h"
#include "../Weapon/Rifle.h"

class GameCharacter: public Entity {
private:
    //variables
    bool attacking;
    float speed;
    Rifle rifle;
    int hp;

    void initVariables();
    void initComponents();
    void initAnimations();//each entity it's going ot have his own
public:
    GameCharacter();
    GameCharacter(float x, float y, sf::Texture &textureSheet);
    ~GameCharacter() override;
    Rifle getWeapon();

    void loseHp(int dmg);
    void gainExp(int exp);
    void refillHP();
    void update(const float& dt,sf::Vector2f mouseposView) override;
    void render(sf::RenderTarget &target,const bool show_hitbox);
    void updateInput(const float & dt);
};


#endif //VIDEOGAME_GAMECHARACTER_H
