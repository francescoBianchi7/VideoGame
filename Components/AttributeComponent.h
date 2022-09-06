#ifndef VIDEOGAME_ATTRIBUTECOMPONENT_H
#define VIDEOGAME_ATTRIBUTECOMPONENT_H

//made to avoid repeating code
//TBD when hp and GUI are implemented
#include "..\headers\PreCompHeaders.h"
class AttributeComponent {
public:
    //Leveling
    int level;
    int exp;
    int expNext;


    //Stats
    int hp;
    int hpMax;

    int bonusHp;
    int bonusDmg;
    int extraDmg;

    int speed;
    int baseSpeed;
    int bonusSpeed;

    //enemyStats
    int expGiven;

    //Con / Des
    AttributeComponent(int level,bool player);
    virtual ~AttributeComponent();

    //Functions
    void loseHP(int hp);
    void gainHP();
    void loseEXP(int exp);
    void gainExp(int exp);
    std::string debugPrint() const;
    bool isDead() const;

    void updatePlayerStats();
    void updateLevel();

    void update();
};


#endif //VIDEOGAME_ATTRIBUTECOMPONENT_H
