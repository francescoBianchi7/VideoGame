//
// Created by bianc on 26/12/2021.
//

#include "GameCharacter.h"
GameCharacter::GameCharacter() {
    speed=300.f;
    hp=10;
    this->createHitboxComponent(10.f,10.f,36.f,52.f);
    this->createMovementComponent(speed);
    this->setPosition(0,0);
}

GameCharacter::GameCharacter( float x, float y, sf::Texture &textureSheet){
    initVariables();
    this->createAttributeComponent(1,true);
    createMovementComponent(attributeComponent->speed);
    createAnimationComponent(textureSheet);
    initAnimations();

    sprite.setScale(1.5,1.5);
    createHitboxComponent(9.f,26.f,38,49);
    setPosition(x,y);
}

GameCharacter::~GameCharacter()= default;

//init function
void GameCharacter::initVariables() {

}
void GameCharacter::initAnimations() {
    this->animationComponent->addAnimation("IDLE_DOWN",10.f,0,0,0,0,36,48);
    this->animationComponent->addAnimation("WALK_DOWN",10.f,0,0,2,0,36,48);
    this->animationComponent->addAnimation("WALK_UP",10.f,0,3,2,3,36,48);
    this->animationComponent->addAnimation("WALK_LEFT",10.f,0,1,2,1,36,48);
    this->animationComponent->addAnimation("WALK_RIGHT",10.f,0,2,2,2,36,48);
}

Rifle GameCharacter::getWeapon() {
    return rifle;
}
void GameCharacter::initComponents(){}

void GameCharacter::update(const float &dt,sf::Vector2f mouseposView) {
   //updates which animation is playing and components
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
       attributeComponent->gainExp(20);
       movementComponent->updateSpeed(attributeComponent->speed);
       system("cls");
       std::cout<<attributeComponent->debugPrint()<<"\n";
       std::cout<<movementComponent->getSpeed()<<"\n";
   }
    movementComponent->update(dt);
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
    rifle.update(mouseposView,getCenter());
}
void GameCharacter::render(sf::RenderTarget &target, const bool show_hitbox) {
    target.draw(sprite);
    rifle.render(target);
    if(show_hitbox)
        hitboxComponent->render(target);
}

void GameCharacter::loseHp(int dmg) {
    hp=hp-dmg;
}
/*void GameCharacter::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed((sf::Keyboard::Key(keybinds.at("M))){
        movementComponent->move(dt,0.f,-1.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
        movementComponent->move(dt,0.f,1.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        movementComponent->move(dt,1.f,0.f);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        movementComponent->move(dt,-1.f,0.f);
    }
    if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
    &!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) &!sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        stopVelocity();
    }
}*/
