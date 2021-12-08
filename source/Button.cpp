//
// Created by bianc on 07/12/2021.
//

#include "Button.h"

Button::Button(float x,float y,float width,float height,sf::Font* font,std::string buttonText,
               sf::Color idleColor,sf::Color hoverColor,sf::Color pressedColor) {
    this->buttonState=BTN_Idle;
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width,height));
    this->font=font;
    this->buttonText.setFont(*this->font);
    this->buttonText.setString(buttonText);
    this->buttonText.setFillColor(sf::Color::Black);
    this->buttonText.setCharacterSize(12);
    this->buttonText.setCharacterSize(this->shape.getGlobalBounds().width/5.f);//to be adjusted
    this->buttonText.setPosition(
            this->shape.getPosition().x+(this->shape.getGlobalBounds().width/2.f) -this->buttonText.getGlobalBounds().width/2.f,
            this->shape.getPosition().y+(this->shape.getGlobalBounds().height/2.f)-this->buttonText.getGlobalBounds().height/2.f);


    this->idleColor=idleColor;
    this->hoverColor=hoverColor;
    this->pressedColor=pressedColor;

    this->shape.setFillColor(this->idleColor);
}

Button::~Button() {

}




void Button::render(sf::RenderTarget *target) {
    target->draw(this->shape);
    target->draw(this->buttonText);
}

void Button::update(const sf::Vector2f mousePos) {
    //idle
    this->buttonState=BTN_Idle;
    this->shape.setFillColor(this->idleColor);
    //hover
    if(this->shape.getGlobalBounds().contains(mousePos)){
        this->buttonState=BTN_Hover;
        this->shape.setFillColor(this->hoverColor);
        //Pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->buttonState=BTN_Pressed;
            this->shape.setFillColor(this->pressedColor);
        }
    }
}
//used in gameEngine
const bool Button::isBTNPressed() const {
    if(this->buttonState==BTN_Pressed)
        return true;
    return false;
}
