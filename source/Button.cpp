//
// Created by bianc on 07/12/2021.
//

#include "Button.h"

Button::Button(float x,float y,float width,float height,sf::Font* font,const std::string buttonText,
               sf::Color idleColor,sf::Color hoverColor,sf::Color pressedColor) {
    this->buttonState=BTN_Idle;
    this->shape.setPosition(sf::Vector2f(x,y));
    this->shape.setSize(sf::Vector2f(width,height));
    this->font=font;
    this->buttonText.setFont(*this->font);
    this->buttonText.setString(buttonText);
    this->buttonText.setFillColor(sf::Color::Black);
    this->buttonText.setCharacterSize(12);
    this->buttonText.setCharacterSize(shape.getGlobalBounds().width/5.f);//to be adjusted
    this->buttonText.setPosition(
            shape.getPosition().x+(this->shape.getGlobalBounds().width/2.f) -this->buttonText.getGlobalBounds().width/2.f,
            shape.getPosition().y+(this->shape.getGlobalBounds().height/2.f)-this->buttonText.getGlobalBounds().height/2.f);


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
    buttonState=BTN_Idle;
    shape.setFillColor(this->idleColor);
    //hover
    if(this->shape.getGlobalBounds().contains(mousePos)){
        buttonState=BTN_Hover;
        shape.setFillColor(this->hoverColor);
        //Pressed
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            buttonState=BTN_Pressed;
            shape.setFillColor(this->pressedColor);
        }
    }
}
//used in gameEngine
bool Button::isBTNPressed() const {
    if(this->buttonState==BTN_Pressed)
        return true;
    return false;
}
