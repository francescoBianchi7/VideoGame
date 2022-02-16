//
// Created by bianc on 30/11/2021.
//
#include "PreCompHeaders.h"
#include "GameEngine.h"
using namespace sf;

//Constructors& Destructors
GameEngine::GameEngine() {
    createWindow();
    initKeys();
    initStates();

}

GameEngine::~GameEngine() {
    delete this->window;

    while(!this->states.empty()){
        delete this->states.top();
        states.pop();
    }

}


//init func
void GameEngine::createWindow() {
    sf::VideoMode windowBounds=sf::VideoMode::getDesktopMode();
    videoModes=sf::VideoMode::getFullscreenModes();
    std::string title;
    unsigned fps=0;
    bool vSync=false;
    unsigned antiAliasing=0;

    std::ifstream ifs("C:/Users/bianc/CLionProjects/VideoGame/config/window.ini");
    if(ifs.is_open()){
        std::getline(ifs,title);
        ifs>>windowBounds.width>>windowBounds.height;
        ifs>>fullscreen;
        ifs>>fps;
        ifs>>vSync;
        ifs>>antiAliasing;
    }
    ifs.close();
    /*Creates an SFML Window */
    windowSettings.antialiasingLevel=antiAliasing;
    if(fullscreen)
        window=new sf::RenderWindow(windowBounds,title,sf::Style::Fullscreen);
    else
        window=new sf::RenderWindow(sf::VideoMode(windowBounds.width,windowBounds.height), title
                                          ,sf::Style::Titlebar | sf::Style::Close,windowSettings);
    window->setFramerateLimit(fps);
    window->setVerticalSyncEnabled(vSync);

}

void GameEngine::initKeys() {

    std::ifstream ifs("./config/supportedKeys.ini");
    if(ifs.is_open()){
        std::string key=" ";
        int key_value=0;
        while(ifs >> key >> key_value){
            supportedKeys[key]=key_value;
        }

    }
    ifs.close();

    //To be removed
    for(auto i:this->supportedKeys){
        std::cout<<i.first<<" "<<i.second<<"\n";
    }
}

void GameEngine::initStates(){
    //when the game opens it starts in the main menu state
    this->states.push(new MainMenuState(this->window,&this->supportedKeys,&this->states));


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
    if(!this->states.empty()){
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


//rendering
void GameEngine::render() {
    this->window->clear();
    //render items
    if(!this->states.empty())
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


