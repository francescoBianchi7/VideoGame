//
// Created by bianc on 30/11/2021.
//

#include "GameEngine.h"
using namespace sf;
//init func
void GameEngine::initVariables() {
    window= nullptr;
    dt=0.f;
    tileSize=50.f;
}
void GameEngine::createWindow() {
    /*Creates an SFML Window */
    //reads the data graphics.ini
    if(gSettings.fullscreen)
        window=new sf::RenderWindow(gSettings.resolution,
                                    gSettings.title,
                                    sf::Style::Fullscreen,
                                    gSettings.contextSettings);
    else
        window=new sf::RenderWindow(gSettings.resolution,
                                    gSettings.title,
                                    sf::Style::Titlebar | sf::Style::Close,
                                    gSettings.contextSettings);
    window->setFramerateLimit(gSettings.fpsLimit);
    window->setVerticalSyncEnabled(gSettings.verticalSync);
}

void GameEngine::initKeys() {
    //reads data and set it up for the starting state
    std::ifstream ifs("./config/supportedKeys.ini");
    if(ifs.is_open()){
        std::string key=" ";
        int key_value=0;
        while(ifs >> key >> key_value){
            supportedKeys[key]=key_value;
        }
    }
    ifs.close();
    //To be removed DEBUG
    for(const auto& i:this->supportedKeys){
        std::cout<<i.first<<" "<<i.second<<"\n";
    }
}
void GameEngine::initGSettings() {//loads file
    gSettings.loadFromFile("./config/graphics.ini");
}
void GameEngine::initStateData() {
    //initializes data that is passed between the various states
    stateData.window=window;
    stateData.gxSettings=&gSettings;
    stateData.supportedKeys=&supportedKeys;
    stateData.states=&states;
    stateData.tileSize=tileSize;
}

void GameEngine::initStates(){
    //when the game opens it starts in the main menu state
    this->states.push(new MainMenuState(stateData));
}

//Constructors& Destructors
GameEngine::GameEngine() {
    initVariables();
    initGSettings();
    createWindow();
    initKeys();
    initStateData();
    initStates();
}
GameEngine::~GameEngine() {
    delete this->window;
    while(!this->states.empty()){
        delete this->states.top();
        states.pop();
    }
}
// update functions
void GameEngine::updateDt() {
    /*Updates dt var with the time it takes to update and render 1 frame */
    this->dt=this->dtClock.restart().asSeconds();
   /* system("cls");
    std::cout<<this->dt<<"\n";*///just to test if it worked properly
}

void GameEngine::closeWindow() {
    while (this->window->pollEvent(this->sfEvent))
    {
        /*make the x appear on top of window to close it */
        if (this->sfEvent.type == sf::Event::Closed)
            window->close();
    }
}


void GameEngine::update() {
    //changes the state you are on
    this->closeWindow();
    if(!this->states.empty()){//so it doesn't update while it's alt-tab etc
        this->states.top()->update(this->dt);
        if(this->states.top()->getQuit()){//if quit is true it closes the game
            delete this->states.top();
            this->states.pop();
        }
    }else{
        //application end
        endApplication();
        window->close();
    }
}
//
//RENDER FUNCTIONS
void GameEngine::render() {
    this->window->clear();
    //render items
    if(!this->states.empty()&& this->window->hasFocus())
        this->states.top()->render(window);
    this->window->display();

}
//test
void GameEngine::endApplication() {
    std::cout<<"Ending App";
}

void GameEngine::run() {
    //loop for running the game
    while (this->window->isOpen())
    {
        updateDt();
        update();
        render();
    }
}


