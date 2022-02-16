//
// Created by bianc on 05/12/2021.
//
#include "PreCompHeaders.h"
#include "GameState.h"



void GameState::initKeybinds() {

    /*this function permits to assign the keybinds for a state based on
     * the available supportedkeys,by reading them from a file
     * e.g. the main menu(or whatever it's gonna be called) state can have different
     * keybinds */

    std::ifstream ifs("./config/gamestate_keybinds.ini");
    if(ifs.is_open()){
        std::string key=" ";
        std::string key2=" ";
        while(ifs >> key >> key2){
            keybinds[key]=this->supportedKeys->at(key2);
        }
    }
    ifs.close();
}
void GameState::initFonts() {
    if(!this->font.loadFromFile("assets/fonts/Amarante.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}
void GameState::initTextures() {
    if(!this->textures["PLAYER_SHEET"].loadFromFile("./assets/Sprites/GC/GC_Sheet.png"))
        throw "ERROR::GAME_STATE::COULDNOTLOADIDLETEXTURE";
}
void GameState::initPlayer() {

    this->player= new GameCharacter(0, 0, this->textures["PLAYER_SHEET"]);
}
void GameState::initPauseMenu() {
    this->pmenu=new PauseMenu(*window,this->font);
    this->pmenu->addButton("QUIT",800.f,"Quit");
}

GameState::GameState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys,std::stack<State*> *states)
:State(window,supportedKeys,states){
    initKeybinds();
    initFonts();
    initTextures();
    initPauseMenu();
    initPlayer();
}

GameState::~GameState() {
    delete this->player;
    delete this->pmenu;
}

//functions
void GameState::render(sf::RenderTarget* target) {
    if(!target)
        target= (this->window);
    player->render(*target);
    if(paused)
    {
        this->pmenu->render(*target);
    }
}

void GameState::updatePlayerInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
        this->player->move(dt,-1.f,0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
        this->player->move(dt,1.f,0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
        this->player->move(dt,0.f,-1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
        this->player->move(dt,0.f,1.f);

}

void GameState::update(const float& dt) {
    this->updateMousePosition();
    this->updateKeyTime(dt);
    this->updateInput(dt);


    if(!this->paused){
        this->updatePlayerInput(dt);
        this->player->update(dt);
    }else{//paused state
        this->pmenu->update(this->mouseposView);
        this->updatePMenuButtons();
    }
}

void GameState::endState() {
    this->quit=true;
    std::cout<<"ending gamestate"<<"\n";
}



void GameState::updateInput(const float &dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))&& this->getKeyTime()){
        if(!paused)
            this->pauseState();
        else
            this->unpauseState();
    }
}

void GameState::updatePMenuButtons() {
    if(this->pmenu->isButtonPressed("QUIT"))
        this->endState();
}





