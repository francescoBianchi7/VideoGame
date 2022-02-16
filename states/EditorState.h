//
// Created by bianc on 09/02/2022.
//

#ifndef VIDEOGAME_EDITORSTATE_H
#define VIDEOGAME_EDITORSTATE_H

//need this class to make tiles etc
#include "State.h"
#include "GUI.h"
class EditorState :public State{
private:
    sf::Font font;

    std::map<std::string, GUI::Button*> buttons;

    void initVariables();
    void initBackground();
    void initKeybinds() override;
    void initfonts();
    void initButtons();
public:
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys,std::stack<State*> *states);

    virtual ~EditorState();
    void render(sf::RenderTarget* target);
    void renderButtons(sf::RenderTarget& target);
//renders buttons
    void endState();
    void updateButtons();//changes button status
    void updateInput(const float& dt) override;
    void update(const float& dt)override;
};


#endif //VIDEOGAME_EDITORSTATE_H
