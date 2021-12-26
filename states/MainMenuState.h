//
// Created by bianc on 07/12/2021.
//

#ifndef VIDEOGAME_MAINMENUSTATE_H
#define VIDEOGAME_MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"
class MainMenuState:public State {
private:
    //variables
    sf::Font font;
    sf::RectangleShape background;
    sf::Texture bgTexture;
    std::map<std::string,Button*>buttons;

    //Functions
    void initBackground();
    void initKeybinds() override;
    void initfonts();
    void initButtons();

public:
    //CON & DES
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*> *states);
    virtual ~MainMenuState();


    void endState();//just to see which state is ending

    void render(sf::RenderTarget* target);
    void renderButtons(sf::RenderTarget* target);//renders buttons

    void updateButtons();//changes button status
    void updateInput(const float&dt);
    void update(const float& dt);


};


#endif //VIDEOGAME_MAINMENUSTATE_H
