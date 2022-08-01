//
// Created by bianc on 31/07/2022.
//

#include "Rifle.h"

Rifle::Rifle() {
    //VISUAL WEAPON to be moved
    wpnRect.height=30;
    wpnRect.width=70;
    wpnRect.top=20;
    this->wpnTexture.loadFromFile("assets/Sprites/weapon/gunSheet.png",wpnRect);
    this->wpnSprite.setTexture(wpnTexture);
    wpnSprite.setOrigin(wpnSprite.getGlobalBounds().width,(wpnSprite.getGlobalBounds().top+wpnSprite.getGlobalBounds().height)/2.f);
    muzzle.x=wpnSprite.getGlobalBounds().left;
    muzzle.y=wpnSprite.getGlobalBounds().top/2.f;
}
//GETTER&SETTER
const sf::Vector2f& Rifle::getMuzzlePosition() const {
    return muzzle;
}
//FUNCTIONS
void Rifle::shoot(sf::Vector2f &mousePosView, const float &dt) {
    std::cout<<"is shooting"<<" ";
}

void Rifle::update(sf::Vector2f& mousePosView,const sf::Vector2f center) {
    wpnSprite.setPosition(center);

    float dX=mousePosView.x-wpnSprite.getPosition().x;
    float dY=mousePosView.y-wpnSprite.getPosition().y;
    float pi=3.14159265;
    float degrees=atan2(dY,dX)*180/pi;
    wpnSprite.setRotation(degrees+180.f);
}

void Rifle::render(sf::RenderTarget &target) {
    target.draw(wpnSprite);
}


