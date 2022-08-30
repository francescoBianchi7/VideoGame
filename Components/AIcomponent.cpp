#include "AIcomponent.h"

AIcomponent::AIcomponent(Entity& self, Entity& entity): self(self), entity(entity){
}

AIcomponent::~AIcomponent()=default;

void AIcomponent::update(const float &dt) {
    sf::Vector2f moveVec;
    moveVec=calculateDistance();
    if (std::abs(moveVec.x)>=std::abs(moveVec.y)){
        if(moveVec.x<0)
            self.moveLeft(dt);
        else
            self.moveRight(dt);
    }else {//if (std::abs(moveVec.y)>std::abs(moveVec.x))
        if(moveVec.y<0)
            self.moveUp(dt);
        else
            self.moveDown(dt);
    }

    //float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));
    //moveVec /= vecLength;
    //if ((self.getPosition().x != entity.getPosition().x) && std::abs(vecLength) < 500.f)
       // self.move(moveVec.x, moveVec.y, dt);
}

sf::Vector2f AIcomponent::calculateDistance() {
    sf::Vector2f moveVec;
    moveVec.x = this->entity.getGlobalBounds().left - this->self.getGlobalBounds().left;
    moveVec.y = this->entity.getGlobalBounds().top - this->self.getGlobalBounds().top;
    return moveVec;
}

sf::Vector2f AIcomponent::moveRandomdirection() {
    int xDir_or_yDir;
    int posOrNeg;
    sf::Vector2f direction;
    xDir_or_yDir= rand() % 2;
    posOrNeg = rand() % 2;
    if (xDir_or_yDir==0){//x
        direction.y=0;
        if(posOrNeg==0){//pos
            direction.x=1.f;
            return direction;
        }
        else if(posOrNeg==1){//ng
            direction.x=-1.f;
            return direction;
        }
    }else if(xDir_or_yDir==1){//y
        direction.x=0;
        if(posOrNeg==0){//pos
            direction.y=1.f;
            return direction;
        }
        else if(posOrNeg==1){
            direction.y=-1.f;
            return direction;
        }
    }
}

