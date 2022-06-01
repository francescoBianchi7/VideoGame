//
// Created by bianc on 22/05/2022.

#include "../headers/PreCompHeaders.h"
#include "../Map/TileMap.h"
#include "../entities/GameCharacter.h"
#include "../googletest/include/gtest/gtest.h"
#include "../states/GameState.h"
#include "../headers//GameEngine.h"
class CollisionFixture : public ::testing::Test {

protected:
    virtual void SetUp(){
        frame.left=0;
        frame.height=109;
        frame.width=71;
        frame.top=0;
        //texture.loadFromFile("./assets/Sprites/GC/GC_Sheet2",frame);
        sprite.setTexture(texture);
        gc.setPosition(0,0);
        sprite.setPosition(gc.getPosition());
        gc.createMovementComponent(300);
        gc.createHitboxComponent(20.f,20.f,35.f,85.f);

    }
    //GameCharacter gc;
    Entity gc;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect frame;
};

TEST_F(CollisionFixture, GameCharacterPosition) {
   Entity gc;
   ASSERT_EQ(0,gc.getPositionX());
   ASSERT_EQ(0,gc.getPositionY());
}