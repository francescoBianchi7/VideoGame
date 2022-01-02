//
// Created by bianc on 07/12/2021.
//

#include "MainMenuState.h"



void MainMenuState::initKeybinds() {
    std::ifstream ifs("./config/mainmenu_keybinds.ini");
if(ifs.is_open()){
    std::string key=" ";
    std::string key2=" ";
    while(ifs >> key >> key2){
        this->keybinds[key]=this->supportedKeys->at(key2);
    }
}
ifs.close();
}

MainMenuState::MainMenuState(sf::RenderWindow* window,std::map<std::string,int>* supportedKeys,std::stack<State*> *states)
:State(window,supportedKeys,states){

    initKeybinds();
    initfonts();

    initBackground();
    initButtons();

}
MainMenuState::~MainMenuState() {
    for(auto b:buttons){
        delete b.second;
    }
}

void MainMenuState::endState() {
    this->quit=true;
    std::cout<<"ending MainMenuState"<<"\n";
}

void MainMenuState::initfonts() {
    if(!this->font.loadFromFile("assets/fonts/Amarante.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void MainMenuState::initButtons() {
    this->buttons["GAME_STATE_BUTTON"]=new Button(200.f,280.f,250.f,50.f,
                                                  &this->font,"Play",50,
                                                  sf::Color(71,71,71,200),sf::Color(150,151,151,200),
                                                  sf::Color(20,20,20,50),
                                                  sf::Color(100,100,150,0),sf::Color(51,51,51,0),
                                                  sf::Color(255,0,25,0));
    this->buttons["EDITOR"]=new Button(200.f,380.f,250.f,50.f,&this->font,"Editor",50,
                                       sf::Color(71,71,71,200),sf::Color(150,151,151,200),
                                       sf::Color(20,20,20,50),
                                       sf::Color(100,100,150,0),sf::Color(51,51,51,0),
                                       sf::Color(255,0,25,0));
    this->buttons["SETTINGS"]=new Button(200.f,480.f,250.f,50.f,&this->font,"Settings",50,
                                         sf::Color(71,71,71,200),sf::Color(150,151,151,200),
                                         sf::Color(20,20,20,50),
                                         sf::Color(100,100,150,0),sf::Color(51,51,51,0),
                                         sf::Color(255,0,25,0));
    this->buttons["EXIT_STATE_BUTTON"]=new Button(200.f,680.f,250.f,50.f,&this->font,"Quit",50,
                                                  sf::Color(71,71,71,200),sf::Color(150,151,151,200),
                                                  sf::Color(20,20,20,50),
                                                  sf::Color(100,100,150,0),sf::Color(51,51,51,0),
                                                  sf::Color(255,0,25,0));
}

void MainMenuState::initBackground() {
    this->background.setSize(sf::Vector2f((float)this->window->getSize().x,(float)this->window->getSize().y));
    if(!this->bgTexture.loadFromFile("assets/mainmenu/bg.png"))
        std::cout<<"ERROR::COULDN'T LOAD TEXTURE FROM FILE";

    this->bgTexture.loadFromFile("assets/mainmenu/bg.png");
    this->background.setTexture(&bgTexture);

}


void MainMenuState::updateInput(const float &dt) {
}


void MainMenuState::render(sf::RenderTarget* target) {
    if(!target)
        target=this->window;
    target->draw(this->background);
    renderButtons(target);
}

//don't know if I really need this one
void MainMenuState::renderButtons(sf::RenderTarget* target) {
    for(auto &it: this->buttons){
        it.second->render(target);
    }
}

void MainMenuState::updateButtons() {
    /*Updates the buttons and handles their functionalities*/
    for(auto &it: this->buttons){
        it.second->update(this->mouseposView);
    }
    //new game,pushes g-state on top of stack
    if(this->buttons["GAME_STATE_BUTTON"]->isBTNPressed()){
        this->states->push(new GameState(this->window,this->supportedKeys,this->states));
    }

    //quit game
    if(this->buttons["EXIT_STATE_BUTTON"]->isBTNPressed()){
        endState();
    }
}

void MainMenuState::update(const float& dt) {
    this->updateInput(dt);
    this->updateMousePosition();
    this->updateButtons();

}