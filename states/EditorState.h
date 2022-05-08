//
// Created by bianc on 09/02/2022.
//

#ifndef VIDEOGAME_EDITORSTATE_H
#define VIDEOGAME_EDITORSTATE_H

//need this class to make tiles etc
#include "State.h"
#include "GUI.h"
#include "..\GUI\PauseMenu.h"
#include "..\Map\TileMap.h"
class EditorState :public State{
private:
    sf::View view;

    sf::Font font;
    sf::Text cursorText;
    PauseMenu* pmenu;//this is used to quit the state
    TileMap *tileMap;
    std::map<std::string, GUI::Button*> buttons;
    sf::RectangleShape selectorRect;//shows which tile you are about to place
    sf::IntRect textureRect; //tileTexture

    bool collision;
    short type;
    float cameraSpeed;
    //init functions
    void initVariables();
    void initBackground();
    void initKeybinds() override;
    void initfonts();
    void initText();
    void initGui();
    void initButtons();
    void initPauseMenu();
    void initTileSheet();
    void initView();
public:
    EditorState(StateData &stateData);
    virtual ~EditorState();
    //render functions
    void render(sf::RenderTarget* target);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget &target);
    //update functions
    void updatePMenuButtons();
    void updateButtons();//changes button status
    void updateInput(const float& dt) override;
    void updateEditorInput(const float& dt);
    void updateGui();
    void update(const float& dt)override;
    //other funtions
    void endState();

};


#endif //VIDEOGAME_EDITORSTATE_H
