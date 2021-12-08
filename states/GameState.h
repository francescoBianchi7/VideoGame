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
    void initKeybinds();

public:
    GameState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys,std::stack<State*> *states);
    virtual ~GameState();


    void endState();//just to see which state is ending
    void updateInput(const float&dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};


#endif //VIDEOGAME_GAMESTATE_H
