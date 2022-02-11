//
// Created by bianc on 11/02/2022.
//

#ifndef VIDEOGAME_PAUSEMENU_H
#define VIDEOGAME_PAUSEMENU_H
#include "ctime"
#include "iostream"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

class PauseMenu {
private:
    sf::Font& font;
    sf::Text menuText;

    sf::RectangleShape background;
    sf::RectangleShape container;
    std::map<std::string ,Button*> buttons;


public:
    PauseMenu(sf::RenderWindow& window,sf::Font& font);
    virtual ~PauseMenu();
    std::map<std::string ,Button*>& getButtons();
    void addButton(std::string key,float y,std::string text);
    const bool isButtonPressed(const std::string key);
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target);
};


#endif //VIDEOGAME_PAUSEMENU_H
