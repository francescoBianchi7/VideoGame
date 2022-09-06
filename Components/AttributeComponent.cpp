#include "AttributeComponent.h"

#include <cmath>
AttributeComponent::AttributeComponent(int level, bool player)
{
    this->level = level;
    if(player){
        this->hpMax=10;
        this->hp=hpMax;
        bonusHp=0;

        exp = 0;
        expNext = 50*level;
        this->expGiven=0;

        baseSpeed = 300.f;
        this->speed=baseSpeed;
        bonusSpeed=0;

        this->bonusDmg=0;
        extraDmg=0;

        updateLevel();
        updatePlayerStats();
    }else{
        exp=expNext=0;
        this->expGiven=5*level;

        baseSpeed=100.f;
        this->speed=baseSpeed+level*5;
        bonusSpeed=0;

        bonusHp = level*5;
        hpMax=15+bonusHp;
        hp=hpMax;


        this->bonusDmg=level;
        extraDmg=0;

        updateLevel();
        updatePlayerStats();
    }
}

AttributeComponent::~AttributeComponent()=default;

//Functions

void AttributeComponent::loseHP(const int dmg)
{
    this->hp=this->hp-dmg;
    if (hp < 0)
        hp = 0;
}

void AttributeComponent::gainHP()
{
    this->hp=hpMax;

}
std::string AttributeComponent::debugPrint() const
{
    std::stringstream ss;

    ss << "Level: " << this->level << "\n"
    << "HPMax: " << this->hpMax << "\n"
    << "HP: " << this->hp << "\n"
    << "dmg: " << this->bonusDmg << "\n"
    << "Exp: " << this->exp << "\n"
    << "Exp Next: " << this->expNext << "\n"
    << "speed: " << this->speed << "\n"
    << "baseSpeed: " << this->baseSpeed << "\n";

    return ss.str();
}
void AttributeComponent::loseEXP(const int exp)
{
    this->exp -= exp;
    if (this->exp < 0)
        this->exp = 0;
}

void AttributeComponent::gainExp(const int exp)
{
    this->exp += exp;
    this->updateLevel();
}

bool AttributeComponent::isDead() const
{
    return hp <= 0;
}

void AttributeComponent::updatePlayerStats()
{
    this->hpMax= hpMax+bonusHp+(level/2);
    bonusDmg=int(std::floor((level/2)))+bonusDmg+extraDmg;
    speed=baseSpeed+bonusSpeed+level*10;
}

void AttributeComponent::updateLevel()
{
    if (exp >= expNext)
    {
        ++level;
        exp=0;
        expNext = 50*level;
        updatePlayerStats();
        this->gainHP();
    }
}

void AttributeComponent::update()
{
    this->updateLevel();
}


