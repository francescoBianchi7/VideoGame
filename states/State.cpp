//
// Created by bianc on 30/11/2021.
//
#include "PreCompHeaders.h"
#include "State.h"
State::State(StateData& stateData):stateData(stateData) {

    tileSize=stateData.tileSize;
    this->window=stateData.window;
    this->supportedKeys=stateData.supportedKeys;
    this->states=stateData.states;
    this->quit=false;
    this->paused=false;
    this->keyTime=0.f;
    this->keyTimeMax=20.f;
}
State::~State() {

}
//GETTERS
bool State::getKeyTime() {
    if(this->keyTime>=keyTimeMax){
        this->keyTime=0.f;
        return true;
    }
    return false;
}

const bool &State::getQuit() const {
    return this->quit;
}
//others
void State::pauseState() {
    this->paused=true;
}
void State::unpauseState() {
    this->paused=false;
}

//UPDATE
void State::updateMousePosition(sf::View* view) {//continuosly checks mouse pos
    this->mousePosScreen=sf::Mouse::getPosition();
    this->mouseposWindow=sf::Mouse::getPosition(*window);
    if(view)
        this->window->setView(*view);
    this->mouseposView=this->window->mapPixelToCoords(sf::Mouse::getPosition(*window));
    mousePosGrid=sf::Vector2u(static_cast<unsigned>(mouseposView.x)/static_cast<unsigned>(tileSize),
                              static_cast<unsigned>(mouseposView.y)/static_cast<unsigned>(tileSize));
    this->window->setView(this->window->getDefaultView());
}
void State::updateKeyTime(const float &dt) {
    if(keyTime<keyTimeMax)
        keyTime+=100.f*dt;
}