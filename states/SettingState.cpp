//
// Created by bianc on 13/02/2022.
//

#include "SettingState.h"
//INIT FUNCTIONS
void SettingState::initVariables() {
    this->modes=sf::VideoMode::getFullscreenModes();
}

void SettingState::initKeybinds() {
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

void SettingState::initfonts() {
    if(!this->font.loadFromFile("assets/fonts/Amarante.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
    }
}

void SettingState::initGUI() {
    this->buttons["EXIT_STATE_BUTTON"]=new GUI::Button(500.f,680.f,250.f,50.f,&this->font,"Back",50,
                                                  sf::Color(71,71,71,200),sf::Color(150,151,151,200),
                                                  sf::Color(20,20,20,50),
                                                  sf::Color(100,100,150,0),sf::Color(51,51,51,0),
                                                  sf::Color(255,0,25,0));
    this->buttons["APPLY"]=new GUI::Button(900.f,800.f,250.f,50.f,&this->font,"Apply",50,
                                                       sf::Color(71,71,71,200),sf::Color(150,151,151,200),
                                                       sf::Color(20,20,20,50),
                                                       sf::Color(100,100,150,0),sf::Color(51,51,51,0),
                                                       sf::Color(255,0,25,0));
    //testing if the dropdownlist works
    std::vector<std::string> modes_string;
    for (auto&i :this->modes)
        modes_string.push_back(std::to_string(i.width)+'x'+std::to_string(i.height));
    this->dropDownLists["RESOLUTION"]=new GUI::DropDownList(500,360,200,50,font,modes_string.data(),modes_string.size());
}

void SettingState::initBackground() {
    this->background.setSize(sf::Vector2f((float)this->window->getSize().x,(float)this->window->getSize().y));
    if(!this->bgTexture.loadFromFile("assets/mainmenu/bg.png"))
        std::cout<<"ERROR::COULDN'T LOAD TEXTURE FROM FILE";

    this->bgTexture.loadFromFile("assets/mainmenu/bg.png");
    this->background.setTexture(&bgTexture);

}
void SettingState::initText() {
    this->optionsText.setFont(font);
    this->optionsText.setPosition(100.f,450.f);
    this->optionsText.setCharacterSize(30);
    this->optionsText.setFillColor(sf::Color(255,255,255,200));
    this->optionsText.setString("Resolution\n\nFullscreen\n\nVsync\n\nAntiliasing\n");
}
//
//CON & DES
SettingState::SettingState(StateData &stateData)
:State(stateData){
    initVariables();
    initKeybinds();
    initfonts();
    initBackground();
    initGUI();
    initText();
}
SettingState::~SettingState() {
    for(const auto& b:buttons){
        delete b.second;
    }
    for(const auto& d:dropDownLists){
        delete d.second;
    }
}
// VARIOUS
void SettingState::endState() {
    this->quit=true;
    std::cout<<"ending MainMenuState"<<"\n";
}
//
//RENDER FUNCTIONS
void SettingState::render(sf::RenderTarget* target) {
    if(!target)
        target=this->window;
    target->draw(this->background);
    renderGUI(*target);
    target->draw(this->optionsText);
}

void SettingState::renderGUI(sf::RenderTarget& target) {
    for(auto &it: this->buttons){
        it.second->render(target);
    }
    for(auto &it: this->dropDownLists){
        it.second->render(target);
    }
}
//
//UPDATE FUNCTIONS
void SettingState::updateInput(const float &dt) {}
void SettingState::updateGUI(const float &dt) {
    /*Updates the GUI elements and handles their functionalities*/
    for(auto &it: this->buttons){
        it.second->update(this->mouseposView);
    }
    //goes back to main menu state
    if(this->buttons["EXIT_STATE_BUTTON"]->isBTNPressed()){
        endState();
    }
    //Apply selected settings
    if(this->buttons["APPLY"]->isBTNPressed()){
        //TEST TO BE REMOVED
        stateData.gxSettings->resolution=this->modes[this->dropDownLists["RESOLUTION"]->getActiveElementId()];
        std::cout<<stateData.gxSettings->resolution.width<<""<<stateData.gxSettings->resolution.height;
        window->create(stateData.gxSettings->resolution,stateData.gxSettings->title,sf::Style::Default);
    }
    //DropDownList
    for(auto &it: this->dropDownLists){
        it.second->update(this->mouseposWindow,dt);
    }
}

void SettingState::update(const float& dt) {
    updateInput(dt);
    updateMousePosition();
    updateGUI(dt);
}




