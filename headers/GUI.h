//
// Created by bianc on 07/12/2021.
//

#ifndef VIDEOGAME_GUI_H
#define VIDEOGAME_GUI_H
#include "PreCompHeaders.h"
enum button_states{BTN_Idle=0,BTN_Hover,BTN_Pressed};
/*buttons to be clicked with mouse*/
namespace GUI
{
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

        sf::Color outlineIdleColor;
        sf::Color outlineHoverColor;
        sf::Color outlinePressedColor;

       short unsigned buttonState;
       short unsigned id;
    public:
        Button(float x,float y,float width,float height,sf::Font* font,
               const std::string& buttonText,unsigned characterSize,
               sf::Color text_idleColor,sf::Color text_hoverColor,sf::Color text_pressedColor,
               sf::Color idleColor,sf::Color hoverColor,sf::Color pressedColor,
               sf::Color outlineIdleColor=sf::Color::Transparent,sf::Color outlineHoverColor=sf::Color::Transparent
                       ,sf::Color outlinePressedColor=sf::Color::Transparent,short unsigned id=0);
        virtual ~Button();

        void setText(const std::string& text);
        void setId(short unsigned id);
        const short unsigned& getId() const;
        bool isBTNPressed() const;
        std::string getText();
        //Functions
        void render(sf::RenderTarget& Target);
        void update(sf::Vector2f mousePos);//checks if the mouse is on the button(clicking it doesn't do anything rn
    };

    class DropDownList{
    private:
        float keyTime,keyTimeMax;
        sf::Font& font;
        GUI::Button* activeElement;
        std::vector<GUI::Button*> list;
        bool showList;
    public:
        DropDownList(float x,float y,float width,float height,sf::Font& font,std::string list[],unsigned nrofElements,unsigned defaultIndex=0);
        virtual ~DropDownList();

        const unsigned short& getActiveElementId() const;
        bool getKeyTime();
        void updateKeyTime(const float &dt);
        void render(sf::RenderTarget& target);
        void update(const sf::Vector2i &mousePosWindow,const float &dt);
    };
}

#endif //VIDEOGAME_GUI_H
