//
// Created by bianc on 11/02/2022.
//

#ifndef VIDEOGAME_PAUSEMENU_H
#define VIDEOGAME_PAUSEMENU_H

#include "GUI.h"

class PauseMenu {
private:
    sf::Font& font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;
    std::map<std::string ,GUI::Button*> buttons;


public:
    PauseMenu(sf::RenderWindow& window,sf::Font& font);
    virtual ~PauseMenu();
    std::map<std::string ,GUI::Button*>& getButtons();
    void addButton(std::string key,float y,std::string text);
    const bool isButtonPressed(const std::string key);
    void update(const sf::Vector2i& mousePosWindow);
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_PAUSEMENU_H
