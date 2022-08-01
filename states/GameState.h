#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include "State.h"
#include "..\GUI\PauseMenu.h"
#include "..\Map\TileMap.h"
#include "..\Weapon\Gun.h"

class GameCharacter;
class PauseMenu;
class TileMap;
class View;
class Font;
class RenderTexture;

class GameState:
        public State{
private:
    sf::View view;
    sf::Vector2i viewGridPos;
    sf::RenderTexture renderTexture; //renders all tiles in a canvas
    sf::Sprite renderSprite; // paste the canvas on window

    PauseMenu *pmenu;
    sf::Font font;

    GameCharacter* player;//memory is dinamically allocated
    sf::Texture texture;

    TileMap* tileMap;
    //Initialization Functions
    void initDelayedRender();//to render faster
    void initView();
    void initKeybinds() override;
    void initTextures();
    void initFonts();
    void initPlayer();
    void initPauseMenu();
    void initTileMap();

public:
    explicit GameState(StateData &stateData);
    virtual ~GameState();

    void endState() override;//just to see which state is ending
    void updatePlayerInput(const float& dt);//choose player actions based on input received
    void updatePlayer(const float& dt);//updates player
    void updateInput(const float& dt) override;//pause & unpuase & quit
    void updatePMenuButtons();
    void updateView(const float& dt);//moves camera based on player position
    void updateTileMap(const float& dt);//checks for collisions, and choose which tiles to render
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
};


#endif //VIDEOGAME_GAMESTATE_H
