#ifndef VIDEOGAME_SETTINGSTATE_H
#define VIDEOGAME_SETTINGSTATE_H
#include "State.h"
#include "GUI.h"
#include "GSettings.h"
class SettingState:public State {
private:
    sf::Font font;
    sf::RectangleShape background;
    sf::Texture bgTexture;
    std::map<std::string,GUI::Button*>buttons;
    std::map<std::string,GUI::DropDownList*> dropDownLists;
    sf::Text optionsText;
    std::vector<sf::VideoMode> modes;

    //Functions
    void initVariables();
    void initBackground();
    void initKeybinds() override;
    void initfonts();
    void initGUI();
    void initText();
public:
    SettingState(StateData &stateData);
    virtual ~SettingState();

    void render(sf::RenderTarget* target) override;
    void renderGUI(sf::RenderTarget& target);//renders buttons
    void endState() override;

    void updateGUI(const float &dt);//changes button status
    void updateInput(const float& dt) override;
    void update(const float& dt)override;
};



#endif //VIDEOGAME_SETTINGSTATE_H
