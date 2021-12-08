//
// Created by bianc on 30/11/2021.
//

#ifndef VIDEOGAME_GAMEENGINE_H
#define VIDEOGAME_GAMEENGINE_H

#include "../states/MainMenuState.h"

class GameEngine {
private:
    //variables
        sf::Vector2f resolution;
        sf::RenderWindow *window;
        sf::Event sfEvent;

        sf::Clock dtClock;//keep track of game-frames so it's not machine dep
        float dt;

        std::stack<State*> states; //top one of stack is the active state
        //so they can be changed
        std::map<std::string,int> supportedKeys;//basic set of keys,read from file


        //init functions
        void createWindow();
        void initKeys();
        void initStates();

public:

    //Constructors&Destructors
    GameEngine();
    virtual ~GameEngine();
    //Regular
    void endApplication();
    //update functions
    void updateDt();
    void closeWindow();//x on top of window to close it
    void update();

    //render
    void render();

    //core
    void run();

};


#endif //VIDEOGAME_GAMEENGINE_H
