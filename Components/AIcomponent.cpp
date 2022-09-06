#include "AIcomponent.h"

AIcomponent::AIcomponent(Entity& self, Entity& entity): self(self), entity(entity){
    this->attackTimerMax=2.f;
}

AIcomponent::~AIcomponent()=default;

void AIcomponent::update(const float &dt) {
    sf::Vector2f moveVec;
    moveVec=calculateDistance();
    if(getDirectionTimer()){
        resetDirectionTimer();
        if (std::abs(moveVec.x)>std::abs(moveVec.y)){
            if(moveVec.x<0)
                self.moveLeft(dt);
            else
                self.moveRight(dt);
        }else if (std::abs(moveVec.x)<std::abs(moveVec.y)){
            if(moveVec.y<0)
                self.moveUp(dt);
            else
                self.moveDown(dt);
        }
    }
    //float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));
    //moveVec /= vecLength;
    //if ((self.getPosition().x != entity.getPosition().x) && std::abs(vecLength) < 500.f)
       // self.move(moveVec.x, moveVec.y, dt);
}
bool AIcomponent::getDirectionTimer() const {
    return keepCurrentDirectionTimer.getElapsedTime().asSeconds()>=0.5f;
}

bool AIcomponent::getDamageTimer() const
{
    return attackTimer.getElapsedTime().asSeconds() >= attackTimerMax;
}
void AIcomponent::resetDirectionTimer() {
    keepCurrentDirectionTimer.restart();
}

void AIcomponent::resetDamageTimer()
{
    attackTimer.restart();
}
sf::Vector2f AIcomponent::calculateDistance() {
    sf::Vector2f moveVec;
    moveVec.x = entity.getGlobalBounds().left - self.getGlobalBounds().left;
    moveVec.y = entity.getGlobalBounds().top - self.getGlobalBounds().top;
    return moveVec;
}
//NOT USED
void AIcomponent::moveRandomdirection(const float &dt) {
    int xDir_or_yDir;
    int posOrNeg;
    sf::Vector2f direction;
    xDir_or_yDir= rand() % 2;
    posOrNeg = rand() % 2;
    if (xDir_or_yDir==0){//x
        if(posOrNeg==0)//pos
            self.moveRight(dt);
        else if(posOrNeg==1){//ng
            self.moveLeft(dt);
        }
    }else if(xDir_or_yDir==1){//y
        if(posOrNeg==0)//pos
            self.moveDown(dt);
        else if(posOrNeg==1)
            self.moveUp(dt);
    }
}

bool AIcomponent::doDamage(const float &dt) {
    if(getDamageTimer()){
        resetDamageTimer();
        return true;
    }
    return false;
}
