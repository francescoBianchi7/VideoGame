//
// Created by bianc on 05/12/2021.
//

#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include "State.h"
#include "..\GUI\PauseMenu.h"
#include "..\Map\TileMap.h"

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
    sf::RenderTexture renderTexture; //renders all tiles in a canvas
    sf::Sprite renderSprite;// paste the canvas on window

    PauseMenu *pmenu;
    sf::Font font;

    GameCharacter* player;//memory is dinamically allocated
    sf::Texture texture;

    TileMap* tileMap;
    //Functions
    void initDelayedRender();
    void initView();
    void initKeybinds() override;
    void initTextures();
    void initFonts();
    void initPlayer();
    void initPauseMenu();
    void initTileMap();

public:
    GameState(StateData &stateData);
    virtual ~GameState();

    void endState() override;//just to see which state is ending
    void updatePlayerInput(const float& dt);//changed name
    void updateInput(const float& dt) override;
    void updatePMenuButtons();
    void updateView(const float& dt);
    void updateTileMap(const float& dt);
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
};


#endif //VIDEOGAME_GAMESTATE_H
