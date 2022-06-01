//
// Created by bianc on 30/11/2021.
//

#ifndef VIDEOGAME_GAMEENGINE_H
#define VIDEOGAME_GAMEENGINE_H
#include "PreCompHeaders.h"
#include "../states/MainMenuState.h"

class GameEngine {
private:
        //variables
        sf::Vector2f resolution;
        sf::RenderWindow *window;
        StateData stateData;
        sf::Event sfEvent;
        GSettings gSettings;
        sf::Clock dtClock;//keep track of game-frames so it's not machine dep
        float dt;
        float tileSize;
        std::stack<State*> states; //top one of stack is the active state
        //so they can be changed
        std::map<std::string,int> supportedKeys;//basic set of keys,read from file


        //init functions
        void initVariables();
        void createWindow();
        void initKeys();
        void initGSettings();
        void initStateData();
        void initStates();

public:

    //Constructors&Destructors
    GameEngine();
    virtual ~GameEngine();
    //Regular
    static void endApplication();
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
