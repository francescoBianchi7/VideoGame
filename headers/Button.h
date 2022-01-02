//
// Created by bianc on 07/12/2021.
//

#ifndef VIDEOGAME_BUTTON_H
#define VIDEOGAME_BUTTON_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

enum button_states{BTN_Idle=0,BTN_Hover,BTN_Pressed};
/*buttons to be clicked with mouse*/
class Button {
private:
    sf::RectangleShape shape;
    sf::Font* font;
    unsigned characterSize;

    sf::Text buttonText;
    sf::Color text_IdleColor;
    sf::Color text_hoverColor;
    sf::Color text_pressedColor;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color pressedColor;

   short unsigned buttonState;

public:
    Button(float x,float y,float width,float height,sf::Font* font,
           std::string buttonText,unsigned characterSize,
           sf::Color text_idleColor,sf::Color text_hoverColor,sf::Color text_pressedColor,
           sf::Color idleColor,sf::Color hoverColor,sf::Color pressedColor);
    virtual ~Button();

    bool isBTNPressed() const;

    //Functions
    void render(sf::RenderTarget* Target);
    void update(sf::Vector2f mousePos);//checks if the mouse is on the button(clicking it doesn't do anything rn
};


#endif //VIDEOGAME_BUTTON_H
