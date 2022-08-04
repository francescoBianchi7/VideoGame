//
// Created by bianc on 31/07/2022.
//

#include "Rifle.h"

Rifle::Rifle() {
    //VISUAL WEAPON to be moved
    wpnRect.height=30;
    wpnRect.width=70;
    wpnRect.top=20;
    wpnRect.left=0;
    this->wpnTexture.loadFromFile("assets/Sprites/weapon/gunSheet.png",wpnRect);
    this->wpnSprite.setTexture(wpnTexture);
    wpnSprite.setOrigin(wpnSprite.getGlobalBounds().width,(wpnSprite.getGlobalBounds().top+wpnSprite.getGlobalBounds().height)/2.f);
    //muzzle.x=wpnSprite.getGlobalBounds().left;
    //muzzle.y=wpnSprite.getGlobalBounds().top/2.f;
    //shotcounter=0;
}
//GETTER&SETTER
void Rifle::setAimDirection(sf::Vector2f& mousePosView) {
    aimDir=mousePosView-wpnSprite.getPosition();
    //std::cout<<mousePosView.x<<"x"<<wpnSprite.getPosition().x<<"\n";
    //std::cout<<mousePosView.y<<"y"<<wpnSprite.getPosition().y<<"\n";
    aimDirNorm=aimDir/static_cast<float>(sqrt(pow(aimDir.x,2)+pow(aimDir.y,2)));
}
sf::Vector2f &Rifle::getAimDirectionNorm() {
    return aimDirNorm;
}

sf::Vector2f Rifle::getMuzzlePos() {
    muzzle.x=wpnSprite.getGlobalBounds().left;
    muzzle.y=wpnSprite.getGlobalBounds().top;
    return wpnSprite.getPosition()+sf::Vector2f(aimDirNorm.x*wpnSprite.getGlobalBounds().width,
                                                aimDirNorm.y*wpnSprite.getGlobalBounds().height);
}

//FUNCTIONS
void Rifle::shoot() {
    this->hasShot=false;
}

bool Rifle::canShoot() const {
    if(!this->hasShot)
        return true;
    else
        return false;
}

void Rifle::update(sf::Vector2f& mousePosView,const sf::Vector2f center) {
    wpnSprite.setPosition(center);

    float dX=mousePosView.x-wpnSprite.getPosition().x;
    float dY=mousePosView.y-wpnSprite.getPosition().y;
    float pi=3.14159265;
    float degrees=atan2(dY,dX)*180/pi;
    wpnSprite.setRotation(degrees+180.f);
    setAimDirection(mousePosView);
    //std::cout<<aimDirNorm.x<<", "<<aimDirNorm.y<<"\n";
    updateBurst();

}

void Rifle::render(sf::RenderTarget &target) {
    target.draw(wpnSprite);
}

void Rifle::updateBurst() {
    this->burstTime=this->timeSinceLastShot.getElapsedTime().asSeconds();
    if(burstTime > shotIntermission.asSeconds()){
        this->hasShot=false;
        this->timeSinceLastShot.restart();
    }
    else
        this->hasShot=true;
}

void Rifle::updateShotCounter() {
    this->shotcounter++;
}