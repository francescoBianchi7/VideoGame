//
// Created by bianc on 05/12/2021.
//

#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include "State.h"
#include "..\GUI\PauseMenu.h"

class GameState :public State{
private:
    PauseMenu *pmenu;
    sf::Font font;

    GameCharacter* player;//cause memory is dinamically allocated
    sf::Texture texture;
    //Functions
    void initKeybinds() override;
    void initTextures();
    void initFonts();
    void initPlayer();
    void initPauseMenu();

public:
    GameState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys,std::stack<State*> *states);
    virtual ~GameState();


    void endState() override;//just to see which state is ending
    void updatePlayerInput(const float& dt);//changed name
    void updateInput(const float& dt) override;
    void updatePMenuButtons();
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
};


#endif //VIDEOGAME_GAMESTATE_H
