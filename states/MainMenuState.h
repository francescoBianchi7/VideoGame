#ifndef VIDEOGAME_MAINMENUSTATE_H
#define VIDEOGAME_MAINMENUSTATE_H

#include "GameState.h"
#include "GUI.h"
#include "EditorState.h"
#include "SettingState.h"
class MainMenuState:public State {
private:
    //variables
    sf::Font font;
    sf::RectangleShape background;
    sf::Texture bgTexture;
    std::map<std::string,GUI::Button*> buttons;

    //Functions
    void initBackground();
    void initKeybinds() override;
    void initfonts();
    void initButtons();

public:
    //CON & DES
    explicit MainMenuState(StateData& stateData);
    ~MainMenuState() override;


    void endState() override;//just to see which state is ending

    void render(sf::RenderTarget* target)override;
    void renderButtons(sf::RenderTarget& target);//renders buttons

    void updateButtons();//changes button status
    void updateInput(const float& dt) override;
    void update(const float& dt)override;
};


#endif //VIDEOGAME_MAINMENUSTATE_H
