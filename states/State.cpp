//
// Created by bianc on 30/11/2021.
//
#include "PreCompHeaders.h"
#include "State.h"
State::State(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys,std::stack<State*> *states) {

    this->window=window;
    this->supportedKeys=supportedKeys;
    this->states=states;
    this->quit=false;
    this->paused=false;
    this->keyTime=0.f;
    this->keyTimeMax=10.f;
}
State::~State() {

}

const bool &State::getQuit() const {
    return this->quit;
}

//continuosly checks mouse pos
void State::updateMousePosition() {
    this->mousePosScreen=sf::Mouse::getPosition();
    this->mouseposWindow=sf::Mouse::getPosition(*window);
    this->mouseposView=this->window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::pauseState() {
    this->paused=true;
}

void State::unpauseState() {
    this->paused=false;
}

void State::updateKeyTime(const float &dt) {
    if(keyTime<keyTimeMax)
        keyTime+=100.f*dt;
}

bool State::getKeyTime() {
    if(this->keyTime>=keyTimeMax){
        this->keyTime=0.f;
        return true;
    }
    return false;
}






