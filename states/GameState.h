//
// Created by bianc on 05/12/2021.
//

#ifndef VIDEOGAME_GAMESTATE_H
#define VIDEOGAME_GAMESTATE_H

#include "State.h"

class GameState :public State{
private:
    Entity player;

    //Functions
    void initKeybinds() override;

public:
    GameState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys,std::stack<State*> *states);
    virtual ~GameState();


    void endState() override;//just to see which state is ending
    void updateInput(const float&dt) override;
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
};


#endif //VIDEOGAME_GAMESTATE_H
