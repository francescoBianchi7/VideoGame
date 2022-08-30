#include "AttributeComponent.h"

#include <cmath>
AttributeComponent::AttributeComponent(int level, bool player)
{
    this->level = level;
    if(player){
        this->hpMax=10;
        hp=hpMax;
        bonusHp=0;
        exp = 0;
        expNext = 50*level;
        attributePoints = 2;
        baseSpeed = 300.f;
        extraDmg=0;
        speed=baseSpeed;
        this->bonusDmg=0;
        updateLevel();
        updateStats();
    }else{
        expGiven=5*level;
        speed=100*level;
        bonusHp = level*5;
        hpMax=20+bonusHp;
    }
}

AttributeComponent::~AttributeComponent()=default;

//Functions

void AttributeComponent::loseHP(const int dmg)
{
    hp -= dmg;
    if (hp < 0)
        hp = 0;
}

void AttributeComponent::gainHP(const int hp)
{
    this->hp += hp;

    if (this->hp > this->hpMax)
        this->hp = this->hpMax;
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

const bool AttributeComponent::isDead() const
{
    return hp <= 0;
}

void AttributeComponent::updateStats()
{
    this->hpMax= hpMax+bonusHp+(level/2);
    bonusDmg=int(std::floor(float(level/2)))+bonusDmg+extraDmg;
    speed=baseSpeed+bonusSpeed+level*10;
    hp = hpMax;

}

void AttributeComponent::updateLevel()
{
    if (exp >= expNext)
    {
        ++level;
        exp=0;
        expNext = 50*level;
        updateStats();
    }
}

void AttributeComponent::update()
{
    this->updateLevel();
}


