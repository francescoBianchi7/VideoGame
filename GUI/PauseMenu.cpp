//
// Created by bianc on 11/02/2022.
//
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window,sf::Font& font) :font(font){
    //init bg
    background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x),
                                               static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color(20,20,20,100));
    //init container
    container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x)/4.f,
                                         static_cast<float>(window.getSize().y)- 60.f));
    container.setFillColor(sf::Color(20,20,20,200));
    container.setPosition(static_cast<float>(window.getSize().x)/2.f-this->container.getSize().x,30.f);
    //init text
    menuText.setFont(font);
    menuText.setFillColor(sf::Color(255,255,255,200));
    menuText.setCharacterSize(60);
    menuText.setString("PAUSED");
    menuText.setPosition(
                container.getPosition().x+container.getSize().x/2.f-menuText.getGlobalBounds().width/2.f
                                   ,container.getPosition().y+30.f);
}


PauseMenu::~PauseMenu() {
    for(const auto& b:buttons){
        delete b.second;
    }
}

void PauseMenu::addButton(const std::string& key, float y, const std::string& text) {
    float width=250.f;
    float height=65.f;
    float x=container.getPosition().x+container.getSize().x/2.f-width/2.f;
    this->buttons[key]=new GUI::Button(x,y,width,height,
                                  &this->font,text,50,
                                  sf::Color(71,71,71,200),sf::Color(150,151,151,200),
                                  sf::Color(20,20,20,50),
                                  sf::Color(100,100,150,0),sf::Color(51,51,51,0),
                                  sf::Color(255,0,25,0));
}
void PauseMenu::update(const sf::Vector2i& mousePosWindow) {
    for(auto &i:buttons){
        i.second->update(static_cast<sf::Vector2f>(mousePosWindow));
    }
}

void PauseMenu::render(sf::RenderTarget& target) {
    target.draw(background);
    target.draw(container);

    for(auto &i: this->buttons){
        i.second->render(target);
    }
    target.draw(menuText);
}

std::map<std::string, GUI::Button *> &PauseMenu::getButtons() {
    return this->buttons;
}

bool PauseMenu::isButtonPressed(const std::string& key) {
    return this->buttons[key]->isBTNPressed();
}


