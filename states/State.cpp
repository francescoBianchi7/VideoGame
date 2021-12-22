//
// Created by bianc on 30/11/2021.
//

#include "State.h"
State::State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys,std::stack<State*> *states) {

    this->window=window;
    this->supportedKeys=supportedKeys;
    this->states=states;
    this->quit=false;

}
State::~State() {

}

void State::checkForQuit() {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))))
    {
        this->quit=true;
    }
}

const bool &State::getQuit() const {
    return this->quit;
}

//continuosly checks mouse pos
void State::updateMousePosition() {
    this->mousePosScreen=sf::Mouse::getPosition();
    this->mouseposWindow=sf::Mouse::getPosition(*this->window);
    this->mouseposView=this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}






