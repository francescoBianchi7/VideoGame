#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include "State.h"
#include "..\GUI\PauseMenu.h"
#include "..\GUI\PlayerGui.h"
#include "..\Map\TileMap.h"
#include "..\Weapon\Gun.h"
#include "..\entities\Enemy.h"
#include "..\entities\BaldZombie.h"

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
    bool gameOver=false;

    ///BULLET
    Bullet b1;
    std::vector<Bullet> bullets;

    PauseMenu *pmenu;
    PlayerGui* playerGui;
    sf::Font font;
    sf::Font GOfont;
    sf::Text gameOverText;
    sf::Text pressEnterText;

    GameCharacter* player;//memory is dinamically allocated
    std::vector<Enemy*> activeEnemies;// vector containing all enemies
    sf::Texture texture;

    TileMap* tileMap;
    ///Initialization Functions
    void initDelayedRender();//to render faster
    void initView();
    void initBullets();
    void initKeybinds() override;
    void initTextures();
    void initFonts();
    void initPlayer();
    void initPlayerGui();
    void initPauseMenu();
    void initTileMap();
    void initGameOver();

public:
    explicit GameState(StateData &stateData);
    virtual ~GameState();

    void render(sf::RenderTarget* target) override;
    static void setupText(sf::Text *textItem, const sf::Font &font, const std::string &value, int size, sf::Color color);
    ///update functions
    void updatePlayerInput(const float& dt);//choose player actions based on input received
    void updatePlayer(const float& dt);//updates player
    void updateEnemies(const float& dt);
    void updateCombat(Enemy* enemy, const float& dt);
    void updateInput(const float& dt) override;//pause & unpuase & quit
    void updatePlayerGui(const float& dt);
    void updatePMenuButtons();
    void updateView(const float& dt);//moves camera based on player position
    void updateTileMap(const float& dt);//checks for collisions, and choose which tiles to render
    void update(const float& dt) override;

    void setGameOver();
    void endState() override;//just to see which state is ending
};


#endif //VIDEOGAME_GAMESTATE_H
