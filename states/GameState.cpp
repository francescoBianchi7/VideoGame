//
// Created by bianc on 05/12/2021.
//

#include "GameState.h"
void GameState::initKeybinds() {

    /*this function permits to assign the keybinds for a state based on
     * the available supportedkeys,by reading them from a file
     * e.g. the main menu(or whatever it's gonna be called) state can have different
     * keybinds */

    std::ifstream ifs("C:/Users/bianc/CLionProjects/VideoGame/config/gamestate_keybinds.ini");
    if(ifs.is_open()){
        std::string key="";
        std::string key2="";
        while(ifs >> key >> key2){
            this->keybinds[key]=this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}

GameState::GameState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys,std::stack<State*> *states)
:State(window,supportedKeys,states){
    this->initKeybinds();
}

GameState::~GameState() {

}





void GameState::render(sf::RenderTarget* target) {
    if(!target)
        target=this->window;
    this->player.render(this->window);
}


void GameState::updateInput(const float &dt) {
    this->checkForQuit();
    /*move the player
    *momentary* in the future it's gonna be in another class*/
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player.move(dt,-1.f,0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player.move(dt,1.f,0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player.move(dt,0.f,-1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player.move(dt,0.f,1.f);
}


void GameState::update(const float& dt) {
    this->updateMousePosition();
    this->updateInput(dt);
    this->player.update(dt);
}

void GameState::endState() {
    std::cout<<"ending gamestate"<<"\n";

}

