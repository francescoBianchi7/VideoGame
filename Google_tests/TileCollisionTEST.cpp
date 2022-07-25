#include "../headers/PreCompHeaders.h"
#include "../Map/TileMap.h"
#include "../entities/GameCharacter.h"
#include "../googletest/include/gtest/gtest.h"
#include "../states/GameState.h"
#include "../headers//GameEngine.h"
#include "ctime"

class TileCollisionFixture : public ::testing::Test {

protected:
    virtual void SetUp(){
        gc1->createMovementComponent(300.f);
        gc1->createHitboxComponent(20.f,20.f,35.f,85.f);
        gc.createHitboxComponent(20.f,20.f,35.f,85.f);
        movementComponent=gc.getMovementComponent();
        hitboxComponent=gc.getHitboxComponent();
        gc.setPosition(0,0);
        tileMap->loadFromFile("Google_tests/gtest_assets/tileCollisionTestMap.txt");
        this->dt=this->dtClock.restart().asSeconds();
        mapSizeF.x=50.f*4;
        mapSizeF.y=50.f*4;
        rect.left=1.f;
        rect.top=1.f;
        rect.width=1.f;
        rect.height=1.f;
    }
    sf::Vector2f mapSizeF;
    Entity gc;
    //GameEngine game;
    StateData stateData;
    sf::Sprite sprite;
    HitboxComponent* hitboxComponent;
    MovementComponent* movementComponent;
    sf::Texture texture;
    //MainMenuState *mainMenuState=new MainMenuState(stateData);
    float dt;
    sf::Window* window;
    sf::Clock dtClock;
    sf::FloatRect rect;
    TileMap* tileMap=new TileMap(50.f,6,6,"Google_tests/gtest_assets/GrassTestTile.png");
    GameCharacter *gc1=new GameCharacter(0,0,texture);
};

TEST_F(TileCollisionFixture,RightCollision){
     //tile without collision
     std::cout<<"TESTING RIGHT COLLISIONS"<<"\n";
     gc1->setPosition(0,50.f);
     gc1->moveRight(dt);
     ASSERT_TRUE(gc1->getMovementComponent()->getVelocityX()>0.f);
     gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                      gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
     float preUpdate;
     preUpdate=gc1->getPositionX();
     tileMap->updateCollision(gc1,dt);
    ASSERT_EQ(preUpdate,gc1->getPositionX());

     //bot side of character collides with collision tile
     gc1->setPosition(65.f,50.f);
     gc1->moveRight(dt);
     ASSERT_TRUE(gc1->getMovementComponent()->getVelocityX()>0.f);
     gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                      gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
     //std::cout<<"pre update"<<gc1->getPositionX()<<","<<gc1->getPositionY()<<"\n";
     tileMap->updateCollision(gc1,dt);
     std::cout<<"post update"<<gc1->getPositionY()<<","<<gc1->getPositionX()<<"\n";
     ASSERT_EQ(100-gc1->getGlobalBounds().width,gc1->getPositionX());

     //top side of character collides with collision tile
     gc1->setPosition(65.f,175.f);
     gc1->moveRight(dt);
     ASSERT_TRUE(gc1->getMovementComponent()->getVelocityX()>0.f);
     gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                      gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
     //std::cout<<"pre update"<<gc1->getPositionX()<<","<<gc1->getPositionY()<<"\n";
     tileMap->updateCollision(gc1,dt);
     std::cout<<"post update"<<gc1->getPositionY()<<","<<gc1->getPositionX()<<"\n";
     ASSERT_EQ(100-gc.getGlobalBounds().width,gc1->getPositionX());
}

