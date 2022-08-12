
#include "../headers/PreCompHeaders.h"
#include "../Map/TileMap.h"
#include "../entities/GameCharacter.h"
#include "../googletest/include/gtest/gtest.h"
#include "../states/GameState.h"
#include "../headers//GameEngine.h"
#include "ctime"

class WorldBoundsFixture : public ::testing::Test {

protected:
    virtual void SetUp(){
        //gc.setPosition(0,0);
        tileMap->loadFromFile("Google_tests/gtest_assets/worldboundTestMap.txt");
        this->dt=this->dtClock.restart().asSeconds();
        mapSizeF.x=50.f*4;
        mapSizeF.y=50.f*4;

    }
    //GameCharacter gc;
    sf::Vector2f mapSizeF;
    //Entity gc;
    sf::Sprite sprite;
    sf::Texture texture;
    float dt;
    sf::Clock dtClock;
    TileMap* tileMap=new TileMap(50.f,4,4,"Google_tests/gtest_assets/GrassTestTile.png");
    GameCharacter *gc1=new GameCharacter(0,0,texture);
};

TEST_F(WorldBoundsFixture, WorldBoundsTest) {
   //Entity gc;
   //dt=this->dtClock.restart().asSeconds();
   gc1->setPosition(-1,-1);
   ASSERT_EQ(-1,gc1->getPositionX());
   ASSERT_EQ(-1,gc1->getPositionY());
    tileMap->update(gc1, dt);
   ASSERT_EQ(0,gc1->getPositionX());
   ASSERT_EQ(0,gc1->getPositionY());
   gc1->setPosition(mapSizeF.x+50,mapSizeF.y+50);
   //ASSERT_EQ(MapSizeF,gc1->getPositionX());
   //ASSERT_EQ(6,gc1->getPositionY());
    tileMap->update(gc1, dt);
   ASSERT_EQ(gc1->getPositionY(),mapSizeF.y - gc1->getGlobalBounds().height);
   ASSERT_EQ(mapSizeF.x - gc1->getGlobalBounds().width,gc1->getPositionX());
   /*gc1->move(dt,1,0);
   gc1->move(dt,0,1);
   ASSERT_EQ(1,gc1->getPositionX());
   ASSERT_EQ(1,gc1->getPositionY());*/
}