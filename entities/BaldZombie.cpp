//
// Created by bianc on 15/08/2022.
//

#include "BaldZombie.h"
void BaldZombie::initVariables() {
    speed=100.f;
    maxHp=20;
    hp=maxHp;
}

void BaldZombie::initAnimations() {
    this->animationComponent->addAnimation("IDLE_DOWN",10.f,0,0,0,0,32,45);
    this->animationComponent->addAnimation("WALK_DOWN",10.f,0,0,2,0,50,48);
    this->animationComponent->addAnimation("WALK_UP",10.f,0,3,2,3,50,48);
    this->animationComponent->addAnimation("WALK_LEFT",10.f,0,1,2,1,50,48);
    this->animationComponent->addAnimation("WALK_RIGHT",10.f,0,2,2,2,50,48);
}
void BaldZombie::initGUI() {
    hpBar.setFillColor(sf::Color::Red);
    hpBar.setSize(sf::Vector2f(30.f, 3.f));
    hpBar.setPosition(this->sprite.getPosition());
    hpBar.setOutlineColor(sf::Color::Black);
    hpBar.setOutlineThickness(-1.f);
}
BaldZombie::BaldZombie(float x, float y, sf::Texture &textureSheet,Entity& player): Enemy() {
    initVariables();
    createMovementComponent(speed);
    createAnimationComponent(textureSheet);
    initAnimations();
    createAttributeComponent(1,false);
    initGUI();
    createHitboxComponent(6.f,6.f,32.f,42.f);
    setPosition(x,y);
    createAIcomponent(*this,player);

}

BaldZombie::~BaldZombie() {

}
int BaldZombie::getHp() {
    return hp;
}

void BaldZombie::update(const float &dt,sf::Vector2f mousePosView) {
    //updates which animation is playing and components
    //movementComponent->update(dt);
    this->hpBar.setSize(sf::Vector2f(30.f * (static_cast<float>(hp) / static_cast<float>(maxHp)), 3.f));
    this->hpBar.setPosition(this->sprite.getPosition());
    getAi()->update(dt);
    if(!movementComponent->isMoving())
        animationComponent->play("IDLE_DOWN",dt);
    else if(movementComponent->getVelocityX()>0.f)
        animationComponent->play("WALK_RIGHT",dt);
    else if(movementComponent->getVelocityX()<0.f)
        animationComponent->play("WALK_LEFT",dt);
    else if(movementComponent->getVelocityY()<0.f)
        animationComponent->play("WALK_UP",dt);
    else if(movementComponent->getVelocityY()>0.f)
        animationComponent->play("WALK_DOWN",dt);
    hitboxComponent->update();
}

void BaldZombie::render(sf::RenderTarget &target, const bool show_hitbox) {
    target.draw(sprite);
    if(show_hitbox)
        hitboxComponent->render(target);
    target.draw(hpBar);
}

void BaldZombie::loseHP(const int dmg) {
    this->hp=hp-dmg;
}

void BaldZombie::updateAnimation(const float &dt) {

}