TEST_F(TileCollisionFixture,LeftCollision){
    //tile without collision
    std::cout<<"TESTING LEFT COLLISIONS"<<"\n";
    gc1->setPosition(250.f,50.f);
    gc1->moveLeft(dt);
    ASSERT_TRUE(gc1->getMovementComponent()->getVelocityX()<0.f);
    gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                     gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
    float preUpdate;
    preUpdate=gc1->getPositionX();

    tileMap->updateCollision(gc1,dt);
    std::cout<<"pre"<<preUpdate<<" and post"<<gc1->getPositionX()<<"\n";
    ASSERT_EQ(preUpdate,gc1->getPositionX());

    //bot side of character collides with collision tile
    gc1->setPosition(200.f,50.f);
    gc1->moveLeft(dt);
    ASSERT_TRUE(gc1->getMovementComponent()->getVelocityX()<0.f);
    gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                     gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
    //std::cout<<"pre update"<<gc1->getPositionX()<<","<<gc1->getPositionY()<<"\n";
    tileMap->updateCollision(gc1,dt);
    std::cout<<"post update"<<gc1->getPositionY()<<","<<gc1->getPositionX()<<"\n";
    ASSERT_EQ(200.f,gc1->getPositionX());

    //top side of character collides with collision tile
    gc1->setPosition(200.f,175.f);
    gc1->moveLeft(dt);
    ASSERT_TRUE(gc1->getMovementComponent()->getVelocityX()<0.f);
    gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                     gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
    //std::cout<<"pre update"<<gc1->getPositionX()<<","<<gc1->getPositionY()<<"\n";
    tileMap->updateCollision(gc1,dt);
    std::cout<<"post update"<<gc1->getPositionY()<<","<<gc1->getPositionX()<<"\n";
    ASSERT_EQ(200.f,gc1->getPositionX());
}

TEST_F(TileCollisionFixture,DownCollision){
    std::cout<<"TESTING DOWNWARDS COLLISIONS"<<"\n";
    gc1->setPosition(0.f,50.f);
    gc1->moveDown(dt);
    ASSERT_TRUE(gc1->getMovementComponent()->getVelocityY()>0.f);
    gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                     gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
    float preUpdate;
    preUpdate=gc1->getPositionY();
    tileMap->updateCollision(gc1,dt);
    std::cout<<"pre"<<preUpdate<<" and post"<<gc1->getPositionY()<<"\n";
    ASSERT_EQ(preUpdate,gc1->getPositionY());

    //bot side of character collides with collision tile
    gc1->setPosition(125.f,15.f);
    gc1->moveDown(dt);
    ASSERT_TRUE(gc1->getMovementComponent()->getVelocityY()>0.f);
    gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                     gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
    tileMap->updateCollision(gc1,dt);
    std::cout<<"post update"<<gc1->getPositionY()<<","<<gc1->getPositionX()<<"\n";
    ASSERT_EQ(15.f,gc1->getPositionY());
}

TEST_F(TileCollisionFixture,UpCollision){
    std::cout<<"TESTING UPWARD COLLISIONS"<<"\n";
    gc1->setPosition(0.f,50.f);
    gc1->moveUp(dt);
    ASSERT_TRUE(gc1->getMovementComponent()->getVelocityY()<0.f);
    gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                     gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
    float preUpdate;
    preUpdate=gc1->getPositionY();
    tileMap->updateCollision(gc1,dt);
    std::cout<<"pre"<<preUpdate<<" and post"<<gc1->getPositionY()<<"\n";
    ASSERT_EQ(preUpdate,gc1->getPositionY());

    //bot side of character collides with collision tile
    gc1->setPosition(125.f,200.f);
    gc1->moveUp(dt);
    ASSERT_TRUE(gc1->getMovementComponent()->getVelocityY()<0.f);
    gc1->setPosition(gc1->getPositionX()+gc1->getMovementComponent()->getVelocityX()*dt,
                     gc1->getPositionY()+gc1->getMovementComponent()->getVelocityY()*dt);
    tileMap->updateCollision(gc1,dt);
    std::cout<<"post update"<<gc1->getPositionY()<<","<<gc1->getPositionX()<<"\n";
    ASSERT_EQ(200.f,gc1->getPositionY());
}